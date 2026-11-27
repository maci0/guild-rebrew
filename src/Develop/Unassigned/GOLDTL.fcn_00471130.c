int __cdecl d2_LoadForm(int a, int b, int c);
void __cdecl fcn_00471d80(int r, int n);

/* ADDRESS: GOLDTL 0x00471130 */
int __cdecl d2_OpenForm(short a, short b, int c)
{
	int r;

	r = d2_LoadForm(a, b, c);
	if (r != -1) {
		fcn_00471d80(r, 3);
	}
	return r;
}
