#include "client_types.h"
extern char gm_GameTime[];
#include "Develop/DieGildeAddOn/game/entity_record.h"
extern char g_68cb58[];
extern char g_6b5c60[];
extern int gm_CityEntity;

char* __cdecl gm_LookupEntityRecordById(int);
void __cdecl fcn_00500bb0(int*, int, int, int);
int __cdecl evt_FindScriptById(int);
void __cdecl evt_RequestScriptExit(int);
void __cdecl fcn_00529160(int, int, int, int);
void __cdecl io_FormatTextBuffer(int*, unsigned int, ...);
void __cdecl he_MessageBoxQuickjump(unsigned int, int, char*, int, int, int, int, char*, char*);
#include "Develop/DieGildeAddOn/game/ch_queue.h"
char* __cdecl ch_CreateAction(int, int, int);
char* __cdecl fcn_004934c0(char*);
void __cdecl fcn_005099e0(char*, char*);
void __cdecl fcn_004c4510(int, int);
void __cdecl cm_AppendPacketFieldDelta(int, int, int, int*);
void __cdecl fcn_004c5360(void);
int __cdecl fcn_0050a710(char*);
void __cdecl fcn_004c57e0(int, int);
int __cdecl fcn_004c4450(int);
int* __cdecl fcn_004c4480(int);
int __cdecl fcn_004c5980(int);
int __cdecl cut_FindCutsceneById(int);
void __cdecl he_FreeAction(char*);

