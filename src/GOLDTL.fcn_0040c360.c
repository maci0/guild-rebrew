// FUNCTION: GOLD 0x0040b530
// FUNCTION: GOLDTL 0x0040c360

char* __cdecl fcn_00404dc0(char* e, char* name, int flag);
void __cdecl fcn_00436a00(int h, char* s, int n);

void __cdecl fcn_0040c360(char* e, char* name)
{
	char* s;

	s = fcn_00404dc0(e, name, 1);
	*(char**) (e + 0x74) = s;
	*(int*) (e + 0x70) = 0;
	if (s != 0) {
		fcn_00436a00(*(int*) (e + 0x34), s, -1);
		*(unsigned char*) (*(char**) (e + 0x74) + 0x6c) = 1;
		*(int*) (*(char**) (e + 0x74) + 0x70) &= ~3;
		*(unsigned char*) (*(char**) (e + 0x74) + 0x6d) |= 0x10;
	}
}
