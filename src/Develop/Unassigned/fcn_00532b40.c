int __cdecl fcn_00472880(int);
int __cdecl fcn_0046bd20(int, int, int, int, int, int, int);

/* ADDRESS: GOLDTL 0x00532b40 */
void __cdecl fcn_00532b40(void)
{
	int rec;
	int idx;
	int v;
	int* tbl;

	fcn_00472880(0x54);
	for (rec = 0x1038144; rec < 0x1040484; rec += 0x2bc) {
		if (*(int*) (rec + 0x18c) != 1) {
			continue;
		}
		idx = *(int*) rec * 972;
		v = *(int*) (0x10161bc + idx);
		tbl = (int*) *(int*) 0x1015ea0;
		if (tbl[v * 189 + 18] != 0) {
			continue;
		}
		fcn_0046bd20(*(int*) (0x1015f44 + idx), *(int*) (0x1015f48 + idx) - 0x14,
			0xa0, 0x60, *(int*) 0x77250c, rec + 0x230, 0x20);
	}
}
