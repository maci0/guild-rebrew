#include <string.h>
#include "client_types.h"

typedef struct
{
	int x0;
	int n;
	int x8[16];
	unsigned short x48[16];
	int x68[16];
	int xa8;
	int xac;
	int xb0;
	char* xb4;
} Stats;

/* The decoded record and the wire packet share one stack buffer. */
typedef union
{
	Stats stats;
	unsigned char msg[0x114];
} MsgBuf;
#include "client_data.h"
extern float g_664168;
extern char* __cdecl gm_LookupEntityRecordById(int);
extern void __cdecl he_AssignActionSlot(int, int, int, char*);
extern int __cdecl ch_StartMovement(int, int, int, char*, int, char*);
extern int __cdecl fcn_004c5620(int, char*);
extern int __cdecl cm_GetCommandStatus(int);
extern char* __cdecl cm_GetCommandResult(int);
extern int __cdecl cut_FindCutsceneById(int);
extern void __cdecl gm_AddTime(pos14_7f4c00*, int, int, int);
extern int __cdecl gm_CompareGameTime(pos14_7f4c00*, pos14_7f4c00*);
extern void __cdecl he_FreeAction(char*);
extern void __cdecl d3_SelectSceneContext(int, int);
extern char* __cdecl fcn_00445600(int, int, int, char*);
extern void __cdecl d3_TransformPoint(char*, char*, float*);
extern int __cdecl CompareVector3WithinTolerance(float*, float*, float);
extern void __cdecl he_CharacterBehavior(char*, int);
extern char* __cdecl he_StartHandlungSearch(int, int, int);
extern char* __cdecl he_fn_Handlung(void);
extern char* __cdecl gm_FindRecordById(int);
extern int __cdecl gm_CalcEntityInventoryStats(char*, Stats*);
extern char* __cdecl fcn_00502cd0(int, ...);
extern char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
extern void* __cdecl cut_FindCutscene(int, int);
extern int __cdecl gm_RandomMod(unsigned short);
extern void __cdecl gm_EquipDuelist(char*, unsigned char);
extern int __cdecl fcn_004c5980(void*);
#include "Develop/DieGildeAddOn/game/game_data.h"
/* ADDRESS: GOLDTL 0x0056b700 */
void __cdecl he_RunUeberfall(char* obj)
{
	int count;
	int i;
	int prev;
	int nearby;
	char* door;
	int saved;
	char* list[4];
	pos14_7f4c00 pos;
	MsgBuf buf;
	char* sel[3];
	char* rec;
	char* slot;
	char* cur;
	char* iter;
	char* ent;
	int code;
	int limit;
	int r;
	int v11;
	unsigned char mode;

	code = *(int*) (obj + 0x84);
	if (code != -1 && !cm_GetCommandStatus(code))
		return;
	*(int*) (obj + 0x84) = -1;
	switch (*(int*) (obj + 0x70)) {
	case 0:
		if (*(unsigned char*) (obj + 0x78) & 2) {
			count = 0;
			iter = obj + 0x8c;
			*(int*) (obj + 0xe4) = 0;
			for (i = 8; i != 0; i--) {
				if (*(int*) iter != -1) {
					rec = gm_LookupEntityRecordById(*(int*) iter);
					if (rec != 0) {
						he_AssignActionSlot(0, 0, *(unsigned short*) rec, obj);
						ch_StartMovement(*(int*) iter, -1, -1, obj + 0xac, 1, (char*) 0x6a6aa0);
						*(int*) (obj + 0xe4) += *(unsigned char*) (rec + 0x82);
						count++;
					}
				}
				iter += 4;
			}
			if (count != 0) {
				*(unsigned int*) (obj + 0xe4) /= count;
			} else {
				*(int*) (obj + 0x84) = fcn_004c5620(-1, obj);
				*(int*) (obj + 0xe4) = 0;
				return;
			}
		}
		*(pos14_7f4c00*) (obj + 0x52) = gm_GameTime;
		gm_AddTime((pos14_7f4c00*) (obj + 0x52), 0, 0x1e, 0);
		*(int*) (obj + 0x70) = *(int*) (obj + 0x70) + 1;
		return;
	case 1:
		goto label_56b858;
	case 2:
		if (!cm_GetCommandStatus(*(int*) (obj + 0xdc)))
			return;
		cur = cm_GetCommandResult(*(int*) (obj + 0xdc));
		if (cur != 0) {
			*(int*) (obj + 0xe0) = *(int*) cur;
			*(pos14_7f4c00*) (obj + 0x52) = gm_GameTime;
			gm_AddTime((pos14_7f4c00*) (obj + 0x52), 0, 1, 0);
			*(int*) (obj + 0x70) = 3;
			return;
		}
		*(int*) (obj + 0x84) = fcn_004c5620(1, obj);
		return;
	case 3:
		if (!cut_FindCutsceneById(*(int*) (obj + 0xe0))) {
			*(pos14_7f4c00*) (obj + 0x52) = gm_GameTime;
			gm_AddTime((pos14_7f4c00*) (obj + 0x52), 0, 0, 1);
			*(int*) (obj + 0x70) = -1;
			return;
		}
		*(pos14_7f4c00*) (obj + 0x52) = gm_GameTime;
		gm_AddTime((pos14_7f4c00*) (obj + 0x52), 0, 5, 0);
		return;
	case -2:
	case -1:
		if (*(unsigned char*) (obj + 0x78) & 2) {
			ent = gm_StartFilteredEntitySearch(1, 1, *(int*) (obj + 0x10));
			iter = obj + 0x8c;
			for (i = 8; i != 0; i--) {
				if (*(int*) iter != -1) {
					rec = gm_LookupEntityRecordById(*(int*) iter);
					if (rec != 0) {
						if (ent != 0)
							ch_StartMovement(*(int*) (rec + 4), *(int*) (ent + 1), -1, 0, 0, (char*) 0x6a6aa0);
						he_AssignActionSlot(0, 0, *(unsigned short*) rec, 0);
					}
				}
				iter += 4;
			}
		}
		he_FreeAction(obj);
		return;
	default:
		return;
	}
label_56b858:
	if (*(unsigned char*) (obj + 0x78) & 2) {
		saved = *(int*) &d3_CurrentContextIndex;
		nearby = 1;
		door = 0;
		prev = -1;
		count = 0;
		list[0] = 0;
		list[1] = 0;
		list[2] = 0;
		d3_SelectSceneContext(0, 1);
		door = fcn_00445600(0, 0x100, 0, obj + 0xac);
		if (door != 0)
			d3_TransformPoint(door, door + 0x4c, (float*) &pos);
		for (i = 0, iter = obj + 0x8c; i < 8; i++, iter += 4) {
			if (*(int*) iter == -1)
				continue;
			cur = gm_LookupEntityRecordById(*(int*) iter);
			if (cur == 0)
				continue;
			cur = *(char**) (*(int*) (cur + 0x184) + 0x34);
			if (!CompareVector3WithinTolerance((float*) (cur + 0x4c), (float*) &pos, 25000.0f)) {
				nearby = 0;
				break;
			}
		}
		he_CharacterBehavior(obj, (int) &pos);
		list[3] = he_StartHandlungSearch(1, 0, 0x51);
		ent = he_StartHandlungSearch(1, 0, 0xf);
		if (nearby) {
			while (door != 0 && ent != 0 && count < 3) {
				if (*(char*) (ent + 0xf0) == 0 &&
				    *(unsigned short*) (ent + 8) != *(unsigned short*) (obj + 8) &&
				    (prev == -1 ||
				     prev == *(int*) ((unsigned int) *(unsigned short*) (ent + 8) * 0x21c + (unsigned long)&g_7f4ca4))) {
					cur = gm_FindRecordById(*(int*) (ent + 0xac));
					if (cur == 0)
						goto next;
					r = CompareVector3WithinTolerance((float*) (*(int*) (*(int*) (cur + 0x3b) + 0x34) + 0x4c), (float*) &pos, 1500.0f);
					gm_CalcEntityInventoryStats(cur, &buf.stats);
					code = buf.stats.xb0;
					if (code <= 0)
						goto next;
					v11 = (int) ((double) *(unsigned int*) (obj + 0xe4) * g_664168);
					if (v11 == 0) {
						if (code <= 100 || code >= 500) {
							if (!r)
								goto next;
							goto accept;
						}
					} else if (v11 == 1) {
						if (code <= 200 || code >= 750) {
							if (!r)
								goto next;
							goto accept;
						}
					} else if (v11 == 2) {
						if (code <= 300 || code >= 1000) {
							if (!r)
								goto next;
							goto accept;
						}
					} else if (v11 == 3) {
						if (code <= 500 || code >= 1500) {
							if (!r)
								goto next;
							goto accept;
						}
					} else if (v11 == 4) {
						if (code <= 600 || code >= 1750) {
							if (!r)
								goto next;
							goto accept;
						}
					} else if (v11 == 5) {
						if (code <= 700) {
							if (!r)
								goto next;
							goto accept;
						}
					} else if (!r)
						goto next;
				accept:
					sel[count] = ent;
					prev = *(int*) ((unsigned int) *(unsigned short*) (ent + 8) * 0x21c + (unsigned long)&g_7f4ca4);
					*(char*) (ent + 0xf0) = 1;
					list[count] = fcn_00502cd0(0, 2, 7, 1, *(int*) (ent + 0xac));
					count++;
				}
			next:
				ent = he_fn_Handlung();
			}
		}
		limit = 0x50;
		if (list[3] != 0)
			limit -= 0x32;
		if (*(int*) &g_774800)
			limit = 0;
		d3_SelectSceneContext(saved, 1);
		if (door != 0 && cut_FindCutscene(3, -1) == 0 &&
		    limit < (int) (gm_RandomMod(100) & 0xffff)) {
			slot = gm_StartFilteredEntitySearch(1, 1, *(int*) (obj + 0x10));
			if (slot != 0) {
				memset(buf.msg, 0, sizeof(buf.msg));
				buf.msg[8] = 3;
				buf.msg[0x26] = 0xa2;
				*(int*) (buf.msg + 0xc) = *(int*) ((unsigned int) *(unsigned short*) &g_774970 * 0x21c + (unsigned long)&g_7f4ca4);
				*(int*) (buf.msg + 0x14) = -1;
				buf.msg[0x30] = 2;
				buf.msg[0x7c] = 1;
				*(int*) (buf.msg + 0x38) = prev;
				*(int*) (buf.msg + 0x34) = *(int*) ((unsigned int) *(unsigned short*) (slot + 0x27) * 0x21c + (unsigned long)&g_7f4ca4);
				if (door != 0 && strstr(door, (char*) 0x6a1d10) != 0)
					buf.msg[0x7c] |= 8;
				for (i = 0; i < 0x10; i++) {
					*(int*) (buf.msg + 0xc0 + i * 4) = -1;
					*(int*) (buf.msg + 0x80 + i * 4) = -1;
				}
				for (i = 0; i < 3; i++) {
					if (list[i] != 0)
						*(int*) (buf.msg + 0x100 + i * 4) = *(int*) (list[i] + 2);
					else
						*(int*) (buf.msg + 0x100 + i * 4) = -1;
				}
				for (i = 0; i < count; i++) {
					mode = *(unsigned char*) (list[i] + 0x28);
					if (mode == 2 && count == 1) {
						gm_EquipDuelist((char*) buf.msg, mode);
						gm_EquipDuelist((char*) buf.msg, 1);
					} else {
						gm_EquipDuelist((char*) buf.msg, mode);
					}
				}
				*(int*) (buf.msg + 0x10c) = *(int*) (slot + 1);
				memcpy(buf.msg + 0xc0, obj + 0x8c, 0x20);
				*(pos14_7f4c00*) (buf.msg + 0x18) = gm_GameTime;
				gm_AddTime((pos14_7f4c00*) (buf.msg + 0x18), 0xf, 0, 0);
				*(int*) (obj + 0xdc) = fcn_004c5980(buf.msg);
				*(pos14_7f4c00*) (obj + 0x52) = gm_GameTime;
				*(int*) (obj + 0x70) = 2;
				return;
			}
			he_FreeAction(obj);
			return;
		}
	}
	if (gm_CompareGameTime((pos14_7f4c00*) &gm_GameTime, (pos14_7f4c00*) (obj + 0xcc)) >= 0) {
		*(int*) (obj + 0x84) = fcn_004c5620(-1, obj);
		return;
	}
	*(pos14_7f4c00*) (obj + 0x52) = gm_GameTime;
	limit = (gm_RandomMod(5) & 0xffff) + 10;
	gm_AddTime((pos14_7f4c00*) (obj + 0x52), 0, limit, 0);
}
