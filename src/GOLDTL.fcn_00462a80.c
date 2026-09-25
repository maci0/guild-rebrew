// FUNCTION: GOLDTL 0x462a80
// SIZE: 102

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

void __cdecl fcn_00462a80(deflate_state* s)
{
	int n;

	for (n = 0; n < L_CODES; n++) {
		s->dyn_ltree[n].Freq = 0;
	}
	for (n = 0; n < D_CODES; n++) {
		s->dyn_dtree[n].Freq = 0;
	}
	for (n = 0; n < BL_CODES; n++) {
		s->bl_tree[n].Freq = 0;
	}
	s->dyn_ltree[END_BLOCK].Freq = 1;
	s->opt_len = s->static_len = 0L;
	s->last_lit = s->matches = 0;
}
