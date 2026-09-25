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

#define DIST_CODE_LEN 512

#include "trees.h"

void __cdecl fcn_004642b0(deflate_state* s);
void __cdecl fcn_00462f90(deflate_state* s, tree_desc* desc);
int __cdecl fcn_00463520(deflate_state* s);
void __cdecl fcn_00462af0(deflate_state* s, charf* buf, ulg stored_len, int eof);
void __cdecl fcn_00463ea0(deflate_state* s, ct_data* ltree, ct_data* dtree);
void __cdecl fcn_00463680(deflate_state* s, int lcodes, int dcodes, int blcodes);
void __cdecl fcn_00462a80(deflate_state* s);
void __cdecl fcn_004643e0(deflate_state* s);

// FUNCTION: GOLDTL 0x462da0
// SIZE: 486
void __cdecl fcn_00462da0(deflate_state* s, charf* buf, ulg stored_len, int eof)
{
	ulg opt_lenb, static_lenb;
	int max_blindex = 0;

	if (s->level > 0) {

		if (s->data_type == Z_UNKNOWN) {
			fcn_004642b0(s);
		}

		fcn_00462f90(s, (tree_desc*) (&(s->l_desc)));

		fcn_00462f90(s, (tree_desc*) (&(s->d_desc)));

		max_blindex = fcn_00463520(s);

		opt_lenb = (s->opt_len + 3 + 7) >> 3;
		static_lenb = (s->static_len + 3 + 7) >> 3;

		if (static_lenb <= opt_lenb) {
			opt_lenb = static_lenb;
		}

	} else {
		opt_lenb = static_lenb = stored_len + 5;
	}

	if (stored_len + 4 <= opt_lenb && buf != (char*) 0) {
		fcn_00462af0(s, buf, stored_len, eof);

	} else if (static_lenb == opt_lenb) {
		send_bits(s, (STATIC_TREES << 1) + eof, 3);
		fcn_00463ea0(s, (ct_data*) static_ltree, (ct_data*) static_dtree);
	} else {
		send_bits(s, (DYN_TREES << 1) + eof, 3);
		fcn_00463680(s, s->l_desc.max_code + 1, s->d_desc.max_code + 1, max_blindex + 1);
		fcn_00463ea0(s, (ct_data*) s->dyn_ltree, (ct_data*) s->dyn_dtree);
	}
	fcn_00462a80(s);

	if (eof) {
		fcn_004643e0(s);
	}
}
