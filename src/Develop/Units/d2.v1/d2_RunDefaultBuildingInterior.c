/* fcn_0058f700 — do r = fcn_005309d0(0x58f700, 0x67fff); while (r != 0). */

int __cdecl main_RunFrameLoop(void*, int);

#if defined(REBREW_GOLD)
/* ADDRESS: GOLD 0x0058f700 */
void __cdecl d2_RunDefaultBuildingInterior(void)
{
	int r;
	do {
		r = main_RunFrameLoop((void*) 0x58f700, 0x67fff);
	} while (r != 0);
}
#else
/* ADDRESS: GOLDTL 0x00597fd0 */
/* ADDRESS: GOLDDE 0x0057d780 */
void __cdecl d2_RunDefaultBuildingInterior(void)
{
	int r;
	do {
		r = main_RunFrameLoop((void*) d2_RunDefaultBuildingInterior, 0x67fff);
	} while (r != 0);
}
#endif
