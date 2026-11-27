/* ADDRESS: GOLDTL 0x005224f0 */
char __cdecl d3_ClearSceneObjectActiveFlag(unsigned char* obj)
{
	obj[0x217] &= ~1;
	return 1;
}
