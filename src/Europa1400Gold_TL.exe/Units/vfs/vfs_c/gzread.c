/* gzread -- read from a gzip (.gz) stream.  Own TU so the link places it at
 * the reference's 0x10003960: check_header's object (0x100036d0) and vfs.c's
 * two functions (0x10003820, 0x100038a0) sit between them in the original.
 * Body from references/zlib-1.1.3/gzio.c with the stripped blocks removed;
 * the shared VFS byte reader stands in for the TU-local get_byte (the
 * reference's check_header calls 0x10003820, not a private helper).
 */

// FUNCTION: GOLDTL 0x45f380
// SIZE: 560

/* gzio.byte -- IO on .gz files
 * Copyright (C) 1995-1998 Jean-loup Gailly.
 * For conditions of distribution and use, see copyright notice in zlib.h
 */

/* @(#) $Id$ */

#include <stdio.h>

#include "zutil.h"
#include "../gz_stream.h"

/* SIZE 0x4 */
// SIZE 0x4
struct internal_state {int dummy;}; /* for buggy compilers */

#ifndef Z_BUFSIZE
#  ifdef MAXSEG_64K
#    define Z_BUFSIZE 4096 /* minimize memory usage for 16-bit DOS */
#  else
#    define Z_BUFSIZE 16384
#  endif
#endif

// SIZE 0x64 (sizeof gz_stream on 32-bit: z_stream 0x38 + 9 ptr/int + mode + startpos; verified with i686-mingw probe)
/* The reference's gzread calls the shared header checker (0x100036d0) and
 * the shared 32-bit big-endian reader (0x10003c50). */
void check_header(gz_stream *s);
int  vfs_ReadUint32BE();

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
