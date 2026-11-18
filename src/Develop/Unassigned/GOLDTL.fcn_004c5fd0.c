


void __cdecl fcn_004c4330(void*);

void __cdecl fcn_004c5fd0(int value)
{
	char buf[0x9c];

	buf[0] = 0x3b;
	*(int*) (buf + 0x10) = value;
	fcn_004c4330(buf);
}
