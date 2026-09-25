// FUNCTION: GOLDTL 0x45e4a0
// SIZE: 113

#include "deflate.h"

int __cdecl fcn_0045e4a0(z_streamp strm, Bytef* buf, unsigned size)
{
	unsigned len = strm->avail_in;

	if (len > size) {
		len = size;
	}
	if (len == 0) {
		return 0;
	}

	strm->avail_in -= len;

	if (!strm->state->noheader) {
		strm->adler = adler32(strm->adler, strm->next_in, len);
	}
	zmemcpy(buf, strm->next_in, len);
	strm->next_in += len;
	strm->total_in += len;

	return (int) len;
}
