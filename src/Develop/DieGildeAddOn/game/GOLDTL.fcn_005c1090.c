extern __int64 g_666018;
extern int g_66601c;
extern char g_5c0d90[];

#include <string.h>

void __cdecl fcn_0051af00(void*, int, ...);
void __cdecl fcn_005cd440(void*, void*, int, int);
void __cdecl fcn_00532ef0(void);


/* ADDRESS: GOLDTL 0x005c1090 */
void __cdecl fcn_005c1090(int a1)
{
	char buf[0x90];

	if (a1 == 0) {
		return;
	}
	memset(buf, 0, 0x50);
	*(int*) (buf + 4) = 0x400;
	*(int*) (buf + 0x10) = 6;
	*(int*) (buf + 8) = (*(int*)&g_666018);
	*(int*) (buf + 0xc) = g_66601c;
	fcn_0051af00(buf + 0x50, 0x190d);
	fcn_005cd440(buf, buf + 0x50, 0, (int) g_5c0d90);
	fcn_00532ef0();
}
