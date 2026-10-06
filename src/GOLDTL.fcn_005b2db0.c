extern char g_774a80[];
extern char g_6b5c60[];
// FUNCTION: GOLDTL 0x5b2db0

int  __cdecl fcn_0051e070(void);
void __cdecl fcn_0051af00(void*, int, int, int, int, int, int);
void __cdecl fcn_00545d40(int, int, void*, int, int, void*);

void __cdecl fcn_005b2db0(void* a1, void* a2, int a3, int a4, int a5, int a6)
{
	char t;

	t = *(char*) ((char*) a1 + 2);
	if (t == 6 || t == 7) {
		switch (fcn_0051e070()) {
		case 0:
		case 2:
			fcn_0051af00(g_774a80, 0x414f, *(unsigned short*) a2, a3,
			    *(int*) (0x665f78 + a4 * 4), a5, a6);
			break;
		case 1:
			fcn_0051af00(g_774a80, 0x414f, *(unsigned short*) a2,
			    *(int*) (0x665f78 + a4 * 4), a3, a5, a6);
			break;
		}
		fcn_00545d40(*(int*) ((char*) a1 + 4), -1, g_774a80, 0, 0x5fc, g_6b5c60);
	}
}
