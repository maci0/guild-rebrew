#include "deflate.h"

uLong __cdecl fcn_0045d3f0(uLong adler, const Bytef* buf, uInt len);

// FUNCTION: GOLDTL 0x45d970
// SIZE: 247
int __cdecl fcn_0045d970(z_streamp strm, const Bytef* dictionary, uInt dictLength)
{
	deflate_state* s;
	uInt length = dictLength;
	uInt n;
	IPos hash_head = 0;

	if (strm == Z_NULL || strm->state == Z_NULL || dictionary == Z_NULL || strm->state->status != INIT_STATE) {
		return Z_STREAM_ERROR;
	}

	s = strm->state;
	strm->adler = fcn_0045d3f0(strm->adler, dictionary, dictLength);

	if (length < MIN_MATCH) {
		return Z_OK;
	}
	if (length > MAX_DIST(s)) {
		length = MAX_DIST(s);
		dictionary += dictLength - length;
	}
	zmemcpy(s->window, dictionary, length);
	s->strstart = length;
	s->block_start = (long) length;

	s->ins_h = s->window[0];
	s->ins_h = ((s->ins_h << s->hash_shift) ^ (s->window[1])) & s->hash_mask;
	for (n = 0; n <= length - MIN_MATCH; n++) {
		s->ins_h = ((s->ins_h << s->hash_shift) ^ (s->window[n + (MIN_MATCH - 1)])) & s->hash_mask;
		s->prev[n & s->w_mask] = hash_head = s->head[s->ins_h];
		s->head[s->ins_h] = (Pos) n;
	}
	if (hash_head) {
		hash_head = 0;
	}
	return Z_OK;
}
