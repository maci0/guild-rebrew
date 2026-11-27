/* ADDRESS: GOLD 0x0044a9e0 */
int __cdecl d3_GetScenePresetCount(unsigned int a)
{
	if (a >= 0x3a6c00ba) {
		return 7;
	}
	if (a >= 0x3a6c00a5) {
		return 6;
	}
	return (a < 0x3a6c00a1 ? -4 : 0) + 4;
}
