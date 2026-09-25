// FUNCTION: GOLD 0x5a1900
// SIZE: 288
// FUNCTION: GOLDTL 0x005aac20
// SIZE: 288

#include <string.h>

typedef struct
{
	int x0;
	int x4;
	int x8;
	int xc;
	int x10;
	int x14;
	int x18;
	char pad1c[0x34];
} Query;
// SIZE 0x50

extern unsigned short g_774970;
extern char g_7f4ca0[];
extern int g_14aad38;
extern int g_14aad18;
extern int g_14aacf8;
extern int g_14aacd0;

int __cdecl fcn_004eb320(char*);
void __cdecl fcn_00526120(int, int);
void __cdecl fcn_00525f60(char*, int);
void __cdecl fcn_005cd440(Query*, int, int, void*);
void __cdecl fcn_005cde50(void*, int, int);
int __cdecl fcn_005aa860(unsigned short*);
void __cdecl fcn_005aa9a0(int);
void __cdecl fcn_005aaae0(int);
void __cdecl fcn_00532ef0(void);

void __cdecl fcn_005aac20(void)
{
	Query q;
	int r;
	char lvl;

	r = fcn_004eb320(g_7f4ca0 + g_774970 * 540);
	if (r != 1) {
		if (r == -1) {
			fcn_00526120(g_14aad38, 0);
			return;
		}
		fcn_00525f60(g_7f4ca0 + g_774970 * 540, 8);
		return;
	}
	lvl = g_7f4ca0[g_774970 * 540 + 0x169];
	if (lvl == 0x1e) {
		memset(&q, 0, sizeof(q));
		q.x4 = 0xc00;
		q.x10 = 6;
		q.x18 = 1;
		fcn_005cd440(&q, g_14aad18, 0, (void*) fcn_005aa860);
	} else if (lvl == 0x1f || lvl == 0x21) {
		fcn_005cde50((void*) fcn_005aa9a0, g_14aacd0, 0);
	} else if (lvl == 0x20) {
		fcn_005cde50((void*) fcn_005aaae0, g_14aacf8, 0);
	}
	fcn_00532ef0();
}
