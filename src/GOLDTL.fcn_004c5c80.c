// FUNCTION: GOLD 0x004c5230
// FUNCTION: GOLDTL 0x4c5c80

void __cdecl fcn_004c4330(void*);

void __cdecl fcn_004c5c80(int a1)
{
	char buf[0x9c];

	buf[0] = 0x31;
	*(int*) (buf + 0x10) = a1;
	fcn_004c4330(buf);
}
