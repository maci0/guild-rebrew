// FUNCTION: GOLDTL 0x4c6470
// SIZE: 50

void __cdecl fcn_004c4330(void*);

void __cdecl fcn_004c6470(int a1, char a2)
{
	char buf[0x9c];

	buf[0] = 0x48;
	*(int*) (buf + 0x10) = a1;
	*(char*) (buf + 0x14) = a2;
	fcn_004c4330(buf);
}
