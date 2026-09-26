// FUNCTION: GOLD 0x00544580
// SIZE: 533
// FUNCTION: GOLDTL 0x54c500
// SIZE: 533

// SIZE 0x21c
struct house {
	unsigned short id;
	unsigned char type;
	char pad3;
	int handle;
	unsigned char level;
	char pad9[0x213];
};

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;
extern char g_7f4ca0[];

char* __cdecl fcn_00508e40(int);
int __cdecl fcn_004c4450(int);
void __cdecl fcn_00500bb0(pos14_7f4c00*, int, int, int);
int __cdecl fcn_004c5620(int, char*);
int __cdecl fcn_005c6270(char*, int);
float __cdecl fcn_00507f10(struct house*, int);
float __cdecl fcn_00507ed0(float, float);
void __cdecl fcn_004c54c0(int, int, int, int);
int __cdecl fcn_00500cb0(char*, pos14_7f4c00*);
void __cdecl fcn_00546190(char*);

void __cdecl fcn_0054c500(char* e)
{
	char* a;
	char* b;
	int mult;
	int i;
	int idx;
	int v;
	float f;

	a = fcn_00508e40(*(int*) (e + 0xbc));
	b = fcn_00508e40(*(int*) (e + 0xc));
	mult = 1;
	if (*(int*) (e + 0x70) == -1 || *(int*) (e + 0x70) == -2) {
		fcn_00546190(e);
		return;
	}
	if ((e[0x78] & 4) != 0) {
		return;
	}
	if (*(int*) (e + 0x84) != -1 && fcn_004c4450(*(int*) (e + 0x84)) == 0) {
		return;
	}
	*(int*) (e + 0x84) = -1;
	if (a == 0) {
		fcn_00500bb0((pos14_7f4c00*) (e + 0x52), 0, 1, 0);
		fcn_004c5620(-1, e);
		return;
	}
	if (b != 0) {
		mult = (fcn_005c6270(b, 0x2c5) != 0) + 1;
	}
	idx = *(int*) (e + 0xc4);
	i = 0;
	while (*(int*) (e + 0xcc) != 0 && i < 16) {
		if (((struct house*)g_7f4ca0)[idx].id != 0xffff && ((struct house*)g_7f4ca0)[idx].handle != *(int*) (e + 0xbc) && ((struct house*)g_7f4ca0)[idx].type < 10
		    && ((struct house*)g_7f4ca0)[idx].level > 0) {
			f = -fcn_00507ed0(*(float*) (e + 0xd0), fcn_00507f10(&((struct house*)g_7f4ca0)[idx], 4));
			v = (int) (f * 10.0f + 1.0f) * mult;
			fcn_004c54c0(*(int*) (e + 0xbc), ((struct house*)g_7f4ca0)[idx].handle, v, 1);
		}
		i++;
		*(int*) (e + 0xcc) = *(int*) (e + 0xcc) - 1;
		idx = (*(int*) (e + 0xc8) + idx) % 768;
	}
	*(int*) (e + 0xc4) = idx;
	*(pos14_7f4c00*) (e + 0x52) = g_7f4c00;
	if (fcn_00500cb0(e + 0xac, &g_7f4c00) == 1) {
		fcn_00500bb0((pos14_7f4c00*) (e + 0x52), 1, 0, 0);
		return;
	}
	fcn_00500bb0((pos14_7f4c00*) (e + 0x52), 0, 1, 0);
	*(int*) (e + 0x84) = fcn_004c5620(-1, e);
}
