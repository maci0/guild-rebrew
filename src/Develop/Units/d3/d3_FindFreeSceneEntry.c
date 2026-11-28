extern char d3_SceneEntries[];
extern char d3_SceneEntries[];

/* ADDRESS: GOLD 0x004cd350 */
/* ADDRESS: GOLDTL 0x004cded0 */
/* ADDRESS: GOLDDE 0x004bb6b0 */
char* __cdecl d3_FindFreeSceneEntry(void)
{
	int i;
	int a;

	for (i = 0, a = (int) d3_SceneEntries; a < (int) d3_SceneEntries + 0x2b8; a += 0x57, i++) {
		if (*(int*) a == 0) {
			return (char*) ((int) d3_SceneEntries + i * 87);
		}
	}
	return 0;
}
#if defined(REBREW_SERVER) || defined(REBREW_GOLD)
unsigned char _dpad_9ba1c0[2336];
#else
/* Reference gaps only; the emitted objects inside the span keep their own rows. */
unsigned char _dpad_9ba1c8[280];
unsigned char _dpad_9ba360[64];
unsigned char _dpad_9ba3dc[1560];
unsigned char _dpad_9ba9f8[8];
unsigned char _dpad_9baa0c[20];
unsigned char _dpad_9baa44[44];
unsigned char _dpad_9baa74[34];
unsigned char _dpad_9baa9a[66];
#endif
unsigned char _dpad_9baae0[752];
