/* gzip header check (0x100036d0).  The reference's check_header calls the
 * shared VFS byte reader (0x10003820) rather than a TU-local get_byte, so
 * this file has no private helper and no unreferenced static code.  gzread
 * lives in gzread.c: the original places vfs.c's two functions between the
 * two, so they cannot share an object.
 */

// FUNCTION: SERVER 0x100036D0

/* gzio.byte -- IO on .gz files
 * Copyright (C) 1995-1998 Jean-loup Gailly.
 * For conditions of distribution and use, see copyright notice in zlib.h
 *
 * Compile this file with -DNO_DEFLATE to avoid the compression code.
 */

/* @(#) $Id$ */

#include <stdio.h>

#include "zutil.h"
#include "../gz_stream.h"

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

static int gz_magic[2] = {0x1f, 0x8b}; /* gzip magic header */

/* gzip flag byte */
#define ASCII_FLAG   0x01 /* bit 0 set: file probably ascii text */
#define HEAD_CRC     0x02 /* bit 1 set: header CRC present */
#define EXTRA_FIELD  0x04 /* bit 2 set: extra field present */
#define ORIG_NAME    0x08 /* bit 3 set: original file name present */
#define COMMENT      0x10 /* bit 4 set: file comment present */
#define RESERVED     0xE0 /* bits 5..7: reserved */


local gzFile gz_open      OF((const char *path, const char *mode, int  fd));
local int do_flush        OF((gzFile file, int flush));
local int    destroy      OF((gz_stream *s));
local void   putLong      OF((FILE *file, uLong x));

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



/* ===========================================================================
     Opens a gzip (.gz) file for reading or writing. The mode parameter
   is as in fopen ("rb" or "wb"). The file is given either by file descriptor
   or path name (if fd == -1).
     gz_open return NULL if the file could not be opened or if there was
   insufficient memory to allocate the (de)compression state; errno
   can be checked to distinguish the two cases (if errno is zero, the
   zlib error is Z_MEM_ERROR).
*/

/* ===========================================================================
     Opens a gzip (.gz) file for reading or writing.
*/

/* ===========================================================================
     Associate a gzFile with the file descriptor fd. fd is not dup'ed here
   to mimic the behavio(u)r of fdopen.
*/

/* ===========================================================================
 * Update the compression level and strategy
 */

/* ===========================================================================
     Read a byte from a gz_stream; update next_in and avail_in. Return EOF
   for end of file.
   IN assertion: the stream s has been sucessfully opened for reading.
*/

/* ===========================================================================
      Check the gzip header of a gz_stream opened for reading. Set the stream
    mode to transparent if the gzip magic header is not present; set s->err
    to Z_DATA_ERROR if the magic header is present but the rest of the header
    is incorrect.
    IN assertion: the stream s has already been created sucessfully;
       s->stream.avail_in is zero for the first time, but may be non-zero
       for concatenated .gz files.
*/

 /* ===========================================================================
 * Cleanup then free the given gz_stream. Return a zlib error code.
   Try freeing in the reverse order of allocations.
 */

/* ===========================================================================
     Reads the given number of uncompressed bytes from the compressed file.
   gzread returns the number of bytes actually read (0 for end of file).
*/


/* ===========================================================================
      Reads one byte from the compressed file. gzgetc returns this byte
   or -1 in case of end of file or error.
*/


/* ===========================================================================
      Reads bytes from the compressed file until len-1 characters are
   read, or a newline character is read and transferred to buf, or an
   end-of-file condition is encountered.  The string is then terminated
   with a null character.
      gzgets returns buf, or Z_NULL in case of error.

      The current implementation is not optimized at all.
*/


#ifndef NO_DEFLATE
/* ===========================================================================
     Writes the given number of uncompressed bytes into the compressed file.
   gzwrite returns the number of bytes actually written (0 in case of error).
*/

/* ===========================================================================
     Converts, formats, and writes the args to the compressed file under
   control of the format string, as in fprintf. gzprintf returns the number of
   uncompressed bytes actually written (0 in case of error).
*/
#ifdef STDC
#include <stdarg.h>

#else /* not ANSI C */

int ZEXPORTVA gzprintf (file, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10,
	               a11, a12, a13, a14, a15, a16, a17, a18, a19, a20)
    gzFile file;
    const char *format;
    int a1, a2, a3, a4, a5, a6, a7, a8, a9, a10,
	a11, a12, a13, a14, a15, a16, a17, a18, a19, a20;
{
    char buf[Z_PRINTF_BUFSIZE];
    int len;

#ifdef HAS_snprintf
    snprintf(buf, sizeof(buf), format, a1, a2, a3, a4, a5, a6, a7, a8,
	     a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20);
#else
    sprintf(buf, format, a1, a2, a3, a4, a5, a6, a7, a8,
	    a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20);
#endif
    len = strlen(buf); /* old sprintf doesn't return the nb of bytes written */
    if (len <= 0) return 0;

    return gzwrite(file, buf, len);
}
#endif

/* ===========================================================================
      Writes byte, converted to an unsigned char, into the compressed file.
   gzputc returns the value that was written, or -1 in case of error.
*/


/* ===========================================================================
      Writes the given null-terminated string to the compressed file, excluding
   the terminating null character.
      gzputs returns the number of characters written, or -1 in case of error.
*/


/* ===========================================================================
     Flushes all pending output into the compressed file. The parameter
   flush is as in the deflate() function.
*/

#endif /* NO_DEFLATE */

/* ===========================================================================
      Sets the starting position for the next gzread or gzwrite on the given
   compressed file. The offset represents a number of bytes in the
      gzseek returns the resulting offset location as measured in bytes from
   the beginning of the uncompressed stream, or -1 in case of error.
      SEEK_END is not implemented, returns error.
      In this version of the library, gzseek can be extremely slow.
*/

/* ===========================================================================
     Rewinds input file. 
*/

/* ===========================================================================
     Returns the starting position for the next gzread or gzwrite on the
   given compressed file. This position represents a number of bytes in the
   uncompressed data stream.
*/

/* ===========================================================================
     Returns 1 when EOF has previously been detected reading the given
   input stream, otherwise zero.
*/

/* ===========================================================================
   Outputs a long in LSB order to the given file
*/

/* ===========================================================================
   Reads a long in LSB order from the given gz_stream. Sets z_err in case
   of error.
*/

/* ===========================================================================
     Flushes all pending output if necessary, closes the compressed file
   and deallocates all the (de)compression state.
*/

/* ===========================================================================
     Returns the error message for the last error which occured on the
   given compressed file. errnum is set to zlib error number. If an
   error occured in the file system and not in the compression library,
   errnum is set to Z_ERRNO and the application may consult errno
   to get the exact error code.
*/
