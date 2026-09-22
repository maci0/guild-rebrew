// FUNCTION: GOLDTL 0x4c5a20
// SIZE: 50

void __cdecl fcn_004c4330(void*);

void __cdecl fcn_004c5a20(int a1, int a2)
{
	char buf[0x9c];

	buf[0] = 0x2a;
	*(int*) (buf + 0x10) = a1;
	*(int*) (buf + 0x14) = a2;
	fcn_004c4330(buf);
}
