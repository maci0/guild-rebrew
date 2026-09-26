// FUNCTION: GOLDTL 0x456c80
// SIZE: 109

extern unsigned int g_104061c;
extern unsigned int g_10405fc;
extern int g_6b89b8;
extern void* g_6b5de0;
extern void** g_1040610[];

long __stdcall fcn_005ef8cf(void*, unsigned int, unsigned int, int, int, int, void**);

void __cdecl fcn_00456c80(void)
{
	unsigned int s;
	unsigned int i;

	s = g_104061c;
	if (s > 0 && g_10405fc > 0) {
		for (i = 0; s <= g_10405fc; s += s) {
			if (i > 2) {
				return;
			}
			fcn_005ef8cf(g_6b5de0, s, s, g_6b89b8, 0, 0, &((void**)g_1040610)[i]);
			i++;
		}
	} else {
		i = 0;
	}
	for (; i <= 2; i++) {
		((void**)g_1040610)[i] = 0;
	}
}
