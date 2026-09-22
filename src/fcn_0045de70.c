// FUNCTION: GOLDTL 0x45de70
// SIZE: 47

void __cdecl fcn_0045de70(char* s, unsigned v)
{
	*(unsigned char*) (*(char**) (s + 8) + *(int*) (s + 0x14)) = (unsigned char) (v >> 8);
	*(int*) (s + 0x14) = *(int*) (s + 0x14) + 1;
	*(unsigned char*) (*(char**) (s + 8) + *(int*) (s + 0x14)) = (unsigned char) v;
	*(int*) (s + 0x14) = *(int*) (s + 0x14) + 1;
}
