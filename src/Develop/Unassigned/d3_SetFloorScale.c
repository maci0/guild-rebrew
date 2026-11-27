void __cdecl d3_BuildFloorGeometry(char* a);

/* ADDRESS: GOLDTL 0x004416e0 */
void __cdecl d3_SetFloorScale(char* floor, float scale)
{
	if (floor != 0) {
		*(float*) (floor + 0x78) = -scale;
		*(float*) (floor + 0x60) = scale;
		d3_BuildFloorGeometry(floor);
	}
}
