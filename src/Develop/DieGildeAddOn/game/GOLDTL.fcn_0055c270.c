#include <string.h>
#include <stdio.h>
#include "Develop/DieGildeAddOn/game/building_prototype.h"
#include "client_types.h"

extern unsigned char g_773d75;
extern char* gm_CityEntity;
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "game_data.h"
typedef struct StateProto { unsigned char kind; unsigned char rest[0x24c]; } StateProto;
extern char g_7f4ca0[];
extern pos14_7f4c00 gm_GameTime;
#include "Develop/DieGildeAddOn/game/entity_record.h"
typedef struct Msg55c270 {
	char pad0[4];
	unsigned char kind;
	char pad05[3];
	int x8;
	int xc;
	char pad10[0x36 - 0x10];
	unsigned char b36;
	char pad37[0x58 - 0x37];
	int x58;
	char pad5c[0xf8 - 0x5c];
} Msg55c270;

typedef struct Req55c270 {
	int id;
	int x4;
	char pad8[0x74];
} Req55c270;

extern char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
extern int __cdecl gm_CompareGameTime(char*, char*);
extern unsigned char* __cdecl fcn_00502cd0(int, int, int, int);
extern int __cdecl cm_SendSellObjekt(int, int, int, int, char, int);
extern int __cdecl cm_GetCommandStatus(int);
extern char* __cdecl cm_GetCommandResult(int);
extern void __cdecl fcn_004f2ba0(char*, char*, int);
extern void __cdecl cm_SendCopyEntityData(char*);
extern char* __cdecl fcn_0050dc90(char*);
extern void __cdecl he_FreeAction(char*);
extern void __cdecl gm_AddTime(pos14_7f4c00*, int, int, int);
extern void __cdecl cm_RequestSysMessage(int, Req55c270*);
extern void __cdecl io_FormatTextBuffer(char*, int, ...);
extern void __cdecl he_MessageBoxQuickjump(int, int, char*, int, int, int, int, char*, char*);

/* Handles the follow-up action state of an entity: it looks the action record
 * up, reports it to the action handler and advances the entity's queue. */
