#include "deflate.h"

#define NIL 0
#define MIN_LOOKAHEAD (MAX_MATCH + MIN_MATCH + 1)
#define UPDATE_HASH(s, h, c) (h = (((h) << s->hash_shift) ^ (c)) & s->hash_mask)

int __cdecl fcn_0045e4a0(z_streamp strm, Bytef* buf, unsigned size);

// FUNCTION: GOLDTL 0x45e370
// SIZE: 290
void __cdecl fcn_0045e370(deflate_state* s)
{
	register unsigned n, m;
	register Posf* p;
	unsigned more;
	uInt wsize = s->w_size;

	do {
		more = (unsigned) (s->window_size - (ulg) s->lookahead - (ulg) s->strstart);

		if (more == 0 && s->strstart == 0 && s->lookahead == 0) {
			more = wsize;

		} else if (more == (unsigned) (-1)) {
			more--;

		} else if (s->strstart >= wsize + MAX_DIST(s)) {

			zmemcpy(s->window, s->window + wsize, (unsigned) wsize);
			s->match_start -= wsize;
			s->strstart -= wsize;
			s->block_start -= (long) wsize;

			n = s->hash_size;
			p = &s->head[n];
			do {
				m = *--p;
				*p = (Pos) (m >= wsize ? m - wsize : NIL);
			} while (--n);

			n = wsize;
			p = &s->prev[n];
			do {
				m = *--p;
				*p = (Pos) (m >= wsize ? m - wsize : NIL);
			} while (--n);
			more += wsize;
		}
		if (s->strm->avail_in == 0) {
			return;
		}

		n = fcn_0045e4a0(s->strm, s->window + s->strstart + s->lookahead, more);
		s->lookahead += n;

		if (s->lookahead >= MIN_MATCH) {
			s->ins_h = s->window[s->strstart];
			UPDATE_HASH(s, s->ins_h, s->window[s->strstart + 1]);
		}

	} while (s->lookahead < MIN_LOOKAHEAD && s->strm->avail_in != 0);
}
