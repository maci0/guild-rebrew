// FUNCTION: GOLDTL 0x4c5250
// SIZE: 63

void __cdecl fcn_004c4330(void*);

void __cdecl fcn_004c5250(int a1, unsigned short a2, int a3)
{
	char buf[0x9c];

	buf[0] = 0x12;
	*(int*) (buf + 0x10) = a1;
	*(unsigned short*) (buf + 0x14) = a2;
	*(int*) (buf + 0x16) = a3;
	fcn_004c4330(buf);
}
