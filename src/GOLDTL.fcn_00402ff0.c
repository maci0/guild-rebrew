extern void* g_14d0020[];
// GLOBAL: GOLDTL 0x67a370
extern int g_67a370;
// FUNCTION: GOLD 0x4027b0
// FUNCTION: GOLDTL 0x402ff0

void __cdecl fcn_00438c40(int, void*);

void __cdecl fcn_00402ff0(void)
{
	void** p;
	void* e;

	p = g_14d0020;
	do {
		e = *p;
		if (e != 0 && (*(unsigned char*) ((char*) e + 0x8c) & 1) != 0 &&
		    *(int*) ((char*) e + 0x88) == g_67a370) {
			fcn_00438c40(*(int*) ((char*) e + 0x34), (char*) e + 0x54);
		}
		p++;
	} while ((int) p < (int) (g_14d0020 + 0x300));
}
