// FUNCTION: GOLDTL 0x4c5fa0
// SIZE: 39

void __cdecl fcn_004c4330(void*);

void __cdecl fcn_004c5fa0(int a1)
{
	char buf[0x9c];

	buf[0] = 0x3a;
	*(int*) (buf + 0x10) = a1;
	fcn_004c4330(buf);
}
