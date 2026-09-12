#include "../../Units/Error/error.h"
#include "../../Units/m_alloc/m_alloc.h"
#include "../../Units/vfs/vfs.h"
#include "../game/entity.h"

#include <stdlib.h>
#include "rebrew_types.h"
#include "rebrew_globals.h"

int __cdecl gv_AllocGraveyardField(int);
extern void amt_FindEntity26(int);
extern void amt_FindEntity27(int);
extern char gm_RandomMod(int);
extern unsigned char _ftol();
extern void gm_AddObjekt(int, int, int);
int __cdecl ls_ReadVfsDataChecked(void* outBuffer, int elementSize, int elementCount, void* streamCtx);
extern int g_file_version;
int __cdecl ls_LoadGraveyardData(int stream_ctx, int dest_buf);
extern int g_file_version; /* 0x1002d4ec */
extern int g_aux_entity_count; /* 0x101de454 */
extern int g_aux_entity_buffer; /* 0x101de55c */
extern unsigned int gm_LookupEntityRecordById(unsigned int);
extern int gm_ResolveEntityById(void**, void**, void**, int);
extern void gm_EntitySetField(void);
extern int g_save_info[2];
extern int vfs_OpenStream(char*, char*, int);
/* Defined in loadsave2.c; same literals, same VAs. */
extern char s_ls_ID2Ptr____Stadtspieler_Id_not_1002d580[];
extern char s_D__Develop_DieGildeAddOn_loadsav_1002d550[];
extern char s_ls_ID2Ptr____Houston__wir_haben_e_1002d520[];
int ls_LoadSavegameHeader(int, char*);
int ls_LoadExistingEntities(int);
unsigned int ls_LoadBuildingEntityState(unsigned int);
int ls_LoadDynamicEntities(void*);
int ls_LoadEntities(int);
int ls_LoadTownData(int);
extern int amt_fio_LoadAemter(int, int);
extern unsigned int ls_ID2Ptr(void);
unsigned short* __cdecl gm_StartFilteredEntitySearch(int, int, int, ...);

extern int g_query_limit; /* 0x10035450 */
extern int g_active_player_count; /* 0x1003543c */
extern unsigned short* g_entity_table_end; /* 0x1003546c */

// FUNCTION: GOLDTL 0x4c4b00
// SIZE: 551
// ls_ID2Ptr
// RELOC, 491/491. The entity loop indexes from the record base (rec = entity_cursor -
// 0x170, positive offsets) so msvc6 keeps the address CSE out of the
// null-check; with entity_cursor-relative negative offsets it hoists `lea [esi-4]` above
// the `je` and shifts every following byte (187/491).
// The list walks need both the target'record_cursor copy-propagation and its eax/ecx
// roles, and those are two separate decisions. Guarding on node'record_cursor successor
// then walking a second cursor (nxt) that is seeded from node and written
// back at the end gives `mov ecx,eax` + `mov eax,[ecx+0x3f]`; walking node
// itself gives the same shape with the registers swapped (461/491), and the
// original do/while over nxt copy-propagates into `mov eax,[eax+0x3f]`
// (488/491). Probed in .scratch/pv3/w3-w6.c.

