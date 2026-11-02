char* __cdecl cut_FindCutsceneById(int id);
#include "Develop/DieGildeAddOn/game/cutscene.h"

/* Inferred distinct client handler name. */
/* ADDRESS: GOLDTL 0x004c9f50 */
int __cdecl cm_ExAddCutsceneParticipant(char* command, char* result)
{
    if (cut_FindCutsceneById(*(int*) (command + 0x10)) == 0)
        return 1;
    if (!cut_AddParticipant(*(int*) (command + 0x10), *(int*) (command + 0x14)))
        return 1;
    if (result != 0)
        result[0] = 1;
    return 0;
}
