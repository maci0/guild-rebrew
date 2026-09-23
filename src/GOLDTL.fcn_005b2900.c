extern char g_774a80[];
extern char g_6b5c60[];
extern char g_7f4ca4[];
extern char g_774970[];

// FUNCTION: GOLDTL 0x5b2900
// SIZE: 256
// FUNCTION: GOLD 0x5a9480
// SIZE: 256

void __cdecl fcn_0051af00(void*, int, ...);
void __cdecl fcn_00545d40(int, int, void*, int, int, void*);

void __cdecl fcn_005b2900(void* a1, void* a2, void* a3)
{
	if (*(char*) ((char*) a2 + 2) == 6) {
		fcn_0051af00(g_774a80, 0x1dcc, *(unsigned short*) a1, *(unsigned short*) a3);
		fcn_00545d40(*(int*) ((char*) a2 + 4), -1, g_774a80, 0, 0x5fd, g_6b5c60);
		return;
	}
	if (*(char*) ((char*) a3 + 2) == 6) {
		fcn_0051af00(g_774a80, 0x1dcc, *(unsigned short*) a1, *(unsigned short*) a2);
		fcn_00545d40(*(int*) ((char*) a3 + 4), -1, g_774a80, 0, 0x5fd, g_6b5c60);
		return;
	}
	if (*(char*) ((char*) a1 + 2) != 6) {
		fcn_0051af00(g_774a80, 0x1dcd, *(unsigned short*) a1, *(unsigned short*) a2,
		    *(unsigned short*) a3);
		fcn_00545d40(*(int*) (g_7f4ca4 + 540 * *(unsigned short*) g_774970), -1,
		    g_774a80, 0, 0x5fe, g_6b5c60);
	}
}
