extern char g_7e6068[];
extern char g_7e6068[];

/* ADDRESS: GOLD 0x0052c4d0 */
/* ADDRESS: GOLDTL 0x00531c00 */
void __cdecl fcn_00531c00(int value)
{
	int i;
	int cursor;

	for (i = 0, cursor = (int) g_7e6068; cursor < (int) g_7e6068 + 0x4300; cursor += 0x10c, i++) {
		if (*(int*) cursor == value) {
			*(int*) ((int) g_7e6068 + i * 268) = 0;
			return;
		}
	}
}