/* ADDRESS: GOLDTL 0x0056e3c0 */
void __cdecl fcn_0056e3c0(char* eventState)
{
	char* s;
	char* obj;
	char* p;
	char c;
	int v;
	int i;
	char buf[0x514];

	if (*(int*) (eventState + 0x70) != -1) {
	} else {
		goto tail;
	}
	s = gm_LookupEntityRecordById(*(int*) (eventState + 0xac));
	if (s == 0) {
		goto tail;
	}
	if (*(int*) (s + 0x20c) != -1 && *(int*) (eventState + 0x70) != 6) {
		*(pos14_7f4c00*) (eventState + 0x52) = *(pos14_7f4c00*) gm_GameTime;
		fcn_00500bb0((int*) (eventState + 0x52), 0, 5, 0);
		return;
	}
	switch (*(int*) (eventState + 0x70)) {
	case -2:
	case -1:
		goto tail;
	case 0:
		obj = *(char**) (s + 0x184);
		if (obj == 0) {
			if ((*(unsigned char*) (eventState + 0x78) & 2) == 0) {
				goto tail;
			}
			*(int*) (eventState + 0x70) = 3;
			return;
		}
		if (*(int*) (obj + 0x28) != -1) {
			evt_RequestScriptExit(evt_FindScriptById(*(int*) (obj + 0x28)));
		}
		fcn_00529160(0, 0, *(unsigned short*) s, 0);
		if ((*(unsigned char*) (eventState + 0x78) & 2) != 0) {
			if (*(char**) (s + 0x16c) != 0) {
				c = *(char*) &((ENTITY_RECORD*) g_7f4ca0)[*(unsigned short*) (*(char**) (s + 0x16c) + 0x27)].entity_state;
				if (c == 6 || c == 7) {
					io_FormatTextBuffer((int*) (buf + 0x114), 0x42f4, *(unsigned short*) s, (int) *(char**) (s + 0x16c));
					v = *(int*) (*(char**) (s + 0x16c) + 1);
					he_MessageBoxQuickjump(
						*(unsigned int*) &((ENTITY_RECORD*) g_7f4ca0)[*(unsigned short*) (*(char**) (s + 0x16c) + 0x27)].entity_id,
						v, buf + 0x114, 0, 0x60a, v, -1, g_6b5c60, g_6b5c60);
				}
			}
		}
		*(int*) (s + 0x16c) = 0;
		*(int*) (eventState + 0x70) = *(int*) (eventState + 0x70) + 1;
		return;
	case 1:
		obj = *(char**) (s + 0x184);
		if (obj != 0 && *(int*) (obj + 0x28) != -1) {
			return;
		}
		*(int*) (eventState + 0x70) = *(int*) (eventState + 0x70) + 1;
		return;
	case 2:
		obj = *(char**) (s + 0x184);
		if (obj != 0) {
			ch_CancelActionQueue(obj);
			p = ch_CreateAction((int) *(char**) (s + 0x184), 0x36, 1);
			if (p != 0) {
				memcpy(p + 0xf0, g_68cb58, 0x19);
			}
		}
		*(pos14_7f4c00*) (eventState + 0x52) = *(pos14_7f4c00*) gm_GameTime;
		fcn_00500bb0((int*) (eventState + 0x52), 0, 0x1e, 0);
		*(int*) (eventState + 0x70) = *(int*) (eventState + 0x70) + 1;
		if ((*(unsigned char*) (eventState + 0x78) & 4) != 0) {
			goto tail;
		}
		return;
	case 3:
		c = *(char*) (s + 2);
		if (c != 6 && c != 7) {
			fcn_00500bb0((int*) (eventState + 0x52), 0, 2, 0);
			*(int*) (eventState + 0x70) = 4;
			return;
		}
		for (i = 0; i < 0x45; i++) {
			*(int*) (buf + i * 4) = 0;
		}
		*(char*) (buf + 0x08) = 8;
		*(char*) (buf + 0x26) = 0xa0;
		*(pos14_7f4c00*) (buf + 0x18) = *(pos14_7f4c00*) gm_GameTime;
		fcn_00500bb0((int*) (buf + 0x18), 0, 0x1e, 0);
		s = *(char**) (s + 4);
		*(int*) (buf + 0x14) = -1;
		*(char*) (buf + 0x30) = 1;
		*(int*) (buf + 0x0c) = (int) s;
		*(int*) (buf + 0x34) = (int) s;
		*(int*) (eventState + 0xb4) = fcn_004c5980((int) buf);
		fcn_00500bb0((int*) (eventState + 0x52), 0, 1, 0);
		*(int*) (eventState + 0x70) = 6;
		return;
	case 4:
		p = fcn_004934c0(s);
		if (p == 0) {
			*(int*) (eventState + 0x70) = 5;
			return;
		}
		fcn_005099e0(s, p);
		c = *(char*) (s + 2);
		if ((c == 6 || c == 7 || c == 5) && *(unsigned char*) (s + 0xd) > *(unsigned char*) (p + 0xd)) {
			fcn_004c4510((int) p, *(int*) (p + 4));
			cm_AppendPacketFieldDelta(1, 1, 0xd, (int*) (s + 0xd));
			fcn_004c5360();
		}
		fcn_004c57e0(*(int*) (s + 4), fcn_0050a710(s));
		he_FreeAction(eventState);
		return;
	case 5:
		fcn_005099e0(s, (char*) gm_CityEntity);
		fcn_004c57e0(*(int*) (s + 4), fcn_0050a710(s));
		he_FreeAction(eventState);
		return;
	case 6:
		v = fcn_004c4450(*(int*) (eventState + 0xb4));
		if (v == 0) {
			return;
		}
		if (v == 2) {
			*(pos14_7f4c00*) (eventState + 0x52) = *(pos14_7f4c00*) gm_GameTime;
			*(int*) (eventState + 0x70) = 4;
		} else {
			*(pos14_7f4c00*) (eventState + 0x52) = *(pos14_7f4c00*) gm_GameTime;
			*(int*) (eventState + 0xb0) = *(int*) fcn_004c4480(*(int*) (eventState + 0xb4));
			fcn_00500bb0((int*) (eventState + 0x52), 2, 0, 0);
			*(int*) (eventState + 0x70) = 7;
		}
		return;
	case 7:
		if (*(unsigned char*) (s + 8) > 0) {
			goto tail;
		}
		if (cut_FindCutsceneById(*(int*) (eventState + 0xb0)) != 0) {
			*(pos14_7f4c00*) (eventState + 0x52) = *(pos14_7f4c00*) gm_GameTime;
			fcn_00500bb0((int*) (eventState + 0x52), 2, 0, 0);
		} else {
			*(int*) (eventState + 0xb4) = -1;
			*(int*) (eventState + 0xb0) = -1;
			*(pos14_7f4c00*) (eventState + 0x52) = *(pos14_7f4c00*) gm_GameTime;
			*(int*) (eventState + 0x70) = 4;
		}
		return;
	default:
		return;
	}
tail:
	he_FreeAction(eventState);
}
