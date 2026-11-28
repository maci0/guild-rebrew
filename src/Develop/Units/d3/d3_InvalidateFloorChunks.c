#if defined(REBREW_GOLD)
/* ADDRESS: GOLD 0x00440140 */
void __cdecl d3_InvalidateFloorChunks(char* obj)
{
	int row;
	int col;
	char* cursor;

	obj[0x1c70] = obj[0x1c70] | 1;
	cursor = obj + 0x13f;
	for (row = 8; row != 0; row--) {
		for (col = 8; col != 0; col--) {
			*cursor = (char) 0xff;
			cursor += 0x64;
		}
	}
}
#else
/* ADDRESS: GOLDTL 0x0043bf20 */
/* ADDRESS: GOLDDE 0x00434be0 */
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
#endif
