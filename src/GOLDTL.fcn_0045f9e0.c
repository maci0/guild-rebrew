// FUNCTION: GOLD 0x004635e0
// SIZE: 112
// FUNCTION: GOLDTL 0x45f9e0
// SIZE: 112

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdarg.h>
#include "zutil.h"
#include "Develop/Units/vfs/gz_stream.h"

int __cdecl fcn_0045f9e0(gzFile file)
{
	gz_stream* s = (gz_stream*) file;

	if (s == NULL || s->mode != 'r') {
		return -1;
	}
	s->z_err = Z_OK;
	s->z_eof = 0;
	s->stream.avail_in = 0;
	s->stream.next_in = s->inbuf;
	s->crc = crc32(0L, Z_NULL, 0);

	if (s->startpos == 0) {
		rewind(s->file);
		return 0;
	}
	(void) inflateReset(&s->stream);
	return fseek(s->file, s->startpos, SEEK_SET);
}
