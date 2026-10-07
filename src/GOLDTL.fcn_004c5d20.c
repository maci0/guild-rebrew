// FUNCTION: GOLD 0x004c5260
// FUNCTION: GOLDTL 0x4c5d20

void __cdecl fcn_004c4330(void*);

void __cdecl fcn_004c5d20(int a1, int a2)
{
	char buf[0x9c];

	buf[0] = 0x33;
	*(int*) (buf + 0x10) = a1;
	*(int*) (buf + 0x14) = a2;
	fcn_004c4330(buf);
}
