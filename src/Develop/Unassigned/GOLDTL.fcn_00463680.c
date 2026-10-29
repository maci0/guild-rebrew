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

extern const uch g_663734[BL_CODES];

void __cdecl fcn_004638d0(deflate_state* s, ct_data* tree, int max_code);

/* ADDRESS: GOLDTL 0x00463680 */
void __cdecl fcn_00463680(deflate_state* s, int lcodes, int dcodes, int blcodes)
{
	int rank;

	send_bits(s, lcodes - 257, 5);
	send_bits(s, dcodes - 1, 5);
	send_bits(s, blcodes - 4, 4);
	for (rank = 0; rank < blcodes; rank++) {
		send_bits(s, s->bl_tree[g_663734[rank]].Len, 3);
	}

	fcn_004638d0(s, (ct_data*) s->dyn_ltree, lcodes - 1);

	fcn_004638d0(s, (ct_data*) s->dyn_dtree, dcodes - 1);
}
