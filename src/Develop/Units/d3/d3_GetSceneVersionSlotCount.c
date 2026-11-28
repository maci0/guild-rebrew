
/* ADDRESS: GOLDTL 0x00446ca0 */
/* ADDRESS: GOLDDE 0x0043e6c0 */
int __cdecl d3_GetSceneVersionSlotCount(unsigned version)
{
	if (version >= 0x3a6c00ba) {
		return 7;
	}
	if (version >= 0x3a6c00a5) {
		return 6;
	}
	if (version >= 0x3a6c00a1) {
		return 4;
	}
	return 0;
}