unsigned int ls_ID2Ptr(void)
{
	int v1;
	int v2;
	int v3;
	unsigned char* entity_cursor;
	int* id_cursor;
	int i;
	char* record_cursor;
	unsigned int idx;
	void* node;
	void* nxt;
	unsigned char* rec;

	g_entity_table_end = gm_LookupEntityRecordById(g_entity_table_end);
	if (g_entity_table_end == 0) {
		LogMessageInternal(s_D__Develop_DieGildeAddOn_loadsav_1002d550, 0x1016,
		    s_ls_ID2Ptr____Stadtspieler_Id_not_1002d580, 1);
		return 0;
	}
	g_active_player_count = (int) gm_StartFilteredEntitySearch(1, 5, 0xa);
	if (g_file_version >= 0x10017) {
		for (id_cursor = (int*) 0x10035478; (int) id_cursor < 0x10035498; id_cursor++) {
			*id_cursor = gm_LookupEntityRecordById(*id_cursor);
		}
	}
	for (entity_cursor = (unsigned char*) 0x10035a10; (int) entity_cursor < 0x1009ae10; entity_cursor += 0x21c) {
		rec = entity_cursor - 0x170;
		if (*(unsigned short*) rec == 0xffff) {
			continue;
		}
		if (*(int*) (rec + 0x16c) == -1) {
			*(int*) (rec + 0x16c) = 0;
		} else {
			gm_ResolveEntityById((void**) (rec + 0x16c), 0, 0, *(int*) (rec + 0x16c));
		}
		if (*(int*) (rec + 0x170) == -1) {
			*(int*) (rec + 0x170) = 0;
		} else {
			gm_ResolveEntityById((void**) (rec + 0x170), 0, 0, *(int*) (rec + 0x170));
		}
	}
	for (i = 0; i < g_query_limit; i++) {
		record_cursor = (char*) g_query_base + i * 0x43;
		idx = *(unsigned short*) record_cursor;
		if (*(char*) (g_item_def_table + idx * 64 + idx) == 0x1d) {
			*(int*) (record_cursor + 0x24) = 0;
		}
		if (*(int*) (record_cursor + 6) != -1) {
			if (!gm_ResolveEntityById(&v1, &v2, &v3, *(int*) (record_cursor + 6))) {
				LogMessageInternal(s_D__Develop_DieGildeAddOn_loadsav_1002d550, 0x1050,
				    s_ls_ID2Ptr____Houston__wir_haben_e_1002d520, 1);
			} else if (v1 != 0) {
				node = *(void**) (v1 + 0x5d);
				if (node == 0) {
					*(void**) (v1 + 0x5d) = record_cursor;
				} else {
					if (*(void**) ((char*) node + 0x3f) != 0) {
						nxt = node;
						do {
							nxt = *(void**) ((char*) nxt + 0x3f);
						} while (*(void**) ((char*) nxt + 0x3f) != 0);
						node = nxt;
					}
					*(void**) ((char*) node + 0x3f) = record_cursor;
				}
			} else if (v2 != 0) {
				node = *(void**) (v2 + 0x14);
				if (node == 0) {
					*(void**) (v2 + 0x14) = record_cursor;
				} else {
					if (*(void**) ((char*) node + 0x3f) != 0) {
						nxt = node;
						do {
							nxt = *(void**) ((char*) nxt + 0x3f);
						} while (*(void**) ((char*) nxt + 0x3f) != 0);
						node = nxt;
					}
					*(void**) ((char*) node + 0x3f) = record_cursor;
				}
			} else {
				node = *(void**) (v3 + 0x178);
				if (node == 0) {
					*(void**) (v3 + 0x178) = record_cursor;
				} else {
					if (*(void**) ((char*) node + 0x3f) != 0) {
						nxt = node;
						do {
							nxt = *(void**) ((char*) nxt + 0x3f);
						} while (*(void**) ((char*) nxt + 0x3f) != 0);
						node = nxt;
					}
					*(void**) ((char*) node + 0x3f) = record_cursor;
				}
			}
		}
	}
	gm_EntitySetField();
	return 1;
}

/* Canonical definitions live in Units/m_alloc/m_alloc2.c. */
extern int g_stream_pool; /* 0x10034670 */
extern int g_stream_count; /* 0x10034678 */
/* Canonical definition lives in DieGildeAddOn/game/spiel.c. */
extern int g_next_object_id;
char g_filter_extra5[1] = {
    0xff,
};
int g_query_filter_extra1[4] = {
    0xff, 0xff, 0xff, 0xff,
};
int g_query_filter_extra2[4] = {
    0xff, 0x7f, 0xff, 0x7f,
};
short g_query_filter_extra3[2] = {
    0xff, 0x7f,
};
int g_query_filter_extra4[4] = {
    0xff, 0x00, 0x00, 0x00,
};
/* Canonical definition lives in game/spiel_c/gm_NextEntityQueryMatch.c. */
extern int g_query_filter_owner;
char g_str_10031500[1] = {
    0x67,
};
char g_str_10031538[1] = {
    0x67,
};
