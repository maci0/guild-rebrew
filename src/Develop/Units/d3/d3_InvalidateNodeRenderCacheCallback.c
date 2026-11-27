
/* ADDRESS: GOLDTL 0x00438a80 */
char __cdecl d3_InvalidateNodeRenderCacheCallback(char* p, char clearBit)
{
	*(unsigned char*) (p + 0x214) |= 4;
	if (clearBit != 0) {
		*(unsigned char*) (p + 0x216) &= 0xdf;
	}
	*(unsigned char*) (p + 0x216) &= 0xbf;
	return 1;
}
