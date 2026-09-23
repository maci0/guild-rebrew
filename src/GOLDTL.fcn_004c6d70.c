// FUNCTION: GOLDTL 0x4c6d70
// SIZE: 55

void __cdecl fcn_004c4330(void*);

void __cdecl fcn_004c6d70(char* a1, char* a2)
{
	char buf[0x9c];

	buf[0] = 0x65;
	*(int*) (buf + 0x10) = *(int*) a1;
	*(int*) (buf + 0x14) = *(int*) (a2 + 4);
	fcn_004c4330(buf);
}
