// FUNCTION: GOLD 0x004c5460
// FUNCTION: GOLDTL 0x004c5f20

void __cdecl fcn_004c4330(void*);

void __cdecl fcn_004c5f20(int a1, int a2, int a3)
{
	char buf[0x9c];

	buf[0] = 0x36;
	*(int*) (buf + 0x10) = a1;
	*(int*) (buf + 0x14) = a2;
	*(int*) (buf + 0x18) = a3;
	fcn_004c4330(buf);
}
