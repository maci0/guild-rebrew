/* ADDRESS: GOLDTL 0x0043bf20 */
void __cdecl d3_InvalidateFloorChunks(char* floor)
{
	int i;
	int j;
	char* p;

	floor[0x8036] |= 1;
	p = floor + 0x28f;
	for (j = 0; j < 8; j++) {
		for (i = 0; i < 8; i++) {
			*p = (char) 0xff;
			p += 0x1f4;
		}
	}
}
