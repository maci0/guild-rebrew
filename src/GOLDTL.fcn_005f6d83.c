typedef struct Node5f6d83
{
	int k0;
	int k4;
	int pad8;
	int kc;
	struct Node5f6d83* next;
} Node5f6d83;

typedef struct Key5f6d83
{
	int k0;
	int k4;
	int kc;
} Key5f6d83;

/* D3DX8 external band. Native keeps an EBP frame and walks one bucket of a
 * chained hash table, comparing kc, k4 then k0, and splices the matching node
 * out. Remaining delta: the native body reloads key.k4 and key.kc from the
 * argument slots on every iteration (mov edi,[eax+0xc]; cmp edi,[ebp+0x10]),
 * while this build hoists both into ebx/edi and pushes ebx; 3 of 78 bytes
 * agree. Declaration order, loop form, pointer key access and volatile access
 * all measured identical. */
#pragma optimize("y", off)

/* ADDRESS: GOLDTL 0x005f6d83 */
void __cdecl fcn_005f6d83(Key5f6d83 key, Node5f6d83** tab, unsigned int n)
{
	Node5f6d83** bucket = &tab[key.k0 % n];
	Node5f6d83* node = *bucket;
	Node5f6d83* prev = 0;
	Node5f6d83* next;

	while (node != 0) {
		if (node->kc == key.kc && node->k4 == key.k4 && node->k0 == key.k0) {
			next = node->next;
			if (prev != 0) {
				prev->next = next;
			} else {
				*bucket = next;
			}
			return;
		}
		prev = node;
		node = node->next;
	}
}
