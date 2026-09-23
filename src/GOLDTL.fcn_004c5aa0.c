// FUNCTION: GOLDTL 0x4c5aa0
// SIZE: 96

void __cdecl fcn_004c4330(void*);

void __cdecl fcn_004c5aa0(int a1, char a2, char a3, short a4, char a5, int a6)
{
	char buf[0x9c];

	buf[0] = 0x2c;
	*(int*) (buf + 0x14) = a1;
	*(char*) (buf + 0x18) = a2;
	*(char*) (buf + 0x19) = a3;
	*(short*) (buf + 0x1a) = a4;
	*(char*) (buf + 0x1c) = a5;
	*(int*) (buf + 0x1d) = a6;
	fcn_004c4330(buf);
}
