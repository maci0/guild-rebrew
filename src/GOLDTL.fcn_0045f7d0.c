// FUNCTION: GOLD 0x004633d0
// SIZE: 180
// FUNCTION: GOLDTL 0x45f7d0
// SIZE: 180

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdarg.h>
#include "zutil.h"
#include "Develop/Units/vfs/gz_stream.h"

#define Z_BUFSIZE 16384

int __cdecl fcn_0045f7d0(gzFile file, int flush)
{
	uInt len;
	int done = 0;
	gz_stream* s = (gz_stream*) file;

	if (s == NULL || s->mode != 'w') {
		return Z_STREAM_ERROR;
	}
	s->stream.avail_in = 0;

	for (;;) {
		len = Z_BUFSIZE - s->stream.avail_out;

		if (len != 0) {
			if ((uInt) fwrite(s->outbuf, 1, len, s->file) != len) {
				s->z_err = Z_ERRNO;
				return Z_ERRNO;
			}
			s->stream.next_out = s->outbuf;
			s->stream.avail_out = Z_BUFSIZE;
		}
		if (done) {
			break;
		}
		s->z_err = deflate(&(s->stream), flush);

		if (len == 0 && s->z_err == Z_BUF_ERROR) {
			s->z_err = Z_OK;
		}
		done = (s->stream.avail_out != 0 || s->z_err == Z_STREAM_END);

		if (s->z_err != Z_OK && s->z_err != Z_STREAM_END) {
			break;
		}
	}
	return s->z_err == Z_STREAM_END ? Z_OK : s->z_err;
}
