#include <string.h>
#include "Develop/DieGildeAddOn/game/client_method_registry.h"
#pragma intrinsic(memset)

extern AM_METHOD am_Methods[];

int __cdecl gm_LookupEntityRecordById(int id);
int __cdecl gm_SelectRandomEntityCandidate(int e);
int __cdecl cm_SendLogAction(char* name);
int __cdecl cm_SendCopyEntityData(char* msg);
int __cdecl cm_SendTraceEnd(char* name);

/* ADDRESS: GOLDTL 0x00499950 */
/* ADDRESS: GOLDDE 0x00488390 */
int __cdecl ai_RunBeatUp(int actor, char* request)
{
    char buf[0xf8];
    int targetEntity;
    int paramVal;

    if (*(char*) request != 7)
        return 0;
    targetEntity = (int) gm_LookupEntityRecordById(*(int*) (request + 4));
    if (targetEntity == 0)
        return 0;
    memset(buf, 0, sizeof(buf));
    buf[4] = 0x1a;
    *(int*) (buf + 8) = *(int*) (actor + 4);
    *(int*) (buf + 0xc) =
        (*(int*) (actor + 0x170) != 0) ? *(int*) (*(int*) (actor + 0x170) + 1) : -1;
    paramVal = *(int*) (request + 0x10);
    *(char*) (buf + 0x36) = 1;
    *(int*) (buf + 0x84) = paramVal;
    *(int*) (buf + 0x60) = *(int*) (targetEntity + 4);
    *(int*) (buf + 0x58) = gm_SelectRandomEntityCandidate(targetEntity);
    am_Methods[0x18].saved_effects[0].value =
        am_Methods[0x18].effects[0].value * *(float*) (request + 0x14);
    am_Methods[0x18].saved_effects[1].value =
        am_Methods[0x18].effects[1].value * *(float*) (request + 0x14);
    am_Methods[0x18].saved_effects[2].value =
        am_Methods[0x18].effects[2].value * *(float*) (request + 0x14);
    am_Methods[0x18].saved_effects[3].value =
        am_Methods[0x18].effects[3].value * *(float*) (request + 0x14);
    cm_SendLogAction("pruegel");
    cm_SendCopyEntityData(buf);
    cm_SendTraceEnd("pruegel");
    return 0x18;
}
