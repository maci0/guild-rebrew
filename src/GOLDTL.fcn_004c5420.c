// FUNCTION: GOLDTL 0x4c5420
// SIZE: 83

void __cdecl fcn_004c4330(void*);

void __cdecl fcn_004c5420(int a1, int a2, int a3, int a4, int a5)
{
	char buf[0x9c];

	buf[0] = 0x19;
	*(int*) (buf + 0x10) = a1;
	*(int*) (buf + 0x14) = a2;
	*(int*) (buf + 0x18) = a3;
	*(int*) (buf + 0x1c) = a4;
	*(int*) (buf + 0x20) = a5;
	fcn_004c4330(buf);
}
