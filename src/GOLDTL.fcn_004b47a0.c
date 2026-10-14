extern unsigned char g_773d75;

int __cdecl fcn_0050d320(int, char);
int __cdecl fcn_0050b710(int, char);

/* ADDRESS: GOLD 0x004b4630 */
/* ADDRESS: GOLDTL 0x004b47a0 */

int __cdecl fcn_004b47a0(int a, char* thr)
{
	return fcn_0050b710(fcn_0050d320(a, (*(char*)&g_773d75)), (*(char*)&g_773d75)) >= *(int*) (thr + 0x14);
}
