


#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern float g_696550[];
extern float g_696540[];

int __cdecl gm_GetSeason(pos14_7f4c00*);
char* __cdecl gm_LookupEntityRecordById(int);
int __cdecl ahm_CheckFlag(char*);
unsigned short __cdecl gm_RandomMod(int);
float __cdecl gm_RandomFloat01(void);
void __cdecl ahm_SendSetFloatValue(char*, float);
int __cdecl cm_SendSetHE(int, char*);
int __cdecl he_GetActionProgress(char*, int*, int*, int);
void __cdecl he_TriggerAhmLabEvent(char*, char*, char*, int);
void __cdecl he_FreeAction(char*);

void __cdecl he_RunAhmAction0x98(char* e)
{
	int a;
	int b;
	int k;
	char* o;
	char* sp;
	int s;
	float v;

	k = (gm_GetSeason(&gm_GameTime) + 1) % 4;
	o = gm_LookupEntityRecordById(*(int*) (e + 0xc));
	if (*(int*) (e + 0x70) == -1 || *(int*) (e + 0x70) == -2) {
		he_FreeAction(e);
		return;
	}
	if ((e[0x78] & 4) != 0) {
		return;
	}
	if (o == 0 || ahm_CheckFlag(o) == 0 || *(int*) (e + 0x70) == -2 || *(int*) (e + 0x70) == -1) {
		cm_SendSetHE(-1, e);
		return;
	}
	sp = *(char**) (*(char**) (o + 0x16c) + 0x65);
	*(pos14_7f4c00*) (e + 0x52) = gm_GameTime;
	((pos14_7f4c00*) (e + 0x52))->a++;
	*(short*) (e + 0x56) = gm_RandomMod((int) (g_696550[k] - g_696540[k])) + (int) g_696540[k];
	*(int*) (e + 0x58) = gm_RandomMod(4) * 15;
	if (*(int*) (e + 0xac) != 0) {
		ahm_SendSetFloatValue(o, (gm_RandomFloat01() + 1.0f) * 0.25f);
		*(int*) (e + 0xac) = 0;
		cm_SendSetHE(0, e);
		return;
	}
	s = he_GetActionProgress(*(char**) (o + 0x16c), &b, &a, 1);
	if ((gm_RandomFloat01() + 1.0f) * 0.25f > *(float*) (sp + 4)) {
		he_TriggerAhmLabEvent(o, e, *(char**) (o + 0x16c), s);
		cm_SendSetHE(0, e);
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
	ahm_SendSetFloatValue(o, v);
	cm_SendSetHE(0, e);
}
