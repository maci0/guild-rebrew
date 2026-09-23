// FUNCTION: GOLDTL 0x438a80
// SIZE: 52

char __cdecl fcn_00438a80(char* p, char a2)
{
	*(unsigned char*) (p + 0x214) |= 4;
	if (a2 != 0) {
		*(unsigned char*) (p + 0x216) &= 0xdf;
	}
	*(unsigned char*) (p + 0x216) &= 0xbf;
	return 1;
}
