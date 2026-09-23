// GLOBAL: SERVER 0x1009aca2
extern char g_dynamic_entities[]; /* 0x1009aca2 */
// FUNCTION: GOLD 0x0051db30
// SIZE: 880
// FUNCTION: GOLDTL 0x522ac0
// SIZE: 880
// FUNCTION: SERVER 0x10012eb0

#include "../../../Units/Error/error.h"
#include "../../../Units/m_alloc/m_alloc.h"
#include "../../../Units/vfs/vfs.h"
#include "../../game/entity.h"

#include <stdlib.h>
#include "rebrew_types.h"
#include "rebrew_globals.h"

int __cdecl ls_ReadVfsDataChecked(void* outBuffer, int elementSize, int elementCount, void* streamCtx);
extern int g_file_version; /* 0x1002d4ec */
extern char g_dynamic_entities[]; /* 0x1009aca2 */
int ls_LoadDynamicEntities(void*);

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
