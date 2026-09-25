#include "deflate.h"

typedef enum { need_more, block_done, finish_started, finish_done } block_state;

void __cdecl fcn_0045e370(deflate_state* s);
void __cdecl fcn_00462da0(deflate_state* s, charf* buf, ulg stored_len, int eof);
void __cdecl fcn_0045dea0(z_streamp strm);

#define FLUSH_BLOCK_ONLY(s, eof) \
	{ \
		fcn_00462da0(s, (s->block_start >= 0L ? (charf*) &s->window[(unsigned) s->block_start] : (charf*) Z_NULL), (ulg) ((long) s->strstart - s->block_start), (eof)); \
		s->block_start = s->strstart; \
		fcn_0045dea0(s->strm); \
	}

#define FLUSH_BLOCK(s, eof) \
	{ \
		FLUSH_BLOCK_ONLY(s, eof); \
		if (s->strm->avail_out == 0) \
			return (eof) ? finish_started : need_more; \
	}

// FUNCTION: GOLDTL 0x45e220
// SIZE: 324
block_state __cdecl fcn_0045e220(deflate_state* s, int flush)
{
	ulg max_block_size = 0xffff;
	ulg max_start;

	if (max_block_size > s->pending_buf_size - 5) {
		max_block_size = s->pending_buf_size - 5;
	}

	for (;;) {
		if (s->lookahead <= 1) {
			fcn_0045e370(s);
			if (s->lookahead == 0 && flush == Z_NO_FLUSH) {
				return need_more;
			}

			if (s->lookahead == 0) {
				break;
			}
		}

		s->strstart += s->lookahead;
		s->lookahead = 0;

		max_start = s->block_start + max_block_size;
		if (s->strstart == 0 || (ulg) s->strstart >= max_start) {
			s->lookahead = (uInt) (s->strstart - max_start);
			s->strstart = (uInt) max_start;
			FLUSH_BLOCK(s, 0);
		}
		if (s->strstart - (uInt) s->block_start >= MAX_DIST(s)) {
			FLUSH_BLOCK(s, 0);
		}
	}
	FLUSH_BLOCK(s, flush == Z_FINISH);
	return flush == Z_FINISH ? finish_done : block_done;
}
