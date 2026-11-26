extern char g_6641a4[];
extern char g_6641a4[];

/* ADDRESS: GOLD 0x00493380 */
/* ADDRESS: GOLDTL 0x00492950 */
int __cdecl gm_IsDiceStageValid(char* p, int entity, int stage)
{
	int value;
	int e;

	if (entity == *(int*) (p + 0xc)) {
		value = *(int*) (p + 0x28);
	} else if (entity == *(int*) (p + 0x30)) {
		value = *(int*) (p + 0x4c);
	} else {
		return 0;
	}
	for (e = (int) g_6641a4; e < (int) g_6641a4 + 0x48; e += 8) {
		if (*(int*) (e - 4) == value && *(int*) e == stage) {
			return 1;
		}
	}
	return 0;
}
