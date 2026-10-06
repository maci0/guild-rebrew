// FUNCTION: GOLDTL 0x4c5120

void __cdecl fcn_004c4330(void*);

void __cdecl fcn_004c5120(unsigned short a1)
{
	char buf[0x9c];

	buf[0] = 0xe;
	*(unsigned short*) (buf + 0x10) = a1;
	fcn_004c4330(buf);
}
