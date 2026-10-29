void __cdecl fcn_00471c00(int, int);

/* ADDRESS: GOLDTL 0x00471db0 */
void __cdecl fcn_00471db0(int a0, int a1)
{
	char* base;
	int i;
	int id;
	int t;

	i = 0;
	base = (char*) (0x1038140 + a0 * 0x2bc);
	if (*(int*) (base + 0x184) <= 0)
		return;
	for (; i < *(int*) (base + 0x184); i++) {
		id = *(int*) (base + 4 + i * 4);
		t = *(int*) (0x10161bc + id * 0x3cc);
		if (*(int*) (*(int*) 0x1015ea0 + t * 756 + 0x40) == 0) {
			fcn_00471c00(id, a1);
		}
	}
}
