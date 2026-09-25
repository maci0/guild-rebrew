#include "deflate.h"

#define SMALLEST 1
#define MAX(a, b) (a >= b ? a : b)

struct static_tree_desc_s {
	const ct_data* static_tree;
	const intf* extra_bits;
	int extra_base;
	int elems;
	int max_length;
};
// SIZE 0x14

void __cdecl fcn_004631b0(deflate_state* s, ct_data* tree, int k);
void __cdecl fcn_00463290(deflate_state* s, tree_desc* desc);
void __cdecl fcn_004634a0(ct_data* tree, int max_code, ushf* bl_count);

#define pqremove(s, tree, top) \
	{ \
		top = s->heap[SMALLEST]; \
		s->heap[SMALLEST] = s->heap[s->heap_len--]; \
		fcn_004631b0(s, tree, SMALLEST); \
	}

// FUNCTION: GOLDTL 0x462f90
// SIZE: 537
void __cdecl fcn_00462f90(deflate_state* s, tree_desc* desc)
{
	ct_data* tree = desc->dyn_tree;
	const ct_data* stree = desc->stat_desc->static_tree;
	int elems = desc->stat_desc->elems;
	int n, m;
	int max_code = -1;
	int node;

	s->heap_len = 0, s->heap_max = HEAP_SIZE;

	for (n = 0; n < elems; n++) {
		if (tree[n].Freq != 0) {
			s->heap[++(s->heap_len)] = max_code = n;
			s->depth[n] = 0;
		} else {
			tree[n].Len = 0;
		}
	}

	while (s->heap_len < 2) {
		node = s->heap[++(s->heap_len)] = (max_code < 2 ? ++max_code : 0);
		tree[node].Freq = 1;
		s->depth[node] = 0;
		s->opt_len--;
		if (stree) {
			s->static_len -= stree[node].Len;
		}
	}
	desc->max_code = max_code;

	for (n = s->heap_len / 2; n >= 1; n--) {
		fcn_004631b0(s, tree, n);
	}

	node = elems;
	do {
		pqremove(s, tree, n);
		m = s->heap[SMALLEST];

		s->heap[--(s->heap_max)] = n;
		s->heap[--(s->heap_max)] = m;

		tree[node].Freq = tree[n].Freq + tree[m].Freq;
		s->depth[node] = (uch) (MAX(s->depth[n], s->depth[m]) + 1);
		tree[n].Dad = tree[m].Dad = (ush) node;
		s->heap[SMALLEST] = node++;
		fcn_004631b0(s, tree, SMALLEST);

	} while (s->heap_len >= 2);

	s->heap[--(s->heap_max)] = s->heap[SMALLEST];

	fcn_00463290(s, (tree_desc*) desc);

	fcn_004634a0((ct_data*) tree, max_code, s->bl_count);
}
