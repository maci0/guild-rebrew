extern char g_774a80[];
extern char g_6ab4b8[];
// FUNCTION: GOLD 0x005a9a60
// FUNCTION: GOLDTL 0x5b2ee0

int  __cdecl fcn_0051e070(void);
unsigned short __cdecl fcn_0042e410(int);
void __cdecl fcn_0051af00(void*, int, int, int, void*, int);
void __cdecl fcn_00545d40(int, int, void*, int, int, void*);

void __cdecl fcn_005b2ee0(void* a1, void* a2, void* a3)
{
	switch (fcn_0051e070()) {
	case 0:
	case 2:
		fcn_0051af00(g_774a80, 0x409b, fcn_0042e410(3) + 0x409c,
		    *(unsigned short*) a1, a3, *(unsigned short*) a1);
		break;
	case 1:
		fcn_0051af00(g_774a80, 0x409b, fcn_0042e410(3) + 0x409c,
		    *(unsigned short*) a1, *(unsigned short*) a1, a3);
		break;
	}
	fcn_00545d40(*(int*) ((char*) a2 + 4), -1, g_774a80, 1, 0x5fb, g_6ab4b8);
}
