#pragma optimize("s", on)

typedef struct Node5f6dd1 {
	int key0;
	int key1;
	int f08;
	int f0c;
	struct Node5f6dd1* next;
} Node5f6dd1;

float __cdecl fcn_005f6eaf(int a, int b, int c, int d, int e, int f, int g,
	int h);

#pragma optimize("y", off)

/* ADDRESS: GOLDTL 0x005f6dd1 */
int __cdecl fcn_005f6dd1(int k0, int k1, int a3, Node5f6dd1** table,
	int buckets, int a6, int a7, int a8)
{
	Node5f6dd1** slot;
	Node5f6dd1* node;
	Node5f6dd1* prev;
	Node5f6dd1* cur;
	Node5f6dd1* parent;
	Node5f6dd1* found;
	int m;
	int i;
	float best;
	float f;

	slot = &table[k0 % buckets];
	m = a6;
	node = *slot;
	prev = 0;
	for (;;) {
		if (node == 0) {
			break;
		}
		if (node->key1 == k1 && node->key0 == k0) {
			m = node->f0c;
			break;
		}
		prev = node;
		node = node->next;
	}
	found = node;
	if (node != 0) {
		cur = node->next;
		parent = node;
		while (cur != 0) {
			if (cur->key1 == k1 && cur->key0 == k0) {
				best = fcn_005f6eaf(found->key0, found->key1,
				    found->f08, k1, k0, a3, a7, a8);
				f = fcn_005f6eaf(cur->key0, cur->key1, cur->f08,
				    k0, k1, a3, a7, a8);
				if (f > best) {
					prev = parent;
					m = cur->f0c;
					found = cur;
				}
			}
			parent = cur;
			cur = cur->next;
		}
	}
	if (m != a6) {
		if (prev != 0) {
			prev->next = found->next;
		} else {
			*slot = found->next;
		}
	}
	return m;
}
