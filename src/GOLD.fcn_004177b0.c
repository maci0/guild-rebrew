void __cdecl fcn_004237f0(int *, int);
void __cdecl fcn_00426170(int *, int);

/* ADDRESS: GOLD 0x004177b0 */
void __cdecl fcn_004177b0(char *p)
{
	if (*(int *)(p + 0x34) != 0) {
		fcn_004237f0(*(int **)(p + 0x34), 0);
		*(int *)(*(int *)(p + 0x34) + 0x14) |= 8;
		fcn_00426170(*(int **)(p + 0x34), 0);
		*(int *)(p + 0x34) = 0;
	}
	if (*(int *)(p + 0x38) != 0) {
		*(int *)(*(int *)(p + 0x38) + 0x20c) = 0;
		*(int *)(p + 0x38) = 0;
	}
}
