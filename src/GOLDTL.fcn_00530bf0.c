// FUNCTION: GOLD 0x0052b4c0
// SIZE: 110
// FUNCTION: GOLDTL 0x530bf0
// SIZE: 110

int sprintf(char*, const char*, ...);
char* __cdecl fcn_00426fd0(int);
void __cdecl fcn_00428340(char*, int, char*);

char* __cdecl fcn_00530bf0(char* o, int x)
{
	char buf[0x80];
	char* p;

	sprintf(buf, "sp_%i", *(int*) (o + 4));
	p = fcn_00426fd0(x);
	if (p != 0) {
		fcn_00428340(p, 1, buf);
		*(int*) (p + 0xc94) = *(int*) (o + 0x184);
		*(int*) (*(char**) (o + 0x184) + 0x28) = *(int*) (p + 0x100);
	}
	return p;
}
