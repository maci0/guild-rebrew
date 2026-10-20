#include "deflate.h"

typedef enum { need_more, block_done, finish_started, finish_done } block_state;

typedef block_state (*compress_func)(deflate_state* s, int flush);

/* SIZE 0xc */
typedef struct config_s {
	ush good_length;
	ush max_lazy;
	ush nice_length;
	ush max_chain;
	compress_func func;
} config;

extern config g_663310[10];

void __cdecl fcn_0045de70(deflate_state* s, uInt b);
void __cdecl fcn_0045dea0(z_streamp strm);
void __cdecl fcn_00462af0(deflate_state* s, charf* buf, ulg stored_len, int eof);
void __cdecl fcn_00462b90(deflate_state* s);

#define ERR_RETURN(strm, err) \
	return (strm->msg = (char*) ERR_MSG(err), (err))

/* ADDRESS: GOLDTL 0x0045dbc0 */
int __cdecl fcn_0045dbc0(z_streamp strm, int flush)
{
	int old_flush;
	deflate_state* s;
	block_state bstate;
	uInt header;
	uInt level_flags;

	if (strm == Z_NULL || strm->state == Z_NULL ||
		flush > Z_FINISH || flush < 0) {
		return Z_STREAM_ERROR;
	}
	s = strm->state;

	if (strm->next_out == Z_NULL ||
		(strm->next_in == Z_NULL && strm->avail_in != 0) ||
		(s->status == FINISH_STATE && flush != Z_FINISH)) {
		ERR_RETURN(strm, Z_STREAM_ERROR);
	}
	if (strm->avail_out == 0) ERR_RETURN(strm, Z_BUF_ERROR);

	s->strm = strm;
	old_flush = s->last_flush;
	s->last_flush = flush;

	if (s->status == INIT_STATE) {
		header = (Z_DEFLATED + ((s->w_bits - 8) << 4)) << 8;
		level_flags = (s->level - 1) >> 1;

		if (level_flags > 3) level_flags = 3;
		header |= (level_flags << 6);
		if (s->strstart != 0) header |= PRESET_DICT;
		header += 31 - (header % 31);

		s->status = BUSY_STATE;
		fcn_0045de70(s, header);

		if (s->strstart != 0) {
			fcn_0045de70(s, (uInt) (strm->adler >> 16));
			fcn_0045de70(s, (uInt) (strm->adler & 0xffff));
		}
		strm->adler = 1L;
	}

	if (s->pending != 0) {
		fcn_0045dea0(strm);
		if (strm->avail_out == 0) {
			s->last_flush = -1;
			return Z_OK;
		}
	} else if (strm->avail_in == 0 && flush <= old_flush &&
			   flush != Z_FINISH) {
		ERR_RETURN(strm, Z_BUF_ERROR);
	}

	if (s->status == FINISH_STATE && strm->avail_in != 0) {
		ERR_RETURN(strm, Z_BUF_ERROR);
	}

	if (strm->avail_in != 0 || s->lookahead != 0 ||
		(flush != Z_NO_FLUSH && s->status != FINISH_STATE)) {
		bstate = g_663310[s->level].func(s, flush);

		if (bstate == finish_started || bstate == finish_done) {
			s->status = FINISH_STATE;
		}
		if (bstate == need_more || bstate == finish_started) {
			if (strm->avail_out == 0) {
				s->last_flush = -1;
			}
			return Z_OK;
		}
		if (bstate == block_done) {
			if (flush == Z_PARTIAL_FLUSH) {
				fcn_00462b90(s);
			} else {
				fcn_00462af0(s, (charf*) 0, 0L, 0);
				if (flush == Z_FULL_FLUSH) {
					s->head[s->hash_size - 1] = 0;
					zmemzero((Bytef*) s->head,
							 (unsigned) (s->hash_size - 1) * sizeof(*s->head));
				}
			}
			fcn_0045dea0(strm);
			if (strm->avail_out == 0) {
				s->last_flush = -1;
				return Z_OK;
			}
		}
	}

	if (flush != Z_FINISH) return Z_OK;
	if (s->noheader) return Z_STREAM_END;

	fcn_0045de70(s, (uInt) (strm->adler >> 16));
	fcn_0045de70(s, (uInt) (strm->adler & 0xffff));
	fcn_0045dea0(strm);

	s->noheader = -1;
	return s->pending != 0 ? Z_OK : Z_STREAM_END;
}
