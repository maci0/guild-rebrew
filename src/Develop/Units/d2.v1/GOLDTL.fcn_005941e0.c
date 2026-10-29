

typedef struct
{
	char pad0[0x10];
	int x10;
	char pad14[0x240];
	int x254;
	int x258;
	char pad25c[0x3cc - 0x25c];
} Win;
// SIZE 0x3cc

extern int g_6a9b9c;
extern int g_772514;
#include "client_types.h"
extern Win_1015f40 g_1015f40[0x60];
extern int g_774a3c;
extern int g_774a38;
extern char* g_779cb8;
extern char* g_14b5d58;

char* __cdecl fcn_004ce000(void);
char* __cdecl fcn_004ce040(void);
void __cdecl d2_SetForm(int, int);
int __cdecl fcn_00519190(int, ...);
char* __cdecl fcn_004ce190(int);
int __cdecl sprintf(char*, const char*, ...);
void __cdecl fcn_0046c310(int);

void __cdecl fcn_005941e0(void)
{
	char buf[0x160];
	int last;
	int h;
	int n;
	char* e;
	char* p;

	last = -1;
	e = fcn_004ce000();
	d2_SetForm(g_6a9b9c, 5);
	h = ((Win*)g_1015f40)[g_772514].x254;
	fcn_00519190((int) "$C");
	g_774a3c = 0;
	while (e != 0) {
		g_774a3c++;
		p = fcn_004ce190(*(int*) (e + 0x68));
		if (p != 0 && *(int*) p == *(int*) (e + 0x68)) {
			n = *(int*) (p + 0xc);
		} else {
			n = 9;
		}
		if (*(int*) (e + 0x64) != 0) {
			if ((((int*)g_779cb8) != 0 && *(int*) (e + 0x64) == *((int*)g_779cb8)) || *(int*) (e + 0x68) == *((int*)g_779cb8)) {
				sprintf(buf, "$%dFF%s (%s): %s$A", n, e + 0x40, g_14b5d58, e);
			}
		} else {
			sprintf(buf, "$%dFF%s: %s$A", n, e + 0x40, e);
		}
		last = fcn_00519190((int) buf);
		e = fcn_004ce040();
	}
	if (g_774a3c > g_774a38 && last >= 0 && h > ((Win*)g_1015f40)[g_772514].x10) {
		g_774a38 = g_774a3c;
		n = h + 0x18;
		((Win*)g_1015f40)[g_772514].x254 = n;
		((Win*)g_1015f40)[g_772514].x258 = n - ((Win*)g_1015f40)[g_772514].x10;
		fcn_0046c310(g_772514);
	}
}
