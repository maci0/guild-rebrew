


void __cdecl fcn_004c4330(void*);

void __cdecl fcn_004c6880(int a1, int a2, int a3)
{
	char buf[0x9c];

	buf[0] = 0x52;
	*(int*) (buf + 0x10) = a1;
	*(int*) (buf + 0x14) = a2;
	*(int*) (buf + 0x18) = a3;
	fcn_004c4330(buf);
}
