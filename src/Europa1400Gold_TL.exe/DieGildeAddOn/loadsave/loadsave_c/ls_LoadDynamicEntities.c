// CFLAGS: /O2 /Gd
// FUNCTION: GOLDTL 0x522ac0
// SIZE: 880
#include "../../../Units/Error/error.h"
#include "../../../Units/m_alloc/m_alloc.h"
#include "../../../Units/vfs/vfs.h"
#include "../../game/entity.h"

#include <stdlib.h>
#include "rebrew_types.h"
#include "rebrew_globals.h"

extern void amt_FindEntity26(int);
extern void amt_FindEntity27(int);
extern char gm_RandomMod(int);
extern unsigned char _ftol();
extern void gm_AddObjekt(int, int, int);
int __cdecl ls_ReadVfsDataChecked(void* outBuffer, int elementSize, int elementCount, void* streamCtx);
extern int g_file_version; /* 0x1002d4ec */
extern char g_dynamic_entities[]; /* 0x1009aca2 */
extern char g_dynamic_entities_end[]; /* 0x1009b762 */
extern int g_aux_entity_count; /* 0x101de454 */
extern int g_aux_entity_buffer; /* 0x101de55c */
extern unsigned int gm_LookupEntityRecordById(unsigned int);
extern int gm_ResolveEntityById(void**, void**, void**, int);
extern void gm_EntitySetField(void);
extern int g_save_info[2];
extern int vfs_OpenStream(char*, char*, int);
int ls_LoadSavegameHeader(int, char*);
int ls_LoadExistingEntities(int);
unsigned int ls_LoadBuildingEntityState(unsigned int);
int ls_LoadDynamicEntities(void*);
int ls_LoadEntities(int);
int ls_LoadTownData(int);
extern int amt_fio_LoadAemter(int, int);
extern unsigned int ls_ID2Ptr(void);

/* Loads graveyard-specific data from a save file. Reads
 * production slots, worker assignments, and field states
 * for graveyard buildings. */

int __cdecl ls_LoadDynamicEntities(void* file)
{
    int i;
    int count;
    int i2;
    char* record_cursor;

    for (i = 0; i < 16; i++) {

        if (!ls_ReadVfsDataChecked(&g_dynamic_entities[i * 0xac - 2], 2, 1, file)) {
            return 0;
        }
        if (!ls_ReadVfsDataChecked(&g_dynamic_entities[i * 0xac], 0x10, 1, file)) {
            return 0;
        }
        if (!ls_ReadVfsDataChecked(&g_dynamic_entities[i * 0xac + 0x12], 4, 1, file)) {
            return 0;
        }
        if (g_file_version >= 0x1002c) {
            if (!ls_ReadVfsDataChecked(&g_dynamic_entities[i * 0xac + 0x26], 4, 1, file)) {
                return 0;
            }
        }
        if (!ls_ReadVfsDataChecked(&g_dynamic_entities[i * 0xac + 0x1a], 4, 1, file)) {
            return 0;
        }
        if (!ls_ReadVfsDataChecked(&g_dynamic_entities[i * 0xac + 0x1e], 4, 1, file)) {
            return 0;
        }
        if (!ls_ReadVfsDataChecked(&g_dynamic_entities[i * 0xac + 0x2a], 4, 1, file)) {
            return 0;
        }
        if (!ls_ReadVfsDataChecked(&g_dynamic_entities[i * 0xac + 0x2e], 4, 1, file)) {
            return 0;
        }
        if (!ls_ReadVfsDataChecked(&g_dynamic_entities[i * 0xac + 0x32], 4, 1, file)) {
            return 0;
        }
        if (!ls_ReadVfsDataChecked(&g_dynamic_entities[i * 0xac + 0x36], 4, 1, file)) {
            return 0;
        }
        if (!ls_ReadVfsDataChecked(&g_dynamic_entities[i * 0xac + 0x3e], 4, 1, file)) {
            return 0;
        }
        if (!ls_ReadVfsDataChecked(&g_dynamic_entities[i * 0xac + 0x42], 4, 1, file)) {
            return 0;
        }
        if (!ls_ReadVfsDataChecked(&g_dynamic_entities[i * 0xac + 0x46], 4, 1, file)) {
            return 0;
        }
        if (!ls_ReadVfsDataChecked(&g_dynamic_entities[i * 0xac + 0x4a], 4, 1, file)) {
            return 0;
        }
        if (!ls_ReadVfsDataChecked(&g_dynamic_entities[i * 0xac + 0x4e], 4, 1, file)) {
            return 0;
        }
        if (g_file_version >= 0x10014) {
            if (!ls_ReadVfsDataChecked(&g_dynamic_entities[i * 0xac + 0x52], 4, 1, file)) {
                return 0;
            }
            if (!ls_ReadVfsDataChecked(&g_dynamic_entities[i * 0xac + 0x56], 4, 1, file)) {
                return 0;
            }
            if (!ls_ReadVfsDataChecked(&g_dynamic_entities[i * 0xac + 0x5a], 4, 1, file)) {
                return 0;
            }
            if (!ls_ReadVfsDataChecked(&g_dynamic_entities[i * 0xac + 0x3a], 4, 1, file)) {
                return 0;
            }
            if (!ls_ReadVfsDataChecked(&g_dynamic_entities[i * 0xac + 0x62], 4, 1, file)) {
                return 0;
            }
            if (!ls_ReadVfsDataChecked(&g_dynamic_entities[i * 0xac + 0x66], 4, 1, file)) {
                return 0;
            }
            if (!ls_ReadVfsDataChecked(&g_dynamic_entities[i * 0xac + 0x6a], 4, 1, file)) {
                return 0;
            }
        }
        if (g_file_version >= 0x10056) {
            if (!ls_ReadVfsDataChecked(&g_dynamic_entities[i * 0xac + 0x5e], 4, 1, file)) {
                return 0;
            }
        }
        else {
            *(int*) (&g_dynamic_entities[i * 0xac + 0x5e]) = 0x3f800000;
        }
        if (g_file_version >= 0x10015) {
            count = (g_file_version < 0x10046) ? 0x0e : 0x11;
            for (i2 = 0; i2 < count; i2++) {
                if (!ls_ReadVfsDataChecked(&g_dynamic_entities[i * 0xac + 0x72 + i2], 1, 1, file)) {
                    return 0;
                }
            }
        }
        if (!ls_ReadVfsDataChecked(&g_dynamic_entities[i * 0xac + 0x86], 4, 1, file)) {
            return 0;
        }
        if (!ls_ReadVfsDataChecked(&g_dynamic_entities[i * 0xac + 0x8a], 0x10, 1, file)) {
            return 0;
        }
        if (!ls_ReadVfsDataChecked(&g_dynamic_entities[i * 0xac + 0x9a], 0x0c, 1, file)) {
            return 0;
        }
        if (!ls_ReadVfsDataChecked(&g_dynamic_entities[i * 0xac + 0xa6], 4, 1, file)) {
            return 0;
        }
        if (g_file_version >= 0x10018) {
            if (!ls_ReadVfsDataChecked(&g_dynamic_entities[i * 0xac + 0x6e], 4, 1, file)) {
                return 0;
            }
        }
    }

    return 1;
}
