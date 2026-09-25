// FUNCTION: GOLD 0x5a8f60
// SIZE: 201
// FUNCTION: GOLDTL 0x005b23e0
// SIZE: 201

extern char g_7f4ca0[];
extern char g_774a80[];
extern char g_6b5c60[];

void __cdecl fcn_0051af00(char*, int, ...);
void __cdecl fcn_00545d40(int, int, char*, int, int, char*);

void __cdecl fcn_005b23e0(char* a1, char* a2, int a3)
{
	int i;

	if (a2[2] == 6 || a2[2] == 7) {
		fcn_0051af00(g_774a80, 0x20c1, *(unsigned short*) a1, a3);
		fcn_00545d40(*(int*) (a2 + 4), -1, g_774a80, 0, 0x5fb, g_6b5c60);
	}
	fcn_0051af00(g_774a80, 0x20c2, a3, *(unsigned short*) a1, (a1[9] != 0) + 0x20c3,
	    *(unsigned short*) a2);
	for (i = 0; i < 768; i++) {
		if (g_7f4ca0 + i * 540 != a1 && g_7f4ca0 + i * 540 != a2 &&
		    (g_7f4ca0[i * 540 + 2] == 6 || g_7f4ca0[i * 540 + 2] == 7)) {
			fcn_00545d40(*(int*) (g_7f4ca0 + i * 540 + 4), -1, g_774a80, 0, 0x5ec, g_6b5c60);
		}
	}
}
