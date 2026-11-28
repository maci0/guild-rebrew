
/* ADDRESS: GOLDTL 0x00477520 */
/* ADDRESS: GOLDDE 0x00469280 */
int __cdecl shp_InitRenderState(int suppressDraw, int blendMode)
{
	*(int*) 0x100f1bc = blendMode;
	*(int*) 0x7725f4 = 1;
	*(int*) 0x100ef80 = suppressDraw;
	*(unsigned short*) 0x100eb6c = 0xbdef;
	return 1;
}
