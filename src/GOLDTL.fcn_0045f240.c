// FUNCTION: GOLDTL 0x45f240
// SIZE: 114

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdarg.h>
#include "zutil.h"
#include "Develop/Units/vfs/gz_stream.h"

#define Z_BUFSIZE 16384

int __cdecl fcn_0045f240(gz_stream* s)
{
	if (s->z_eof) {
		return EOF;
	}
	if (s->stream.avail_in == 0) {
		errno = 0;
		s->stream.avail_in = fread(s->inbuf, 1, Z_BUFSIZE, s->file);
		if (s->stream.avail_in == 0) {
			s->z_eof = 1;
			if (ferror(s->file)) {
				s->z_err = Z_ERRNO;
			}
			return EOF;
		}
		s->stream.next_in = s->inbuf;
	}
	s->stream.avail_in--;
	return *(s->stream.next_in)++;
}
