
#include <string.h>

#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern unsigned short g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;
extern unsigned char g_773d75;

char* __cdecl gm_LookupEntityRecordById(int id);
void __cdecl cm_RequestTransferCurrencyNoKill(int, int, char, int);
void __cdecl gm_ModifyHealth(int, int);
void __cdecl cm_SendCopyEntityData(char* msg);
typedef struct F8 {
	int mask;
	int b;
} F8;
// SIZE 0x8

int __cdecl ai_FindEntityInFavorRange(char* p, int kind, F8 f, int c, float r, int* out);

/* ADDRESS: GOLDTL 0x0048e230 */
int __cdecl ai_RunSecretRoomMode1(char* entity, char* request, char* params)
{
	int found;
	char msg[0xf8];
	char* p;
	F8 f;

	p = gm_LookupEntityRecordById(*(int*) (request + 0xc));
	if (p == 0) {
		return 0;
	}
	gm_ModifyHealth(*(int*) (entity + 4), -*(int*) (request + 8));
	memset(msg, 0, sizeof(msg));
	msg[4] = (char) 0x99;
	*(int*) (msg + 8) = *(int*) (entity + 4);
	*(int*) (msg + 0xc) = *(int*) (request + 0xc);
	*(int*) (msg + 0x28) = (*(int*)&gm_GameTime);
	*(int*) (msg + 0x2c) = (*(int*)&g_7f4c04);
	*(int*) (msg + 0x30) = g_7f4c08;
	*(short*) (msg + 0x34) = g_7f4c0c;
	msg[0x36] = 2;
	*(int*) (msg + 0x60) = *(int*) (p + 4);
	*(int*) (msg + 0x5c) = *(int*) (request + 0xc);
	*(int*) (msg + 0x64) = -1;
	*(int*) (msg + 0x68) = 1;
	*(int*) (msg + 0x6c) = *(int*) (params + 0x10);
	if (*(char**) (p + 0x170) != 0) {
		*(int*) (msg + 0x58) = *(int*) (*(char**) (p + 0x170) + 1);
	} else if (*(char**) (p + 0x16c) != 0) {
		*(int*) (msg + 0x58) = *(int*) (*(char**) (p + 0x16c) + 1);
	} else {
		found = -1;
		f.mask = 0x7b4c4a0;
		f.b = 0;
		ai_FindEntityInFavorRange(p, 0, f, 0, 100.0f, &found);
		*(int*) (msg + 0x58) = found;
	}
	cm_SendCopyEntityData(msg);
	return 1;
}
