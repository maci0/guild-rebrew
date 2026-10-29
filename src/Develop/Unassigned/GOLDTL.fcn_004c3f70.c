

void __cdecl fcn_004c4330(void*);

void __cdecl fcn_004c3f70(void)
{
	char buf[0x9c];

	buf[0] = 3;
	*(int*) (buf + 0x10) = 0xa03ef57c;
	*(int*) (buf + 0x14) = 0;
	fcn_004c4330(buf);
}
