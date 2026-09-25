// FUNCTION: GOLDTL 0x45df20
// SIZE: 170

#include "deflate.h"

int __cdecl fcn_0045df20(z_streamp strm)
{
	int status;

	if (strm == Z_NULL || strm->state == Z_NULL) {
		return Z_STREAM_ERROR;
	}

	status = strm->state->status;
	if (status != INIT_STATE && status != BUSY_STATE && status != FINISH_STATE) {
		return Z_STREAM_ERROR;
	}

	TRY_FREE(strm, strm->state->pending_buf);
	TRY_FREE(strm, strm->state->head);
	TRY_FREE(strm, strm->state->prev);
	TRY_FREE(strm, strm->state->window);

	ZFREE(strm, strm->state);
	strm->state = Z_NULL;

	return status == BUSY_STATE ? Z_DATA_ERROR : Z_OK;
}
