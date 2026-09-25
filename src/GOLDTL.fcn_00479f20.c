void __cdecl fcn_00478fc0(int, int, int, char*);

// FUNCTION: GOLDTL 0x479f20
// SIZE: 77

int __cdecl fcn_00479f20(int a1, int a2, int a3, char* h, int idx)
{
	char* e;
	char save;

	if (idx > *(unsigned short*) (h + 0x2a))
		return 0;
	e = h + *(int*) (h + idx * 4 + 0x45);
	save = e[0xd];
	e[0xd] = 3;
	fcn_00478fc0(a1, a2, a3, h + *(int*) (h + idx * 4 + 0x45));
	e[0xd] = save;
	return 1;
}
