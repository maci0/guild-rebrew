extern int d3_SceneLightingColors[];

/* ADDRESS: GOLDTL 0x00459b80 */
/* ADDRESS: GOLDDE 0x0044f340 */
void __cdecl InitColorTable(void)
{
	d3_SceneLightingColors[0] = 0xff000040;
	d3_SceneLightingColors[1] = 0xffe08080;
	d3_SceneLightingColors[2] = 0xffe0e0e0;
	d3_SceneLightingColors[3] = 0xffffffff;
	d3_SceneLightingColors[4] = 0xffe0e0e0;
	d3_SceneLightingColors[5] = 0xffe08080;
}
