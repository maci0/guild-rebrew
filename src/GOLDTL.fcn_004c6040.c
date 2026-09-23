// FUNCTION: GOLDTL 0x4c6040
// SIZE: 72

void __cdecl fcn_004c4330(void*);

void __cdecl fcn_004c6040(int a1, int a2, int a3, int a4)
{
	char buf[0x9c];

	buf[0] = 0x3c;
	*(int*) (buf + 0x10) = a1;
	*(int*) (buf + 0x14) = a2;
	*(int*) (buf + 0x18) = a3;
	*(int*) (buf + 0x1c) = a4;
	fcn_004c4330(buf);
}
