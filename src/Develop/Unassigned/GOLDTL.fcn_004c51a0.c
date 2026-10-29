


void __cdecl fcn_004c4330(void*);

void __cdecl fcn_004c51a0(int a1, int a2, char a3, int a4)
{
	char buf[0x9c];

	buf[0] = 0x10;
	*(int*) (buf + 0x10) = a1;
	*(int*) (buf + 0x14) = a2;
	*(char*) (buf + 0x1c) = a3;
	*(int*) (buf + 0x1d) = a4;
	fcn_004c4330(buf);
}
