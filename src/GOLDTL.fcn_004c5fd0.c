// FUNCTION: GOLD 0x004c5510
// FUNCTION: GOLDTL 0x4c5fd0

void __cdecl fcn_004c4330(void*);

void __cdecl fcn_004c5fd0(int a1)
{
	char buf[0x9c];

	buf[0] = 0x3b;
	*(int*) (buf + 0x10) = a1;
	fcn_004c4330(buf);
}
