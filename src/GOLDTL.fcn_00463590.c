// FUNCTION: GOLDTL 0x463590
// SIZE: 231

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

void __cdecl fcn_00463590(deflate_state* s, ct_data* tree, int max_code)
{
	int n;
	int prevlen = -1;
	int curlen;
	int nextlen = tree[0].Len;
	int count = 0;
	int max_count = 7;
	int min_count = 4;

	if (nextlen == 0) {
		max_count = 138, min_count = 3;
	}
	tree[max_code + 1].Len = (ush) 0xffff;

	for (n = 0; n <= max_code; n++) {
		curlen = nextlen;
		nextlen = tree[n + 1].Len;
		if (++count < max_count && curlen == nextlen) {
			continue;
		} else if (count < min_count) {
			s->bl_tree[curlen].Freq += count;
		} else if (curlen != 0) {
			if (curlen != prevlen) {
				s->bl_tree[curlen].Freq++;
			}
			s->bl_tree[REP_3_6].Freq++;
		} else if (count <= 10) {
			s->bl_tree[REPZ_3_10].Freq++;
		} else {
			s->bl_tree[REPZ_11_138].Freq++;
		}
		count = 0;
		prevlen = curlen;
		if (nextlen == 0) {
			max_count = 138, min_count = 3;
		} else if (curlen == nextlen) {
			max_count = 6, min_count = 3;
		} else {
			max_count = 7, min_count = 4;
		}
	}
}
