// SIZE 0x1c
typedef struct {
	char pad0[0x18];
	int* items;
} fcn_0047ccd0_set;

int __cdecl fcn_0047bdd0(int, int, int, float, unsigned char, unsigned char, unsigned char);


/* ADDRESS: GOLDTL 0x0047ccd0 */
int __cdecl fcn_0047ccd0(int a1, int a2, int a3, fcn_0047ccd0_set* s, int idx)
{
	if (s == 0)
		return 0;
	return fcn_0047bdd0(a1, a2, s->items[idx], 1.0f, 0xff, 0xff, 0xff) != 0;
}
