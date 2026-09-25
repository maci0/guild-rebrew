// FUNCTION: GOLDTL 0x442d90
// SIZE: 152

void __cdecl fcn_004398d0(char*);
char* __cdecl fcn_00437890(char*);
void __cdecl fcn_00439d80(char*);
void __cdecl fcn_0044c200(int, int);
void __cdecl fcn_00449f90(char*, int, int);
void __cdecl fcn_0045cfa0(int);

char __cdecl fcn_00442d90(char* o, int a2)
{
	char* p;
	char* n;

	if (o == 0) {
		return 0;
	}
	if (*(char**) (o + 0x200) != 0) {
		fcn_004398d0(*(char**) (o + 0x200));
		*(char**) (o + 0x200) = 0;
	}
	p = *(char**) (o + 0x1f4);
	if (p != 0 && (p[0x214] & 1) == 0) {
		n = fcn_00437890(o);
		fcn_004398d0(p);
		*(char**) (o + 0x1f4) = n;
	}
	fcn_00439d80(o);
	fcn_0044c200(a2, a2);
	fcn_00449f90(o, 0, a2);
	fcn_0045cfa0(0);
	p = *(char**) (o + 0x1ec);
	if (p != 0 && *(int*) (p + 0x40c) != 0) {
		return 1;
	}
	return 0;
}
