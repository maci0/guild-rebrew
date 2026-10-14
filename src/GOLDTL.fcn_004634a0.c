


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

unsigned __cdecl fcn_00464330(unsigned, int);

void __cdecl fcn_004634a0(ct_data* tree, int max_code, ushf* bl_count)
{
	ush next_code[MAX_BITS + 1];
	ush code = 0;
	int bits;
	int n;

	for (bits = 1; bits <= MAX_BITS; bits++) {
		next_code[bits] = code = (code + bl_count[bits - 1]) << 1;
	}
	for (n = 0; n <= max_code; n++) {
		int len = tree[n].Len;
		if (len == 0) {
			continue;
		}
		tree[n].Code = fcn_00464330(next_code[len]++, len);
	}
}
