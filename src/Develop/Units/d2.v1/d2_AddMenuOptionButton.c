extern char d2_Controls[];


int __cdecl d2_AddWindowTextButton(int, int, int, int, int);
void __cdecl d2_SetElementWidth(int, int);

/* ADDRESS: GOLDDE 0x005c5060 */
int __cdecl d2_AddMenuOptionButton(int a, int b, int c)
{
	int idx;

	idx = d2_AddWindowTextButton(0x20, a * 46 + 10, 0xbf, b, c);
	*(int*) (*(char**) &d2_Controls + idx * 0x2f4 + 0x6c) = 1;
	d2_SetElementWidth(idx, 300);
	return idx;
}
