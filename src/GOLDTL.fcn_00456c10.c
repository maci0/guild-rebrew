typedef int(__stdcall* Fn1)(void* self);

extern unsigned int g_10405fc;
extern unsigned int g_104061c;
extern void** g_1040610[];
extern unsigned long g_14ce728;

// FUNCTION: GOLDTL 0x456c10
void __cdecl fcn_00456c10(void)
{
	unsigned int i;
	unsigned int s;

	for (i = 0, s = g_104061c; s <= g_10405fc && i <= 2; i++, s += s) {
		if (g_1040610[i] != 0) {
			(*(int*)&g_14ce728) = ((Fn1) ((void**) *g_1040610[i])[2])(g_1040610[i]);
			g_1040610[i] = 0;
		}
	}
}
