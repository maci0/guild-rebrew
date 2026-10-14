/* ADDRESS: GOLD 0x00580070 */
// fcn_00580070 — (a[0x10] - c0) / (c1 - c0) where c0=0x5eec70 c1=0x5eec6c.

float __cdecl fcn_00580070(float* a)
{
	return (a[4] - *(float*) 0x5eec70) / (*(float*) 0x5eec6c - *(float*) 0x5eec70);
}
