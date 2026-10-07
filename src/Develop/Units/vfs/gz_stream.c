#include "../Error/error.h"
#include "../m_alloc/m_alloc.h"

#include <stdio.h>
#include <stdlib.h>

int* __cdecl _errno(void);
void __cdecl free(void*);
unsigned int __cdecl vfs_GetByte(int*);
int __cdecl vfs_CloseStream(void*);

int __cdecl deflate(void*, int);  
unsigned int __cdecl vfs_GetByte(int*);
unsigned int __cdecl vfs_FlushStream(int, int);
void __cdecl vfs_WriteUint32LE(int, unsigned int);
int __cdecl vfs_CloseStream(void*);

int __cdecl vfs_ReadUint32BE(int);
int __cdecl vfs_FlushAndClose(int);
#include "zutil.h"
#include "gz_stream.h"

/* gzip header check (0x100036d0).  The reference's check_header calls the
 * shared VFS byte reader (0x10003820) rather than a TU-local get_byte, so
 * this file has no private helper and no unreferenced static code.  gzread
 * lives in gzread.c: the original places vfs.c's two functions between the
 * two, so they cannot share an object.
 */

static int gz_magic[2] = {0x1f, 0x8b}; /* gzip magic header */


/* gzio.byte -- IO on .gz files
 * Copyright (C) 1995-1998 Jean-loup Gailly.
 * For conditions of distribution and use, see copyright notice in zlib.h
 *
 * Compile this file with -DNO_DEFLATE to avoid the compression code.
 */

/* @(#) $Id$ */



// SIZE 0x4
struct internal_state {int dummy;}; /* for buggy compilers */

#ifndef Z_BUFSIZE
#  ifdef MAXSEG_64K
#    define Z_BUFSIZE 4096 /* minimize memory usage for 16-bit DOS */
#  else
#    define Z_BUFSIZE 16384
#  endif
#endif
#ifndef Z_PRINTF_BUFSIZE
#  define Z_PRINTF_BUFSIZE 4096
#endif

#define ALLOC(size) malloc(size)
#define TRYFREE(p) {if (p) free(p);}


/* gzip flag byte */
#define ASCII_FLAG   0x01 /* bit 0 set: file probably ascii text */
#define HEAD_CRC     0x02 /* bit 1 set: header CRC present */
#define EXTRA_FIELD  0x04 /* bit 2 set: extra field present */
#define ORIG_NAME    0x08 /* bit 3 set: original file name present */
#define COMMENT      0x10 /* bit 4 set: file comment present */
#define RESERVED     0xE0 /* bits 5..7: reserved */

/* Dead zlib forward decls removed: `local gzFile`/`local int`/`local void`
 * OF((...)) lines parse as globals named gzFile/int/void (false inventory). */

/* The shared VFS byte reader (0x10003820).  The reference's check_header
 * calls 0x10003820, not a TU-local helper; the signed int return keeps the
 * EOF comparison shape the target uses. */
int __cdecl vfs_GetByte(int* stream);

void check_header(gz_stream* s)
{
    int method; /* method byte */
    int flags;  /* flags byte */
    uInt len;
    int byte;

    /* Check the gzip magic header */
    for (len = 0; len < 2; len++) {
	byte = vfs_GetByte((int*)s);
	if (byte != gz_magic[len]) {
	    if (len != 0) s->stream.avail_in++, s->stream.next_in--;
	    if (byte != EOF) {
		s->stream.avail_in++, s->stream.next_in--;
		s->transparent = 1;
	    }
	    s->z_err = s->stream.avail_in != 0 ? Z_OK : Z_STREAM_END;
	    return;
	}
    }
    method = vfs_GetByte((int*)s);
    flags = vfs_GetByte((int*)s);
    if (method != Z_DEFLATED || (flags & RESERVED) != 0) {
	s->z_err = Z_DATA_ERROR;
	return;
    }

    /* Discard time, xflags and OS code: */
    for (len = 0; len < 6; len++) (void)vfs_GetByte((int*)s);

    if ((flags & EXTRA_FIELD) != 0) { /* skip the extra field */
	len  =  (uInt)vfs_GetByte((int*)s);
	len += ((uInt)vfs_GetByte((int*)s))<<8;
	/* len is garbage if EOF but the loop below will quit anyway */
	while (len-- != 0 && vfs_GetByte((int*)s) != EOF) ;
    }
    if ((flags & ORIG_NAME) != 0) { /* skip the original file name */
	while ((byte = vfs_GetByte((int*)s)) != 0 && byte != EOF) ;
    }
    if ((flags & COMMENT) != 0) {   /* skip the .gz file comment */
	while ((byte = vfs_GetByte((int*)s)) != 0 && byte != EOF) ;
    }
    if ((flags & HEAD_CRC) != 0) {  /* skip the header crc */
	for (len = 0; len < 2; len++) (void)vfs_GetByte((int*)s);
    }
    s->z_err = s->z_eof ? Z_DATA_ERROR : Z_OK;
}

