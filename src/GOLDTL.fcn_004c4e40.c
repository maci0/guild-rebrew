// FUNCTION: GOLD 0x004c44d0
// SIZE: 39
// FUNCTION: GOLDTL 0x4c4e40
// SIZE: 39

void __cdecl fcn_004c4330(void*);

void __cdecl fcn_004c4e40(int a1)
{
	char buf[0x9c];

	buf[0] = 8;
	*(int*) (buf + 0x10) = a1;
	fcn_004c4330(buf);
}
