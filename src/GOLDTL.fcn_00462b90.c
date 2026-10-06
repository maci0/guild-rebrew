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

#define send_code(s, c, tree) send_bits(s, tree[c].Code, tree[c].Len)

#define DIST_CODE_LEN 512

#include "trees.h"

void __cdecl fcn_00464350(deflate_state* s);

// FUNCTION: GOLD 0x00465f70
// FUNCTION: GOLDTL 0x462b90
void __cdecl fcn_00462b90(deflate_state* s)
{
	send_bits(s, STATIC_TREES << 1, 3);
	send_code(s, END_BLOCK, static_ltree);
	fcn_00464350(s);
	if (1 + s->last_eob_len + 10 - s->bi_valid < 9) {
		send_bits(s, STATIC_TREES << 1, 3);
		send_code(s, END_BLOCK, static_ltree);
		fcn_00464350(s);
	}
	s->last_eob_len = 7;
}