unsigned int __cdecl vfs_GetByte(int* stream)
{
	int* errno_ptr;
	int bytes_read;

	if (stream[0xf] != 0) {
		return (unsigned int) -1;
	}
	if (stream[1] == 0) {
		errno_ptr = _errno();
		*errno_ptr = 0;
		bytes_read = (int) fread((void*) stream[0x11], 1, 0x4000, (FILE*) stream[0x10]);
		stream[1] = bytes_read;
		if (bytes_read == 0) {
			stream[0xf] = 1;
			if ((*(unsigned char*) (stream[0x10] + 0xc) & 0x20) != 0) {
				stream[0xe] = -1;
			}
			return (unsigned int) -1;
		}
		stream[0] = stream[0x11];
	}
	/* The read cursor is post-incremented in place through a pointer alias
	 * of stream[0]. Copying it into a local first makes MSVC6 hold the
	 * cursor in ecx and zero-extend the byte into eax, which loses the
	 * target's reuse of eax for both the count temp and the cursor. */
	stream[1] = stream[1] - 1;
	return *(*(unsigned char**) &stream[0])++;
}

/* Closes a VFS stream and releases associated resources.
 * Frees internal buffers and removes from open stream list. */


int __cdecl vfs_CloseStream(void* stream)
{
	int close_result;
	int* errno_ptr;
	int result;

	result = 0;
	if (stream == 0) {
		return -2;
	}
	if (*(void**) ((int) stream + 0x50) != 0) {
		free(*(void**) ((int) stream + 0x50));
	}
	if (*(int*) ((int) stream + 0x1c) != 0) {
		if (*(char*) ((int) stream + 0x5c) == 'w') {
			result = deflateEnd((void*) stream);
		}
		else if (*(char*) ((int) stream + 0x5c) == 'r') {
			result = inflateEnd((void*) stream);
		}
	}
	if (*(FILE**) ((int) stream + 0x40) != 0) {
		close_result = fclose(*(FILE**) ((int) stream + 0x40));
		if (close_result != 0) {
			errno_ptr = _errno();
			if (*errno_ptr != 0x1d) {
				result = -1;
			}
		}
	}
	if (*(int*) ((int) stream + 0x38) < 0) {
		result = *(int*) ((int) stream + 0x38);
	}
	if (*(void**) ((int) stream + 0x44) != 0) {
		free(*(void**) ((int) stream + 0x44));
	}
	if (*(void**) ((int) stream + 0x48) != 0) {
		free(*(void**) ((int) stream + 0x48));
	}
	if (*(void**) ((int) stream + 0x54) != 0) {
		free(*(void**) ((int) stream + 0x54));
	}
	free(stream);
	return result;
}

int ZEXPORT gzread(gzFile file, voidp buf, unsigned len)
{
    gz_stream *s = (gz_stream*)file;
    Bytef *start = (Bytef*)buf; /* starting point for crc computation */
    Byte  *next_out; /* == stream.next_out but not forced far (for MSDOS) */

    if (s == NULL || s->mode != 'r') return Z_STREAM_ERROR;

    if (s->z_err == Z_DATA_ERROR || s->z_err == Z_ERRNO) return -1;
    if (s->z_err == Z_STREAM_END) return 0;  /* EOF */

    next_out = (Byte*)buf;
    s->stream.next_out = (Bytef*)buf;
    s->stream.avail_out = len;

    while (s->stream.avail_out != 0) {

	if (s->transparent) {
	    /* Copy first the lookahead bytes: */
	    uInt n = s->stream.avail_in;
	    if (n > s->stream.avail_out) n = s->stream.avail_out;
	    if (n > 0) {
		zmemcpy(s->stream.next_out, s->stream.next_in, n);
		next_out += n;
		s->stream.next_out = next_out;
		s->stream.next_in   += n;
		s->stream.avail_out -= n;
		s->stream.avail_in  -= n;
	    }
	    if (s->stream.avail_out > 0) {
		s->stream.avail_out -= fread(next_out, 1, s->stream.avail_out,
					     s->file);
	    }
	    len -= s->stream.avail_out;
	    s->stream.total_in  += (uLong)len;
	    s->stream.total_out += (uLong)len;
            if (len == 0) s->z_eof = 1;
	    return (int)len;
	}
        if (s->stream.avail_in == 0 && !s->z_eof) {

            errno = 0;
            s->stream.avail_in = fread(s->inbuf, 1, Z_BUFSIZE, s->file);
            if (s->stream.avail_in == 0) {
                s->z_eof = 1;
		if (ferror(s->file)) {
		    s->z_err = Z_ERRNO;
		    break;
		}
            }
            s->stream.next_in = s->inbuf;
        }
        s->z_err = inflate(&(s->stream), Z_NO_FLUSH);

	if (s->z_err == Z_STREAM_END) {
	    /* Check CRC and original size */
	    s->crc = crc32(s->crc, start, (uInt)(s->stream.next_out - start));
	    start = s->stream.next_out;

	    if (vfs_ReadUint32BE(s) != s->crc) {
		s->z_err = Z_DATA_ERROR;
	    } else {
	        (void)vfs_ReadUint32BE(s);
                /* The uncompressed length returned by above getlong() may
                 * be different from s->stream.total_out) in case of
		 * concatenated .gz files. Check for such files:
		 */
		check_header(s);
		if (s->z_err == Z_OK) {
		    uLong total_in = s->stream.total_in;
		    uLong total_out = s->stream.total_out;

		    inflateReset(&(s->stream));
		    s->stream.total_in = total_in;
		    s->stream.total_out = total_out;
		    s->crc = crc32(0L, Z_NULL, 0);
		}
	    }
	}
	if (s->z_err != Z_OK || s->z_eof) break;
    }
    s->crc = crc32(s->crc, start, (uInt)(s->stream.next_out - start));

    return (int)(len - s->stream.avail_out);
}

