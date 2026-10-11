extern char g_774a80[];
// FUNCTION: GOLD 0x005a91a0
// FUNCTION: GOLDTL 0x5b2620

unsigned short __cdecl gm_RandomMod(int);
void __cdecl fcn_0051af00(void*, int, ...);
void __cdecl fcn_00545d40(int, int, void*, int, int, int);

void __cdecl fcn_005b2620(void* a1, void* a2)
{
	char buf[0x200];
	char t;

	t = *(char*) ((char*) a2 + 2);
	if (t == 6 || t == 7) {
		fcn_0051af00(buf, gm_RandomMod(3) + 0x134a, *(unsigned short*) a1);
		fcn_0051af00(g_774a80, 0x1343, *(unsigned short*) a1,
		    gm_RandomMod(3) +
		        (*(char*) ((char*) a2 + 9) != 0 ? 0x1347 : 0x1344),
		    *(unsigned short*) a2, buf);
		fcn_00545d40(*(int*) ((char*) a2 + 4), -1, g_774a80, 1, 0x5ec, 0);
	}
}
