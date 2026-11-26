extern volatile int g_6b7fac;

void __cdecl d3_InvalidateSubTreeFlags(char* p, int a);

/* ADDRESS: GOLDTL 0x0043ac80 */
char __cdecl fcn_0043ac80(char* a, char on)
{
	if (on) {
		if (*(int*) (a + 0x218) == 5 && *a == 'r') {
			*(int*) (a + 0x218) = 6;
			*(int*) (a + 0x40) = g_6b7fac;
			d3_InvalidateSubTreeFlags(a, 0);
			return 1;
		}
	} else if (*(int*) (a + 0x218) == 6) {
		*(int*) (a + 0x218) = 5;
		d3_InvalidateSubTreeFlags(a, 0);
	}
	return 1;
}