#pragma optimize("y", off)
/* ADDRESS: GOLDTL 0x0055c270 */
void __cdecl fcn_0055c270(char* o)
{
	unsigned char* rec;
	unsigned char* e;
	unsigned char* src;
	unsigned char* p;
	unsigned char* h;
	int kind;
	void* fill_dst;
	int fill_count;
	char buf[0x400];

	switch (*(int*) (o + 0x70)) {
	case 0:
		*(int*) (o + 0x70) = 1;
		break;
	case 1:
		if (gm_CompareGameTime(o + 0x52, (char*) 0x7f4c00) < 0) {
			e = (unsigned char*) gm_StartFilteredEntitySearch(1, 1, *(int*) (o + 0x10));
			if (e == 0) {
				he_FreeAction(o);
				return;
			}
			h = fcn_00502cd0(*(int*) (e + 0x5d), 1, 1, *(int*) (o + 0xb0));
			*(int*) (o + 0xb4) = cm_SendSellObjekt(*(int*) (o + 0xb0), -1,
				*(unsigned short*) (o + 0xac), 1, *(char*) &g_773d75, 0);
			(*(int*) (o + 0x70))++;
		}
		break;
	case 2:
		if (cm_GetCommandStatus(*(int*) (o + 0xb4)) == 0)
			break;
		rec = (unsigned char*) cm_GetCommandResult(*(int*) (o + 0xb4));
		e = (unsigned char*) gm_StartFilteredEntitySearch(1, 1, *(int*) (o + 0x10));
		if (e == 0 || rec == 0) {
			he_FreeAction(o);
			return;
		}
		if (*(unsigned short*) rec == 0x1f9) {
			fcn_004f2ba0((char*) &((ENTITY_RECORD*) 0x7f4ca0)[*(unsigned short*) (e + 0x27)],
				(char*) e, 1);
		} else if (*(unsigned short*) rec == 0x1fd) {
			fcn_004f2ba0((char*) &((ENTITY_RECORD*) 0x7f4ca0)[*(unsigned short*) (e + 0x27)],
				(char*) e, 2);
		} else if (*(unsigned short*) rec == 0x201) {
			fcn_004f2ba0((char*) &((ENTITY_RECORD*) 0x7f4ca0)[*(unsigned short*) (e + 0x27)],
				(char*) e, 3);
		} else if (*(unsigned short*) rec == 0x12d) {
			Msg55c270 msg;
			fill_dst = &msg;
            fill_count = sizeof(msg);
            __asm {
                mov edi, fill_dst
                mov ebx, fill_count
                xor eax, eax
                lea ecx, [edi+edi*2]
                and ecx, 3
                sub ebx, ecx
                jle short L_fill_tail
                rep stosb
                mov ecx, ebx
                and ebx, 3
                shr ecx, 2
                rep stosd
            L_fill_tail:
                add ecx, ebx
                rep stosb
            }
			msg.kind = 0x2a;
			msg.x8 = *(int*) (gm_CityEntity + 4);
			msg.xc = *(int*) (e + 1);
			msg.b36 = 2;
			msg.x58 = *(int*) (e + 1);
			cm_SendCopyEntityData((char*) &msg);
		}
		if (*(char*) &((ENTITY_RECORD_VIEW*) g_7f4ca0)[*(unsigned short*) (e + 0x27)].entity_type == 6) {
			char tmp[0x80];
			char name[0x80];

			h = fcn_00502cd0(*(int*) (e + 0x5d), 1, 1, *(int*) (o + 0xb0));
			src = (unsigned char*) (g_item_def_table +
				*(unsigned short*) (o + 0xac) * 0x41);
			if (h != 0 && *(unsigned short*) h != 0xfd) {
				kind = 0x606;
				if (((BUILDING_PROTOTYPE *)lpGebaeudePROT)[*e].category != 6) {
					p = (unsigned char*) fcn_0050dc90((char*) e);
					if (p != 0 && p[2] == 1 && (p[0x1b4] & 1) != 0 &&
					    *(int*) (o + 0xb8) != 0)
						kind = 0x60b;
				}
				strcpy(tmp, (char*) src + 1);
				_strupr(tmp);
				sprintf(name, (char*) 0x68b7ac, tmp);
				io_FormatTextBuffer(buf, 0x1c2b, e, *(unsigned short*) (o + 0xac) * 2 + 0x9a8);
				he_MessageBoxQuickjump(*(int*) &((ENTITY_RECORD*) 0x7f4ca0)[
						*(unsigned short*) (e + 0x27)].entity_id,
					*(int*) (o + 0x10), buf, 0, kind, *(int*) (e + 1),
					*(int*) (o + 0xb0), name, (char*) 0x6a6248);
			} else {
				kind = 0x606;
				if (((BUILDING_PROTOTYPE *)lpGebaeudePROT)[*e].category != 6) {
					p = (unsigned char*) fcn_0050dc90((char*) e);
					if (p != 0 && p[2] == 1 && (p[0x1b4] & 1) != 0 &&
					    *(int*) (o + 0xb8) != 0)
						kind = 0x60b;
				}
				io_FormatTextBuffer(buf, 0x1c2d, e, *(unsigned short*) (o + 0xac) * 2 + 0x9a8);
				he_MessageBoxQuickjump(*(int*) &((ENTITY_RECORD*) 0x7f4ca0)[
						*(unsigned short*) (e + 0x27)].entity_id,
					*(int*) (o + 0x10), buf, 0, kind, *(int*) (e + 1),
					-1, 0, (char*) 0x6a6234);
			}
			rec[0x13] |= 0xa0;
		}
		{
			Req55c270 m;

			h = fcn_00502cd0(*(int*) (e + 0x5d), 1, 1, *(int*) (o + 0xb0));
			*(pos14_7f4c00*) &m = gm_GameTime;
			gm_AddTime((pos14_7f4c00*) &m, 0, 0, 1);
			m.id = *(int*) (e + 1);
			m.x4 = *(int*) (h + 2);
			cm_RequestSysMessage(4, &m);
		}
		he_FreeAction(o);
		return;
	}
}
#pragma optimize("", on)
