/* ADDRESS: GOLDTL 0x005224f0 */
/* ADDRESS: GOLDDE 0x0050b7c0 */
char __cdecl d3_ClearSceneObjectActiveFlag(unsigned char* obj)
{
	obj[0x217] &= ~1;
	return 1;
}
