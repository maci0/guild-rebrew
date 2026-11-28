
// fcn_00580070 — (a[0x10] - c0) / (c1 - c0) where c0=0x665f18 c1=0x665f14.

/* ADDRESS: GOLDTL 0x005886f0 */
/* ADDRESS: GOLDDE 0x0056e3b0 */
float __cdecl d2_CalcKanoneProgress(float* a)
{
	return (a[4] - *(float*) 0x665f18) / (*(float*) 0x665f14 - *(float*) 0x665f18);
}
