
/* ADDRESS: GOLDTL 0x00445d00 */
/* ADDRESS: GOLDDE 0x0043da90 */
char __cdecl d3_ScaleNodeIntensityCallback(char* p, float* q)
{
	*(float*) (p + 0x94) = *q * *(float*) (p + 0x94);
	return 1;
}
