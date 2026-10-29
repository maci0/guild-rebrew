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

struct static_tree_desc_s {
	const ct_data* static_tree;
	const intf* extra_bits;
	int extra_base;
	int elems;
	int max_length;
};
// SIZE 0x14

/* ADDRESS: GOLDTL 0x00463290 */
void __cdecl fcn_00463290(deflate_state* s, tree_desc* desc)
{
	ct_data* tree = desc->dyn_tree;
	int max_code = desc->max_code;
	const ct_data* stree = desc->stat_desc->static_tree;
	const intf* extra = desc->stat_desc->extra_bits;
	int base = desc->stat_desc->extra_base;
	int max_length = desc->stat_desc->max_length;
	int h;
	int n, m;
	int bits;
	int xbits;
	ush f;
	int overflow = 0;

	for (bits = 0; bits <= MAX_BITS; bits++) {
		s->bl_count[bits] = 0;
	}

	tree[s->heap[s->heap_max]].Len = 0;

	for (h = s->heap_max + 1; h < HEAP_SIZE; h++) {
		n = s->heap[h];
		bits = tree[tree[n].Dad].Len + 1;
		if (bits > max_length) {
			bits = max_length, overflow++;
		}
		tree[n].Len = (ush) bits;

		if (n > max_code) {
			continue;
		}

		s->bl_count[bits]++;
		xbits = 0;
		if (n >= base) {
			xbits = extra[n - base];
		}
		f = tree[n].Freq;
		s->opt_len += (ulg) f * (bits + xbits);
		if (stree) {
			s->static_len += (ulg) f * (stree[n].Len + xbits);
		}
	}
	if (overflow == 0) {
		return;
	}

	do {
		bits = max_length - 1;
		while (s->bl_count[bits] == 0) {
			bits--;
		}
		s->bl_count[bits]--;
		s->bl_count[bits + 1] += 2;
		s->bl_count[max_length]--;
		overflow -= 2;
	} while (overflow > 0);

	for (bits = max_length; bits != 0; bits--) {
		n = s->bl_count[bits];
		while (n != 0) {
			m = s->heap[--h];
			if (m > max_code) {
				continue;
			}
			if (tree[m].Len != (unsigned) bits) {
				s->opt_len += ((long) bits - (long) tree[m].Len) * (long) tree[m].Freq;
				tree[m].Len = (ush) bits;
			}
			n--;
		}
	}
}
