// FUNCTION: GOLDTL 0x463df0

#include "deflate.h"

#define END_BLOCK 256
#define REP_3_6 16
#define REPZ_3_10 17
#define REPZ_11_138 18
#define Buf_size (8 * 2 * sizeof(char))
#define SMALLEST 1

#define put_short(s, w) \
	{ \
		put_byte(s, (uch) ((w) &0xff)); \
		put_byte(s, (uch) ((ush) (w) >> 8)); \
	}

#define send_bits(s, value, length) \
	{ \
		int len = length; \
		if (s->bi_valid > (int) Buf_size - len) { \
			int val = value; \
			s->bi_buf |= (val << s->bi_valid); \
			put_short(s, s->bi_buf); \
			s->bi_buf = (ush) val >> (Buf_size - s->bi_valid); \
			s->bi_valid += len - Buf_size; \
		} else { \
			s->bi_buf |= (value) << s->bi_valid; \
			s->bi_valid += len; \
		} \
	}

#define smaller(tree, n, m, depth) (tree[n].Freq < tree[m].Freq || (tree[n].Freq == tree[m].Freq && depth[n] <= depth[m]))

int __cdecl fcn_00463df0(deflate_state* s, unsigned dist, unsigned lc)
{
	s->d_buf[s->last_lit] = (ush) dist;
	s->l_buf[s->last_lit++] = (uch) lc;
	if (dist == 0) {
		s->dyn_ltree[lc].Freq++;
	} else {
		s->matches++;
		dist--;
		s->dyn_ltree[_length_code[lc] + LITERALS + 1].Freq++;
		s->dyn_dtree[d_code(dist)].Freq++;
	}
	return (s->last_lit == s->lit_bufsize - 1);
}
