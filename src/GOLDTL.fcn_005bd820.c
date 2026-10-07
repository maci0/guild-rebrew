// FUNCTION: GOLDTL 0x005bd820

extern int g_774a64;
extern unsigned char g_773d75;
extern char g_868060[];
extern char g_1015da0[];
extern char g_6ac3d0[];
extern int g_778d24;
extern int g_778d20;
extern float g_6ab3e0;

void __cdecl fcn_0047ac60(int, int);
int __cdecl fcn_0064d41a(char*, const char*, ...);
int* __cdecl fcn_00475c10(char*);
int __cdecl fcn_0047b640(int, int, int, int, int*, int);
void __cdecl fcn_00475f80(int*);

void __cdecl fcn_005bd820(void)
{
	char path[0x104];
	int* img;

	if (g_774a64 != 0) {
		fcn_0047ac60(g_774a64, 0);
		g_774a64 = 0;
	}
	fcn_0064d41a(path, g_6ac3d0, g_1015da0, g_868060 + g_773d75 * 756);
	img = fcn_00475c10(path);
	if (img != 0) {
		g_774a64 = fcn_0047b640(0, 0, img[1], img[2], img, 0x100);
		g_778d24 = img[1];
		g_778d20 = img[2];
		g_6ab3e0 = 7.5f;
		if (g_778d24 < 0x780) {
			g_6ab3e0 = 5.33f;
		}
		fcn_00475f80(img);
	}
}
