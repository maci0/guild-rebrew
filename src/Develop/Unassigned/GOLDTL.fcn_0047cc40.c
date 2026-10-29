// SIZE 0x1c
typedef struct {
	char pad0[0x18];
	int* items;
} fcn_0047cc40_set;

int __cdecl fcn_0047bdd0(int, int, int, float, unsigned char, unsigned char, unsigned char);


/* ADDRESS: GOLDTL 0x0047cc40 */
int __cdecl fcn_0047cc40(int a1, int a2, int a3, fcn_0047cc40_set* s, int idx, float scale)
{
	if (s == 0)
		return 0;
	return fcn_0047bdd0(a1, a2, s->items[idx], scale, 0xc8, 0xc8, 0xc8);
}
