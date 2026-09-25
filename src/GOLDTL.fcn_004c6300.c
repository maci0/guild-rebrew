// FUNCTION: GOLD 0x004c5840
// SIZE: 39
// FUNCTION: GOLDTL 0x4c6300
// SIZE: 39

void __cdecl fcn_004c4330(void*);

void __cdecl fcn_004c6300(int a1)
{
	char buf[0x9c];

	buf[0] = 0x42;
	*(int*) (buf + 0x10) = a1;
	fcn_004c4330(buf);
}
