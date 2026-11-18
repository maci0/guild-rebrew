


void __cdecl fcn_004c4330(void*);

void __cdecl fcn_004c6db0(int* values)
{
	char buf[0x9c];

	buf[0] = 0x66;
	*(int*) (buf + 0x10) = values[0];
	*(int*) (buf + 0x14) = values[1];
	fcn_004c4330(buf);
}
