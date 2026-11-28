void __cdecl d2_BlitShape(int, int, int, char*);
void __cdecl d2_BlitShape(int, int, int, char*);

/* ADDRESS: GOLDTL 0x00479ed0 */
int __cdecl shp_ShowShapeFromBankRle(int x, int y, int surface, char* h, int idx)
{
	char* e;
	char save;

	if (idx > *(unsigned short*) (h + 0x2a))
		return 0;
	e = h + *(int*) (h + idx * 4 + 0x45);
	save = e[0xd];
	e[0xd] = 1;
	d2_BlitShape(x, y, surface, h + *(int*) (h + idx * 4 + 0x45));
	e[0xd] = save;
	return 1;
}

/* ADDRESS: GOLDTL 0x00479f20 */
int __cdecl fcn_00479f20(int x, int y, int surface, char* h, int idx)
{
	char* e;
	char save;

	if (idx > *(unsigned short*) (h + 0x2a))
		return 0;
	e = h + *(int*) (h + idx * 4 + 0x45);
	save = e[0xd];
	e[0xd] = 3;
	d2_BlitShape(x, y, surface, h + *(int*) (h + idx * 4 + 0x45));
	e[0xd] = save;
	return 1;
}
