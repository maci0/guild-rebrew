extern char* g_f8f080;

#if defined(REBREW_GOLD)
/* GOLD twin of GOLDTL fcn_00465920: 0x2ff slots of 0x2ec bytes here,
 * 0x3ff slots of 0x2f4 bytes in GOLDTL. */
/* ADDRESS: GOLD 0x00468850 */
int __cdecl d2_FindFreeElementSlot(void)
{
	int i;
	char* p;

	for (i = 0, p = (char*) ((*(int*)&g_f8f080) + 4); i < 0x2ff; i++, p += 0x2ec) {
		if (*(int*) p == 0) {
			return i;
		}
	}
	return -1;
}
#else
/* ADDRESS: GOLDTL 0x00465920 */
/* ADDRESS: GOLDDE 0x00459550 */
int __cdecl d2_FindFreeElementSlot(void)
{
	int i;
	char* p;

	for (i = 0, p = (char*) (*(int*) 0x1015ea0 + 4); i < 0x3ff; i++, p += 0x2f4) {
		if (*(int*) p == 0) {
			return i;
		}
	}
	return -1;
}
#endif
