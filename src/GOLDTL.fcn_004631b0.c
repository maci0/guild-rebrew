// FUNCTION: GOLDTL 0x4631b0
// SIZE: 209

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

void __cdecl fcn_004631b0(deflate_state* s, ct_data* tree, int k)
{
	int v = s->heap[k];
	int j = k << 1;

	while (j <= s->heap_len) {
		if (j < s->heap_len && smaller(tree, s->heap[j + 1], s->heap[j], s->depth)) {
			j++;
		}
		if (smaller(tree, v, s->heap[j], s->depth)) {
			break;
		}
		s->heap[k] = s->heap[j];
		k = j;
		j <<= 1;
	}
	s->heap[k] = v;
}
