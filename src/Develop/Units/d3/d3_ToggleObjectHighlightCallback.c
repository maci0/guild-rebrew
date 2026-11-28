extern volatile int gm_GameTicks;

void __cdecl d3_InvalidateSubTreeFlags(char* p, int a);

/* ADDRESS: GOLDTL 0x0043ac80 */
/* ADDRESS: GOLDDE 0x00433a40 */
char __cdecl d3_ToggleObjectHighlightCallback(char* a, char on)
{
	if (on) {
		if (*(int*) (a + 0x218) == 5 && *a == 'r') {
			*(int*) (a + 0x218) = 6;
			*(int*) (a + 0x40) = gm_GameTicks;
			d3_InvalidateSubTreeFlags(a, 0);
			return 1;
		}
	} else if (*(int*) (a + 0x218) == 6) {
		*(int*) (a + 0x218) = 5;
		d3_InvalidateSubTreeFlags(a, 0);
	}
	return 1;
}
