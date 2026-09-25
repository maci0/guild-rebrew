// FUNCTION: GOLDTL 0x463520
// SIZE: 111

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

void __cdecl fcn_00463590(deflate_state*, ct_data*, int);
void __cdecl fcn_00462f90(deflate_state*, tree_desc*);

int __cdecl fcn_00463520(deflate_state* s)
{
	int max_blindex;

	fcn_00463590(s, (ct_data*) s->dyn_ltree, s->l_desc.max_code);
	fcn_00463590(s, (ct_data*) s->dyn_dtree, s->d_desc.max_code);
	fcn_00462f90(s, (tree_desc*) (&(s->bl_desc)));

	for (max_blindex = BL_CODES - 1; max_blindex >= 3; max_blindex--) {
		if (s->bl_tree[g_663734[max_blindex]].Len != 0) {
			break;
		}
	}
	s->opt_len += 3 * (max_blindex + 1) + 5 + 5 + 4;
	return max_blindex;
}
