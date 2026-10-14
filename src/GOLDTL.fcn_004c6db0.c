


void __cdecl fcn_004c4330(void*);

void __cdecl fcn_004c6db0(int* a1)
{
	char buf[0x9c];

	buf[0] = 0x66;
	*(int*) (buf + 0x10) = a1[0];
	*(int*) (buf + 0x14) = a1[1];
	fcn_004c4330(buf);
}
