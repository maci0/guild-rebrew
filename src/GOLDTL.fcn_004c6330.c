// FUNCTION: GOLD 0x004c5870
// FUNCTION: GOLDTL 0x4c6330

void __cdecl fcn_004c4330(void*);

void __cdecl fcn_004c6330(int a1)
{
	char buf[0x9c];

	buf[0] = 0x43;
	*(int*) (buf + 0x10) = a1;
	fcn_004c4330(buf);
}
