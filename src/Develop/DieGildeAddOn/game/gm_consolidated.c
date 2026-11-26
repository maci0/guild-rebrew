#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern unsigned short g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;
extern char s_67fb2c[];

char* __cdecl gm_LookupEntityRecordById(int id);
char* __cdecl gm_StartFilteredEntitySearch(int a, int b, int c);
unsigned short __cdecl gm_RandomMod(int n);
void __cdecl cm_SendLogAction(char* s);
void __cdecl cm_SendCopyEntityData(char* msg);
void __cdecl cm_SendTraceEnd(char* s);
extern char s_67fb40[];

char* __cdecl gm_LookupEntityRecordById(int id);
#include "Develop/DieGildeAddOn/game/spiel.h"
float __cdecl gm_RandomFloat01(void);
void __cdecl cm_SendLogAction(char* s);
void __cdecl cm_SendCopyEntityData(char* msg);
void __cdecl fcn_004c6ae0(int id, int k);
void __cdecl cm_SendTraceEnd(char* s);
extern char s_67fb50[];

void __cdecl cm_SendLogAction(char* s);
void __cdecl cm_SendCopyEntityData(char* msg);
void __cdecl fcn_004c6ae0(int id, int k);
void __cdecl cm_SendTraceEnd(char* s);

/* ADDRESS: GOLDTL 0x004aaa60 */
int __cdecl fcn_004aaa60(char* actor, int a2, char* x)
{
	char msg[0xf8];
	char* target;

	if (x[0] != 7) {
		return 0;
	}
	target = gm_LookupEntityRecordById(*(int*) (x + 4));
	if (!target) {
		return 0;
	}
	gm_StartFilteredEntitySearch(1, 5, 0xa);
	msg[4] = 0x35;
	msg[0x36] = 2;
	*(int*) (msg + 8) = *(int*) (actor + 4);
	*(int*) (msg + 0xc) = *(int*) (actor + 4);
	*(int*) (msg + 0x58) = (*(int*)&gm_GameTime);
	*(int*) (msg + 0x5c) = (*(int*)&g_7f4c04);
	*(int*) (msg + 0x60) = g_7f4c08;
	*(short*) (msg + 0x64) = g_7f4c0c;
	msg[0x6d] = (char) gm_RandomMod(0x1d);
	*(int*) (msg + 0x68) = *(int*) (target + 4);
	cm_SendLogAction(s_67fb2c);
	cm_SendCopyEntityData(msg);
	cm_SendTraceEnd(s_67fb2c);
	return 1;
}

/* ADDRESS: GOLDTL 0x004aab30 */
int __cdecl fcn_004aab30(char* actor, int a2, char* x)
{
	char msg[0xf8];
	float f;
	char* target;

	if (x[0] != 7) {
		return 0;
	}
	target = gm_LookupEntityRecordById(*(int*) (x + 4));
	if (!target) {
		return 0;
	}
	cm_SendLogAction(s_67fb40);
	f = fcn_00507e70(actor, target, 4);
	if (gm_RandomFloat01() + f >= 1.0f) {
		msg[4] = 0x2e;
		*(int*) (msg + 8) = *(int*) (target + 4);
		*(int*) (msg + 0xc) = -1;
		msg[0x36] = 2;
		*(int*) (msg + 0x5c) = *(int*) (actor + 4);
		*(int*) (msg + 0x58) = *(int*) (target + 4);
		cm_SendCopyEntityData(msg);
	}
	fcn_004c6ae0(*(int*) (actor + 4), -2);
	cm_SendTraceEnd(s_67fb40);
	return 1;
}

/* ADDRESS: GOLDTL 0x004aac00 */
int __cdecl aip_ExecAnschwaerzen(char* actor, int a2, char* x)
{
	char msg[0xf8];

	*(int*) (msg + 8) = *(int*) (x + 8);
	*(int*) (msg + 0x5c) = *(int*) (actor + 4);
	*(int*) (msg + 0x58) = *(int*) (x + 4);
	*(int*) (msg + 0x60) = *(int*) (x + 8);
	*(int*) (msg + 0x28) = (*(int*)&gm_GameTime);
	msg[4] = 0x2f;
	*(int*) (msg + 0xc) = -1;
	msg[0x36] = 1;
	*(int*) (msg + 0x2c) = (*(int*)&g_7f4c04);
	*(int*) (msg + 0x30) = g_7f4c08;
	*(short*) (msg + 0x34) = g_7f4c0c;
	cm_SendLogAction(s_67fb50);
	cm_SendCopyEntityData(msg);
	fcn_004c6ae0(*(int*) (actor + 4), -3);
	cm_SendTraceEnd(s_67fb50);
	return 1;
}
