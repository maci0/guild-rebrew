// FUNCTION: GOLDTL 0x4c6ea0

void __cdecl fcn_004c4330(void*);

void __cdecl fcn_004c6ea0(char* a1)
{
	char buf[0x9c];

	buf[0] = 0x69;
	*(int*) (buf + 0x10) = *(int*) (a1 + 2);
	fcn_004c4330(buf);
}