/* Reads a single byte from a VFS stream. Advances the read
 * position and returns the byte value, or error on EOF. */


/* Destroys a VFS entity (file/directory node). Frees the
 * entity's name string and the entity struct itself. */


unsigned int __cdecl vfs_FlushStream(int stream, int dest)
{
	int done;
	int write_result;
	int remaining;

	done = 0;
	if (stream == 0 || *(char*) (stream + 0x5c) != 'w') {
		return 0xFFFFFFFE;
	}
	*(int*) (stream + 4) = 0;
	do {
		remaining = 0x4000 - *(int*) (stream + 0x10);
		if (remaining != 0) {
			write_result = fwrite(*(void**) (stream + 0x48), 1, remaining, *(FILE**) (stream + 0x40));
			if (write_result != remaining) {
				*(int*) (stream + 0x38) = -1;
				return (unsigned int) -1;
			}
			*(int*) (stream + 0x10) = 0x4000;
			*(int*) (stream + 0x0c) = *(int*) (stream + 0x48);
		}
		if (done) {
			break;
		}
		write_result = deflate((void*) stream, (int) dest);
		*(int*) (stream + 0x38) = write_result;
		if (remaining == 0 && write_result == -5) {
			*(int*) (stream + 0x38) = 0;
		}
		if (*(int*) (stream + 0x10) == 0 && *(int*) (stream + 0x38) != 1) {
			done = 0;
		}
		else {
			done = 1;
		}
	} while (*(int*) (stream + 0x38) == 0 || *(int*) (stream + 0x38) == 1);
	if (*(unsigned int*) (stream + 0x38) != 1) {
		return *(unsigned int*) (stream + 0x38);
	}
	return 0;
}

int __cdecl vfs_ReadUint32BE(int stream)
{
	int result;
	int last;

	result = vfs_GetByte((int*) stream);
	result = result + (vfs_GetByte((int*) stream) << 8);
	result = result + (vfs_GetByte((int*) stream) << 16);
	last = vfs_GetByte((int*) stream);
	if (last == -1) {
		*(unsigned int*) (stream + 0x38) = 0xfffffffd;
	}
	return (last << 24) + result;
}

/* Flushes a VFS stream and closes it. Combines vfs_FlushStream
 * and vfs_CloseStream into a single operation. */


int __cdecl vfs_FlushAndClose(int stream)
{
	int flush_result;

	if (stream == 0) {
		return -2;
	}
	if (*(char*) (stream + 0x5c) == 'w') {
		flush_result = vfs_FlushStream(stream, 4);
		if (flush_result == 0) {
			vfs_WriteUint32LE(*(int*) (stream + 0x40), *(unsigned int*) (stream + 0x4c));
			vfs_WriteUint32LE(*(int*) (stream + 0x40), *(unsigned int*) (stream + 8));
		}
	}
	return vfs_CloseStream((void*) stream);
}

/* Writes a 32-bit little-endian integer to the VFS stream. */


void __cdecl vfs_WriteUint32LE(int stream, unsigned int value)
{
	int i;

	i = 4;
	do {
		fputc(value & 0xff, (void*) stream);
		value = value >> 8;
		i = i - 1;
	} while (i != 0);
	return;
}

