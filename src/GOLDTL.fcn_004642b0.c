// FUNCTION: GOLDTL 0x4642b0
// SIZE: 116

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

void __cdecl fcn_004642b0(deflate_state* s)
{
	int n = 0;
	unsigned ascii_freq = 0;
	unsigned bin_freq = 0;

	while (n < 7) {
		bin_freq += s->dyn_ltree[n++].Freq;
	}
	while (n < 128) {
		ascii_freq += s->dyn_ltree[n++].Freq;
	}
	while (n < LITERALS) {
		bin_freq += s->dyn_ltree[n++].Freq;
	}
	s->data_type = (Byte) (bin_freq > (ascii_freq >> 2) ? Z_BINARY : Z_ASCII);
}
