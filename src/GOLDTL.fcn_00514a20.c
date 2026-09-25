// FUNCTION: GOLDTL 0x00514a20
// SIZE: 304

#include <stdio.h>

// SIZE 0x7c
typedef struct {
	int who;
	char pad4[0x7c - 4];
} Msg;

extern char g_6a1ea4[];
extern char g_6a1e8c[];
extern char* g_14ac600;
extern unsigned char g_6a375c;
extern int g_77494c;
extern char* g_14ac5f0;
extern char* g_14ac5fc;
extern int g_7725c8;

void __cdecl fcn_00514570(char* s);
void __cdecl fcn_005356e0(void);
void __cdecl fcn_00535960(void);
int __cdecl fcn_005259f0(char* s);
void __cdecl fcn_004c5790(int kind, Msg* m);
void __cdecl fcn_00521920(char* s, int n);
void __cdecl fcn_00535770(int v);
void __cdecl fcn_00515250(void);

int __cdecl fcn_00514a20(char* name)
{
	Msg msg;
	char save[260];
	char path[260];
	char text[512];

	sprintf(path, g_6a1ea4, name);
	sprintf(text, g_14ac600, g_6a375c);
	fcn_00514570(text);
	g_77494c = 0;
	do {
		fcn_005356e0();
		fcn_00535960();
	} while (g_77494c == 0);
	if (g_77494c & 1) {
		sprintf(save, g_6a1e8c, name);
		fcn_00514570(g_14ac5f0);
		if (fcn_005259f0(save) == 0) {
			return 1;
		}
		if (g_77494c & 1) {
			msg.who = g_6a375c;
			fcn_004c5790(6, &msg);
		}
	}
	while (!(g_77494c & 4)) {
		fcn_005356e0();
		fcn_00535960();
	}
	fcn_00521920(path, 5);
	fcn_00535770(0x24087);
	fcn_00514570(g_14ac5fc);
	fcn_00515250();
	g_7725c8 = 0;
	return 0;
}
