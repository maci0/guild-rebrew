extern char g_774a80[];
extern char g_6ab430[];
extern char g_7f4ca0[];
// FUNCTION: GOLD 0x005a9310
// FUNCTION: GOLDTL 0x5b2790

unsigned short __cdecl gm_RandomMod(int);
int  __cdecl fcn_0064d41a(char*, char*, int);
void __cdecl fcn_0051af00(void*, int);
void __cdecl fcn_00545d40(int, int, void*, int, int, void*);

void __cdecl fcn_005b2790(void)
{
	char buf[0x100];
	int id;
	int p;

	id = gm_RandomMod(3);
	fcn_0064d41a(buf, g_6ab430, id);
	fcn_0051af00(g_774a80, id + 0x20c7);
	for (p = (int) g_7f4ca0 + 2; p < (int) g_7f4ca0 + 0x65402; p += 0x21c) {
		if (*(char*) p == 6 || *(char*) p == 7) {
			fcn_00545d40(*(int*) (p + 2), -1, g_774a80, 0, 0x600, buf);
		}
	}
}
