// FUNCTION: GOLDTL 0x45da70
// SIZE: 115

#include "deflate.h"

void __cdecl fcn_0045e180(deflate_state*);

int __cdecl fcn_0045da70(z_streamp strm)
{
	deflate_state* s;

	if (strm == Z_NULL || strm->state == Z_NULL || strm->zalloc == Z_NULL || strm->zfree == Z_NULL) {
		return Z_STREAM_ERROR;
	}
	strm->total_in = strm->total_out = 0;
	strm->msg = Z_NULL;
	strm->data_type = Z_UNKNOWN;

	s = (deflate_state*) strm->state;
	s->pending = 0;
	s->pending_out = s->pending_buf;

	if (s->noheader < 0) {
		s->noheader = 0;
	}
	s->status = s->noheader ? BUSY_STATE : INIT_STATE;
	strm->adler = 1;
	s->last_flush = Z_NO_FLUSH;

	_tr_init(s);
	fcn_0045e180(s);
	return Z_OK;
}
