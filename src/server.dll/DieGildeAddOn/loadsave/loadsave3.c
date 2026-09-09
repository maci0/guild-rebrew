#include "../../Units/Error/error.h"
#include "../../Units/m_alloc/m_alloc.h"
#include "../../Units/vfs/vfs.h"
#include "../game/entity.h"

#include <stdlib.h>

int __cdecl AllocGraveyardField(int);
extern void amt_FindEntity26(int);
extern void amt_FindEntity27(int);
extern char gm_RandomMod(int);
extern unsigned char _ftol();
extern void gm_AddOrAccumulateObject(int, int, int);
int __cdecl ls_ReadVfsDataChecked(void* outBuffer, int elementSize, int elementCount, void* streamCtx);
extern int g_file_version;
int __cdecl ls_LoadGraveyardData(int stream_ctx, int dest_buf);
extern int g_file_version; /* 0x1002d4ec */
extern unsigned char* g_entity_ptr; /* 0x1014d8c0 */
extern int g_101de454; /* 0x101de454 */
extern int g_101de55c; /* 0x101de55c */
extern unsigned int gm_LookupEntityRecordById(unsigned int);
extern int gm_ResolveEntityById(void**, void**, void**, int);
extern void gm_EntitySetField(void);
extern int g_save_info[2];
extern int OpenVfsStream(char*, char*, int);
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
extern char* g_item_def_table; /* 0x101de450 */
extern char* g_query_base; /* 0x100a8c34 */
extern unsigned int g_entity_table_end; /* 0x1003546c */

// FUNCTION: SERVER 0x10014070
// ls_ID2Ptr
// RELOC, 491/491. The entity loop indexes from the record base (rec = e -
// 0x170, positive offsets) so msvc6 keeps the address CSE out of the
// null-check; with e-relative negative offsets it hoists `lea [esi-4]` above
// the `je` and shifts every following byte (187/491).
// The list walks need both the target's copy-propagation and its eax/ecx
// roles, and those are two separate decisions. Guarding on node's successor
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
	unsigned char* e;
	int* p;
	int i;
	char* s;
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
		for (p = (int*) 0x10035478; (int) p < 0x10035498; p++) {
			*p = gm_LookupEntityRecordById(*p);
		}
	}
	for (e = (unsigned char*) 0x10035a10; (int) e < 0x1009ae10; e += 0x21c) {
		rec = e - 0x170;
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
		s = (char*) g_query_base + i * 0x43;
		idx = *(unsigned short*) s;
		if (*(char*) (g_item_def_table + idx * 64 + idx) == 0x1d) {
			*(int*) (s + 0x24) = 0;
		}
		if (*(int*) (s + 6) != -1) {
			if (!gm_ResolveEntityById(&v1, &v2, &v3, *(int*) (s + 6))) {
				LogMessageInternal(s_D__Develop_DieGildeAddOn_loadsav_1002d550, 0x1050,
				    s_ls_ID2Ptr____Houston__wir_haben_e_1002d520, 1);
			} else if (v1 != 0) {
				node = *(void**) (v1 + 0x5d);
				if (node == 0) {
					*(void**) (v1 + 0x5d) = s;
				} else {
					if (*(void**) ((char*) node + 0x3f) != 0) {
						nxt = node;
						do {
							nxt = *(void**) ((char*) nxt + 0x3f);
						} while (*(void**) ((char*) nxt + 0x3f) != 0);
						node = nxt;
					}
					*(void**) ((char*) node + 0x3f) = s;
				}
			} else if (v2 != 0) {
				node = *(void**) (v2 + 0x14);
				if (node == 0) {
					*(void**) (v2 + 0x14) = s;
				} else {
					if (*(void**) ((char*) node + 0x3f) != 0) {
						nxt = node;
						do {
							nxt = *(void**) ((char*) nxt + 0x3f);
						} while (*(void**) ((char*) nxt + 0x3f) != 0);
						node = nxt;
					}
					*(void**) ((char*) node + 0x3f) = s;
				}
			} else {
				node = *(void**) (v3 + 0x178);
				if (node == 0) {
					*(void**) (v3 + 0x178) = s;
				} else {
					if (*(void**) ((char*) node + 0x3f) != 0) {
						nxt = node;
						do {
							nxt = *(void**) ((char*) nxt + 0x3f);
						} while (*(void**) ((char*) nxt + 0x3f) != 0);
						node = nxt;
					}
					*(void**) ((char*) node + 0x3f) = s;
				}
			}
		}
	}
	gm_EntitySetField();
	return 1;
}

extern int g_1002dde0[4];
extern int g_array_count[4];
/* Canonical definitions live in Units/m_alloc/m_alloc2.c. */
extern int g_stat1;
extern int g_stat2;
extern int g_stat3;
extern int g_stat4;
extern int g_flag_3c[4];
extern void* g_array_ptr[4];
extern char g_stream_pool[1];
extern int g_stream_count[4];
extern int g_connection_counter[4];
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
extern char g_query_filter_state;
char g_str_10031500[1] = {
    0x67,
};
char g_str_10031538[1] = {
    0x67,
};
