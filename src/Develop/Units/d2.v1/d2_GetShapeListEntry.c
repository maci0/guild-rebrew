
/* ADDRESS: GOLDTL 0x0047a070 */
/* ADDRESS: GOLDDE 0x00469320 */
char* __cdecl d2_GetShapeListEntry(char* p, int i)
{
	if (p == 0) {
		return 0;
	}
	return p + *(int*) (p + i * 4 + 0x45);
}
