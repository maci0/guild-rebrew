#include <stdio.h>
#include <string.h>

/* SIZE 0x2d */
typedef struct Straftat {
	int id;
	char pad04[0x12];
	int f16;
	char pad1a[0x13];
} Straftat;

/* SIZE 0xc */
typedef struct Area {
	unsigned int a;
	unsigned int b;
	unsigned int c;
	unsigned int d;
} Area;

#include "Develop/DieGildeAddOn/game/game_data.h"
#include "client_straftat.h"
#include "Develop/DieGildeAddOn/game/entity_record.h"

void __cdecl srv_SeedRandom(int);
void __cdecl fcn_004b4650(char*, int);
int __cdecl gs_AddBeweis(int, int);
int __cdecl fcn_004f57e0(void);
void __cdecl fcn_004fa850(int, char, unsigned int*, unsigned int*);
void __cdecl fcn_004faa90(unsigned int, unsigned int, Area*);
int __cdecl gm_ResolveEntityById(char**, int, int, int);
int __cdecl gm_LookupEntityRecordById(int);
int __cdecl he_StartHandlungSearch(int, int, int);
int __cdecl he_fn_Handlung(void);
void __cdecl fcn_005b2740(char*, char*);


/* Copies the crime description of a source record into the crime table,
 * resolves the offender, reports the new entry and walks the entity list
 * that belongs to the case. */
/* ADDRESS: GOLDTL 0x004c9a10 */
int __cdecl cm_ExAddStraftat(char* src, char* out)
{
	STRAFTAT_RECORD* rec;
	unsigned int v13;
	unsigned int v14;
	char* p;
	Straftat* ent;
	Area area;
	char msg[0x200];
	int taeter;
	int idx;
	unsigned short slot;

	if (g_14cbca0 != -1) {
		cm_LastCrimeId = *(int*) (src + 0x10);
	} else {
		cm_LastCrimeId = cm_LastCrimeId + 1;
	}
	idx = fcn_004f57e0();
	if (idx != -1) {
		ent = (Straftat*) gm_LookupEntityRecordById(*(int*) (src + 0x26));
		if (ent != 0 && *(char*) ((char*) ent + 2) == 6) {
			fcn_004b4650((char*) ent, 0x17);
		}
		rec = &g_9a3800[idx];
		memcpy(rec, src + 0x10, 0x2d);
		rec->id = cm_LastCrimeId;
		sprintf(msg, "cm_ExAddStraftat(): Executed---- st_id = %i, taeter = %i, opfer = %i",
			cm_LastCrimeId, *(int*) (src + 0x26), *(int*) (src + 0x22));
		taeter = *(int*) (src + 0x31);
		if (taeter == -1) {
			ent = (Straftat*) gm_LookupEntityRecordById(*(int*) (src + 0x22));
			if (ent != 0) {
				if (*(int*) ((char*) ent + 0x170) != 0) {
					taeter = *(int*) (*(char**) ((char*) ent + 0x170) + 1);
				} else if (*(int*) ((char*) ent + 0x16c) != 0) {
					taeter = *(int*) (*(char**) ((char*) ent + 0x16c) + 1);
				} else {
					srv_SeedRandom(*(int*) (src + 0x39));
				}
			} else {
				srv_SeedRandom(*(int*) (src + 0x39));
			}
		}
		fcn_004fa850(taeter, *(char*) (src + 0x2c), &v13, &v14);
		gm_ResolveEntityById(&p, 0, 0, taeter);
		if (p == 0) {
			fcn_004faa90(v13, v14, &area);
		} else {
			if (*(int*) (p + 0x61) != 0) {
				area.a = *(unsigned int*) (*(char**) (p + 0x61) + 0x4c);
				area.b = *(unsigned int*) (*(char**) (p + 0x61) + 0x50);
				area.c = *(unsigned int*) (*(char**) (p + 0x61) + 0x54);
			}
		}
		for (ent = (Straftat*) he_StartHandlungSearch(1, 0, 0x18); ent != 0;
			ent = (Straftat*) he_fn_Handlung()) {
			if (*(int*) ((char*) ent + 0xc4) != g_9a3800[idx].target_id) {
				continue;
			}
			slot = *(unsigned short*) ((char*) ent + 8);
			if (gs_AddBeweis(rec->id, *(int*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[slot].entity_id) == 0) {
				break;
			}
			if (out != 0) {
				char* px;

				px = (char*) gm_LookupEntityRecordById(*(int*) ((char*) ent + 0xc4));
				if (px != 0) {
					fcn_005b2740(px, ((char*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[slot]));
				}
			}
		}
		if (out != 0) {
			out[0] = 1;
			out[1] = 6;
			*(STRAFTAT_RECORD**) (out + 6) = rec;
		}
		return 0;
	}
	return -1;
}
#if defined(REBREW_SERVER) || defined(REBREW_GOLD)
#if defined(REBREW_SERVER) || defined(REBREW_GOLD)
unsigned char _dpad_7731b8[2944];
#else
/* Reference gaps only; the emitted objects inside the span keep their own rows. */
unsigned char _dpad_7731d8[2912];
#endif
#else
/* Reference gaps only; the emitted objects inside the span keep their own rows. */
unsigned char _dpad_7731d8[2912];
#endif
