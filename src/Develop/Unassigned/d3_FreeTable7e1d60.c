/* Drop every entry of a second pointer table. */

int __cdecl sb_UnloadSampleBank(int);
void __cdecl sb_ReleaseSampleBank(int);

#if defined(REBREW_GOLD)
/* ADDRESS: GOLD 0x00538010 */
void __cdecl d3_FreeTable7e1d60(void)
{
	int p;
	for (p = 0x75df20; p < 0x75e120; p += 4) {
		if (*(int*) p != 0) {
			sb_UnloadSampleBank(*(int*) p);
		}
	}
}
#else
/* ADDRESS: GOLDTL 0x0053f8f0 */
void __cdecl d3_FreeTable7e1d60(void)
{
	int* entry;

	for (entry = (int*) 0x7e1d60; (int) entry < (int) 0x7e1f60; entry++) {
		if (*entry != 0) {
			sb_ReleaseSampleBank(*entry);
		}
	}
}
#endif
