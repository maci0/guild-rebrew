// FUNCTION: GOLDTL 0x45f0a0

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdarg.h>
#include "zutil.h"
#include "Develop/Units/vfs/gz_stream.h"

#define Z_BUFSIZE 16384

int __cdecl fcn_0045f0a0(gzFile file, int level, int strategy)
{
	gz_stream* s = (gz_stream*) file;

	if (s == NULL || s->mode != 'w') {
		return Z_STREAM_ERROR;
	}
	if (s->stream.avail_out == 0) {
		s->stream.next_out = s->outbuf;
		if (fwrite(s->outbuf, 1, Z_BUFSIZE, s->file) != Z_BUFSIZE) {
			s->z_err = Z_ERRNO;
		}
		s->stream.avail_out = Z_BUFSIZE;
	}
	return deflateParams(&(s->stream), level, strategy);
}
