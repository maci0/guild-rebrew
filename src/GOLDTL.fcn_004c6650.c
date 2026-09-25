// FUNCTION: GOLD 0x004c5b90
// SIZE: 39
// FUNCTION: GOLDTL 0x4c6650
// SIZE: 39

void __cdecl fcn_004c4330(void*);

void __cdecl fcn_004c6650(int a1)
{
	char buf[0x9c];

	buf[0] = 0x4d;
	*(int*) (buf + 0x10) = a1;
	fcn_004c4330(buf);
}
