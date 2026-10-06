// FUNCTION: GOLDTL 0x00593550

#include <string.h>

typedef struct
{
	char pad0[0x18];
	int x18;
	int x1c;
	char pad20[0x18];
	int x38;
	char pad3c[0x20];
	int x5c;
	char pad60[0x170];
	int x1d0;
	char pad1d4[0x2f4 - 0x1d4];
} Ctl;
// SIZE 0x2f4

extern int* g_774a34;
extern int g_6a9b9c;
extern int g_772514;
extern char* g_1015ea0;
extern char* g_14a5774;
extern char* g_14a579c;
extern char* g_14b5d54;
extern int g_779cc0[];
extern char* g_779cb8;
extern int g_779ce0;
extern int g_779c40;

char* __cdecl fcn_004ce190(int);
void __cdecl fcn_004727a0(int, int);
int __cdecl fcn_00519190(int, ...);
int __cdecl sprintf(char*, const char*, ...);
int __cdecl fcn_0046f740(int, int, int, int);
int __cdecl fcn_0046fac0(int, int, char*, int);

void __cdecl fcn_00593550(void)
{
	int y;
	int i;
	char buf[0x100];
	char* p;
	int h;

	y = 10;
	fcn_004727a0(g_6a9b9c, 1);
	fcn_00519190((int) "$C");
	for (i = 0; i < 8; i++) {
		p = fcn_004ce190(g_774a34[i + 1]);
		if (p != 0) {
			h = fcn_0046f740(5, y, *(int*) (p + 0xc) + 0x59a, g_772514);
			sprintf(buf, "%s %s %s ", p[0x10] == 0 ? g_14a5774 : g_14a579c, p + 0x12, p + 0x22);
			if (*(int*) (p + 4) != 0) {
				strcat(buf, g_14b5d54);
			}
			fcn_0046fac0(((Ctl*)g_1015ea0)[h].x18 + 10, y, buf, g_772514);
			y = y + ((Ctl*)g_1015ea0)[h].x1c + 5;
			g_779cc0[i] = h;
			if (p == g_779cb8) {
				g_779ce0 = i;
			} else {
				((Ctl*)g_1015ea0)[h].x5c = 1;
				((Ctl*)g_1015ea0)[h].x1d0 = 3;
			}
			if (g_779c40 == *(int*) p) {
				((Ctl*)g_1015ea0)[h].x38 = 1;
			}
		}
	}
}
