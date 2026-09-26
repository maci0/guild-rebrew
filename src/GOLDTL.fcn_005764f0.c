// FUNCTION: GOLD 0x0056e0b0
// SIZE: 600
// FUNCTION: GOLDTL 0x5764f0
// SIZE: 600

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;
extern float g_696550[];
extern float g_696540[];

int __cdecl fcn_00500e20(pos14_7f4c00*);
char* __cdecl fcn_00508e40(int);
int __cdecl ahm_CheckFlag(char*);
unsigned short __cdecl fcn_0042e410(int);
float __cdecl gm_RandomFloat01(void);
void __cdecl fcn_004eeb50(char*, float);
int __cdecl fcn_004c5620(int, char*);
int __cdecl fcn_004ecf00(char*, int*, int*, int);
void __cdecl sub_00576750(char*, char*, char*, int);
void __cdecl fcn_00546190(char*);

void __cdecl fcn_005764f0(char* e)
{
	int a;
	int b;
	int k;
	char* o;
	char* sp;
	int s;
	float v;

	k = (fcn_00500e20(&g_7f4c00) + 1) % 4;
	o = fcn_00508e40(*(int*) (e + 0xc));
	if (*(int*) (e + 0x70) == -1 || *(int*) (e + 0x70) == -2) {
		fcn_00546190(e);
		return;
	}
	if ((e[0x78] & 4) != 0) {
		return;
	}
	if (o == 0 || ahm_CheckFlag(o) == 0 || *(int*) (e + 0x70) == -2 || *(int*) (e + 0x70) == -1) {
		fcn_004c5620(-1, e);
		return;
	}
	sp = *(char**) (*(char**) (o + 0x16c) + 0x65);
	*(pos14_7f4c00*) (e + 0x52) = g_7f4c00;
	((pos14_7f4c00*) (e + 0x52))->a++;
	*(short*) (e + 0x56) = fcn_0042e410((int) (g_696550[k] - g_696540[k])) + (int) g_696540[k];
	*(int*) (e + 0x58) = fcn_0042e410(4) * 15;
	if (*(int*) (e + 0xac) != 0) {
		fcn_004eeb50(o, (gm_RandomFloat01() + 1.0f) * 0.25f);
		*(int*) (e + 0xac) = 0;
		fcn_004c5620(0, e);
		return;
	}
	s = fcn_004ecf00(*(char**) (o + 0x16c), &b, &a, 1);
	if ((gm_RandomFloat01() + 1.0f) * 0.25f > *(float*) (sp + 4)) {
		sub_00576750(o, e, *(char**) (o + 0x16c), s);
		fcn_004c5620(0, e);
		return;
	}
	switch (s) {
	case 1:
		v = -((gm_RandomFloat01() + 1.0f) * 0.1f);
		break;
	case 2:
		v = -(gm_RandomFloat01() * 0.15f + 0.1f);
		break;
	case 3:
	case 4:
		v = -(gm_RandomFloat01() * 0.2f + 0.1f);
		break;
	default:
		v = gm_RandomFloat01() * 0.15f + 0.05f;
		break;
	}
	fcn_004eeb50(o, v);
	fcn_004c5620(0, e);
}
