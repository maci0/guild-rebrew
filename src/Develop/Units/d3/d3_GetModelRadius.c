
/* ADDRESS: GOLDTL 0x0044c0c0 */
/* ADDRESS: GOLDDE 0x00442560 */
float __cdecl d3_GetModelRadius(int unused, char* node)
{
	if (node != 0) {
		if (*(int*) (node + 0x318) != 0) {
			return *(float*) (*(int*) (node + 0x318) + 0x1d4);
		}
	}
	return *(float*) 0x6628a8;
}
