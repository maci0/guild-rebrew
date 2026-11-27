void __cdecl d3_BuildFloorGeometry(char* a);

/* ADDRESS: GOLDTL 0x004416e0 */
void __cdecl d3_SetFloorScale(char* a, float v)
{
	if (a != 0) {
		*(float*) (a + 0x78) = -v;
		*(float*) (a + 0x60) = v;
		d3_BuildFloorGeometry(a);
	}
}
