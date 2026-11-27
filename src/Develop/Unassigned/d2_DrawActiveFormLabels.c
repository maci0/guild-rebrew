int __cdecl d2_SelectFont(int);
int __cdecl d2_DrawWordWrappedText(int, int, int, int, int, int, int);

/* ADDRESS: GOLDTL 0x00532b40 */
void __cdecl d2_DrawActiveFormLabels(void)
{
	int rec;
	int idx;
	int v;
	int* tbl;

	d2_SelectFont(0x54);
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
		d2_DrawWordWrappedText(*(int*) (0x1015f44 + idx), *(int*) (0x1015f48 + idx) - 0x14,
			0xa0, 0x60, *(int*) 0x77250c, rec + 0x230, 0x20);
	}
}
