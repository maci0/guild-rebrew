// FUNCTION: GOLD 0x004c4960
// FUNCTION: GOLDTL 0x4c52d0

void __cdecl fcn_004c4330(void*);

void __cdecl fcn_004c52d0(int a1, unsigned short a2)
{
	char buf[0x9c];

	buf[0] = 0x14;
	*(int*) (buf + 0x10) = a1;
	*(unsigned short*) (buf + 0x14) = a2;
	fcn_004c4330(buf);
}
