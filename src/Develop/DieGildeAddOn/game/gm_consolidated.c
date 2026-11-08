#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;
extern unsigned short g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;
extern char s_67fb2c[];

char* __cdecl gm_LookupEntityRecordById(int id);
char* __cdecl gm_StartFilteredEntitySearch(int a, int b, int c);
unsigned short __cdecl gm_RandomMod(int n);
void __cdecl fcn_004c4eb0(char* s);
void __cdecl fcn_004c5530(char* msg);
void __cdecl fcn_004c4ef0(char* s);
extern char s_67fb40[];

char* __cdecl gm_LookupEntityRecordById(int id);
#include "Develop/DieGildeAddOn/game/spiel.h"
float __cdecl gm_RandomFloat01(void);
void __cdecl fcn_004c4eb0(char* s);
void __cdecl fcn_004c5530(char* msg);
void __cdecl fcn_004c6ae0(int id, int k);
void __cdecl fcn_004c4ef0(char* s);
extern char s_67fb50[];

void __cdecl fcn_004c4eb0(char* s);
void __cdecl fcn_004c5530(char* msg);
void __cdecl fcn_004c6ae0(int id, int k);
void __cdecl fcn_004c4ef0(char* s);

/* ADDRESS: GOLDTL 0x004aaa60 */
int __cdecl fcn_004aaa60(char* a1, int a2, char* x)
{
	char msg[0xf8];
	char* p;

	if (x[0] != 7) {
		return 0;
	}
	p = gm_LookupEntityRecordById(*(int*) (x + 4));
	if (!p) {
		return 0;
	}
	gm_StartFilteredEntitySearch(1, 5, 0xa);
	msg[4] = 0x35;
	msg[0x36] = 2;
	*(int*) (msg + 8) = *(int*) (a1 + 4);
	*(int*) (msg + 0xc) = *(int*) (a1 + 4);
	*(int*) (msg + 0x58) = (*(int*)&g_7f4c00);
	*(int*) (msg + 0x5c) = (*(int*)&g_7f4c04);
	*(int*) (msg + 0x60) = g_7f4c08;
	*(short*) (msg + 0x64) = g_7f4c0c;
	msg[0x6d] = (char) gm_RandomMod(0x1d);
	*(int*) (msg + 0x68) = *(int*) (p + 4);
	fcn_004c4eb0(s_67fb2c);
	fcn_004c5530(msg);
	fcn_004c4ef0(s_67fb2c);
	return 1;
}

/* ADDRESS: GOLDTL 0x004aab30 */
int __cdecl fcn_004aab30(char* a1, int a2, char* x)
{
	char msg[0xf8];
	float f;
	char* p;

	if (x[0] != 7) {
		return 0;
	}
	p = gm_LookupEntityRecordById(*(int*) (x + 4));
	if (!p) {
		return 0;
	}
	fcn_004c4eb0(s_67fb40);
	f = fcn_00507e70(a1, p, 4);
	if (gm_RandomFloat01() + f >= 1.0f) {
		msg[4] = 0x2e;
		*(int*) (msg + 8) = *(int*) (p + 4);
		*(int*) (msg + 0xc) = -1;
		msg[0x36] = 2;
		*(int*) (msg + 0x5c) = *(int*) (a1 + 4);
		*(int*) (msg + 0x58) = *(int*) (p + 4);
		fcn_004c5530(msg);
	}
	fcn_004c6ae0(*(int*) (a1 + 4), -2);
	fcn_004c4ef0(s_67fb40);
	return 1;
}

/* ADDRESS: GOLDTL 0x004aac00 */
int __cdecl fcn_004aac00(char* a1, int a2, char* x)
{
	char msg[0xf8];

	*(int*) (msg + 8) = *(int*) (x + 8);
	*(int*) (msg + 0x5c) = *(int*) (a1 + 4);
	*(int*) (msg + 0x58) = *(int*) (x + 4);
	*(int*) (msg + 0x60) = *(int*) (x + 8);
	*(int*) (msg + 0x28) = (*(int*)&g_7f4c00);
	msg[4] = 0x2f;
	*(int*) (msg + 0xc) = -1;
	msg[0x36] = 1;
	*(int*) (msg + 0x2c) = (*(int*)&g_7f4c04);
	*(int*) (msg + 0x30) = g_7f4c08;
	*(short*) (msg + 0x34) = g_7f4c0c;
	fcn_004c4eb0(s_67fb50);
	fcn_004c5530(msg);
	fcn_004c6ae0(*(int*) (a1 + 4), -3);
	fcn_004c4ef0(s_67fb50);
	return 1;
}
