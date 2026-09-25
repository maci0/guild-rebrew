#include <stdio.h>
#include "zutil.h"
#include "Develop/Units/vfs/gz_stream.h"

#define HEAD_CRC 0x02
#define EXTRA_FIELD 0x04
#define ORIG_NAME 0x08
#define COMMENT 0x10
#define RESERVED 0xE0

extern int g_67bd70[2];

int __cdecl fcn_0045f240(gz_stream* s);

// FUNCTION: GOLDTL 0x45f110
// SIZE: 294
void __cdecl fcn_0045f110(gz_stream* s)
{
	int method;
	int flags;
	uInt len;
	int c;

	for (len = 0; len < 2; len++) {
		c = fcn_0045f240(s);
		if (c != g_67bd70[len]) {
			if (len != 0) {
				s->stream.avail_in++, s->stream.next_in--;
			}
			if (c != EOF) {
				s->stream.avail_in++, s->stream.next_in--;
				s->transparent = 1;
			}
			s->z_err = s->stream.avail_in != 0 ? Z_OK : Z_STREAM_END;
			return;
		}
	}
	method = fcn_0045f240(s);
	flags = fcn_0045f240(s);
	if (method != Z_DEFLATED || (flags & RESERVED) != 0) {
		s->z_err = Z_DATA_ERROR;
		return;
	}

	for (len = 0; len < 6; len++) {
		(void) fcn_0045f240(s);
	}

	if ((flags & EXTRA_FIELD) != 0) {
		len = (uInt) fcn_0045f240(s);
		len += ((uInt) fcn_0045f240(s)) << 8;
		while (len-- != 0 && fcn_0045f240(s) != EOF) {
		}
	}
	if ((flags & ORIG_NAME) != 0) {
		while ((c = fcn_0045f240(s)) != 0 && c != EOF) {
		}
	}
	if ((flags & COMMENT) != 0) {
		while ((c = fcn_0045f240(s)) != 0 && c != EOF) {
		}
	}
	if ((flags & HEAD_CRC) != 0) {
		for (len = 0; len < 2; len++) {
			(void) fcn_0045f240(s);
		}
	}
	s->z_err = s->z_eof ? Z_DATA_ERROR : Z_OK;
}
