
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/DieGildeAddOn/game/game_player.h"

unsigned short __cdecl gm_RandomMod(int);
int __cdecl cm_GetCommandStatus(int);
void __cdecl he_FreeAction(char*);
int __cdecl cm_SendSetHE(int, char*);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl he_PostEntityMessage(int, int, char*, int, int, void*);
void __cdecl gm_AddTime(char*, int, int, int);
int __cdecl gm_PickRandomGedicht(short);
unsigned short __cdecl gm_PickRandomGedichtVariant(int);
char* __cdecl gm_GetBardEventEntry(short);
char* __cdecl evt_FindScriptById(int);
char* __cdecl evt_LoadGfxScript(char*);
void __cdecl evt_CallScriptFunction(char*, int, int);
void __cdecl evt_RequestScriptExit(char*);
void __cdecl d3_SelectSceneContext(int, int);
int __cdecl sprintf(char*, const char*, ...);
void __cdecl cm_RequestChangeBits(int, int, int, int, int);
void __cdecl d3_FreeEventGfxSlot(int);

#include "client_types.h"

extern pos14_7f4c00 gm_GameTime;

/* ADDRESS: GOLDTL 0x00555d30 */
void __cdecl he_RunBardeEvent(char* obj)
{
	char buf[0x200];
	char* p;
	char* e;
	char* q;
	char* x;
	int t;
	int id;
	int* base;
	int j;

	if (*(int*) (obj + 0x70) == -1 || *(int*) (obj + 0x70) == -2) {
		he_FreeAction(obj);
		return;
	}
	if (*(int*) (obj + 0x84) != -1 && cm_GetCommandStatus(*(int*) (obj + 0x84)) == 0) {
		return;
	}
	*(int*) (obj + 0x84) = -1;
	switch (*(int*) (obj + 0x70)) {
	case 0:
		if (*(unsigned char*) (obj + 0x78) & 4) {
			return;
		}
		id = gm_PickRandomGedicht(*(short*) (obj + 0xac));
		*(short*) (obj + 0xac) = id;
		*(short*) (obj + 0xae) = gm_PickRandomGedichtVariant(id);
		base = (int*) (obj + 0x52);
		*(pos14_7f4c00*) base = gm_GameTime;
		base[0] += gm_RandomMod(4) + 3;
		*(unsigned short*) (obj + 0x56) = 10;
		*(int*) (obj + 0x58) = 0;
		cm_SendSetHE(1, obj);
		*(int*) (obj + 0x84) = -1;
		return;
	case 1:
		if (*(unsigned char*) (obj + 0x78) & 4) {
			return;
		}
		io_FormatTextBuffer(buf, 0x1e29);
		for (j = 0x7f4ca2; j < 0x85a0a2; j += 0x21c) {
			if (*(unsigned short*) (j - 2) == 0xffff) {
				continue;
			}
			if (*(char*) j != 6 && *(char*) j != 7) {
				continue;
			}
			he_PostEntityMessage(*(int*) (j + 2), *(int*) (obj + 4), buf, 0,
				     0x601, (void*) 0x6b5c60);
		}
		gm_AddTime(obj + 0x52, 0, 5, 0);
		*(int*) (obj + 0x84) = cm_SendSetHE(2, obj);
		return;
	case 2:
		base = (int*) (obj + 0x52);
		*(pos14_7f4c00*) base = gm_GameTime;
		gm_AddTime((char*) base, 0, 5, 0);
		e = evt_FindScriptById(*(int*) (obj + 0xb4));
		if (*(unsigned short*) (obj + 0x56) < 0x14) {
			if (e == 0 || *(int*) e != 0x68427244) {
				*(int*) (obj + 0xb4) = -1;
				x = gm_GetBardEventEntry(*(unsigned short*) (obj + 0xac));
				sprintf(buf, (char*) 0x67d444, *(int*) (x + 8));
				t = *(int*) 0x6b8010;
				d3_SelectSceneContext(0, 1);
				q = evt_LoadGfxScript((char*) 0x6a5edc);
				if (q != 0) {
					*(int*) q = 0x68427244;
					*(int*) (obj + 0xb4) = *(int*) (q + 0x100);
					evt_CallScriptFunction(q, 1, *(int*) (x + 8));
					*(int*) (q + 0x104) = 0;
				}
				d3_SelectSceneContext(t, 1);
			}
		} else {
			if (e != 0 && *(int*) e == 0x68427244) {
				evt_RequestScriptExit(e);
			}
			gm_AddTime((char*) base, 0, 5, 0);
			*(int*) (obj + 0x70) = 3;
			return;
		}
		*(int*) (obj + 0x70) = 2;
		if (*(int*) (obj + 0x88) != 0 &&
		    (*(int*) (g_774970 * 0x21c + 0x7f4e68) & 0x20000) != 0) {
			d3_FreeEventGfxSlot(*(int*) (obj + 0x88));
			*(int*) (obj + 0x88) = 0;
		}
		return;
	case 3:
		if (*(unsigned char*) (obj + 0x78) & 2) {
			for (j = 0x7f4e68; j < 0x85a268; j += 0x21c) {
				if (*(unsigned short*) (j - 0x1c8) == 0xffff) {
					continue;
				}
				if ((*(int*) j & 0x20000) == 0) {
					continue;
				}
				cm_RequestChangeBits(*(int*) (j - 0x1c4), 0x1c8, 4, 0, 0x20000);
			}
		}
		*(pos14_7f4c00*) (obj + 0x52) = gm_GameTime;
		id = *(int*) (obj + 0x52) + 1;
		*(unsigned short*) (obj + 0x56) = 6;
		*(int*) (obj + 0x52) = id;
		*(int*) (obj + 0x58) = 0;
		if (*(int*) (obj + 0x88) != 0) {
			d3_FreeEventGfxSlot(*(int*) (obj + 0x88));
			*(int*) (obj + 0x88) = 0;
		}
		if (*(unsigned char*) (obj + 0x78) & 2) {
			*(int*) (obj + 0x84) = cm_SendSetHE(0, obj);
		}
		*(int*) (obj + 0x84) = -1;
		return;
	}
}
