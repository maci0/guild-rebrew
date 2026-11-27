
/* ADDRESS: GOLDTL 0x00445d00 */
char __cdecl d3_ScaleNodeIntensityCallback(char* p, float* q)
{
	*(float*) (p + 0x94) = *q * *(float*) (p + 0x94);
	return 1;
}
