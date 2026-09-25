// FUNCTION: GOLD 0x005a9b80
// SIZE: 188
// FUNCTION: GOLDTL 0x005b3000
// SIZE: 188

extern char g_774a80[];
extern char g_774e80[];
extern char g_6ab50c[];

char* __cdecl strcat(char*, const char*);
#pragma intrinsic(strcat)
void __cdecl fcn_0051af00(char*, int, ...);
void __cdecl fcn_00545d40(int, int, char*, int, int, char*);

void __cdecl fcn_005b3000(char* a1, unsigned char* a2, unsigned short* a3, int a4)
{
	fcn_0051af00(g_774a80, 0x40ad, 0x40a3, *(unsigned short*) a2, *(int*) (a2 + 0x16c), *a3);
	if (a4 != 0) {
		fcn_0051af00(g_774e80, 0x40ae, (a2[9] != 0 ? 0x230 : 0x20d) + a2[0x165]);
		strcat(g_774a80, g_774e80);
	}
	fcn_00545d40(*(int*) (a1 + 4), -1, g_774a80, 0, 0x5fa, g_6ab50c);
}
