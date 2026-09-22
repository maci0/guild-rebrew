// FUNCTION: GOLDTL 0x4c5ed0
// SIZE: 70

void __cdecl fcn_004c4330(void*);

void __cdecl fcn_0064d530(void*, int, int);

void __cdecl fcn_004c5ed0(int a1, int a2, char a3)
{
	char buf[0x9c];

	*(int*) (buf + 0x10) = a1;
	buf[0] = 0x37;
	*(char*) (buf + 0x44) = a3;
	fcn_0064d530(buf + 0x14, a2, 0x2f);
	fcn_004c4330(buf);
}
