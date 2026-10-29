


unsigned short* __cdecl fcn_00508e40(int);
void __cdecl fcn_00529160(int, int, int, int);
int __cdecl fcn_00426cc0(int);
void __cdecl fcn_00428720(int);
void __cdecl gm_KillSpieler(int, int);

int __cdecl fcn_004c9980(char* x, char* out)
{
	unsigned short* e;
	int ok;

	ok = 0;
	if (out != 0)
		*out = 2;
	e = fcn_00508e40(*(int*) (x + 0x10));
	if (e != 0) {
		ok = 1;
		fcn_00529160(0, 0, *e, 0);
		if (*(char**) ((char*) e + 0x184) != 0 && *(int*) (*(char**) ((char*) e + 0x184) + 0x28) != -1)
			fcn_00428720(fcn_00426cc0(*(int*) (*(char**) ((char*) e + 0x184) + 0x28)));
		gm_KillSpieler(*e, *(int*) (x + 0x14));
	}
	if (out != 0 && ok != 0)
		*out = 1;
	return 0;
}
