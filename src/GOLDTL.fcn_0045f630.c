// FUNCTION: GOLD 0x00463330
// FUNCTION: GOLDTL 0x45f630

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdarg.h>
#include "zutil.h"
#include "Develop/Units/vfs/gz_stream.h"

#define Z_BUFSIZE 16384

int __cdecl fcn_0045f630(gzFile file, const voidp buf, unsigned len)
{
	gz_stream* s = (gz_stream*) file;

	if (s == NULL || s->mode != 'w') {
		return Z_STREAM_ERROR;
	}
	s->stream.next_in = (Bytef*) buf;
	s->stream.avail_in = len;

	while (s->stream.avail_in != 0) {
		if (s->stream.avail_out == 0) {
			s->stream.next_out = s->outbuf;
			if (fwrite(s->outbuf, 1, Z_BUFSIZE, s->file) != Z_BUFSIZE) {
				s->z_err = Z_ERRNO;
				break;
			}
			s->stream.avail_out = Z_BUFSIZE;
		}
		s->z_err = deflate(&(s->stream), Z_NO_FLUSH);
		if (s->z_err != Z_OK) {
			break;
		}
	}
	s->crc = crc32(s->crc, (const Bytef*) buf, len);

	return (int) (len - s->stream.avail_in);
}
