#include <string.h>
#include "client_method_registry.h"
#pragma intrinsic(memset)

extern AM_METHOD g_1008540[];

int __cdecl gm_LookupEntityRecordById(int id);
int __cdecl gm_SelectRandomEntityCandidate(int e);
int __cdecl cm_SendLogAction(char* name);
int __cdecl cm_SendCopyEntityData(char* msg);
int __cdecl cm_SendTraceEnd(char* name);

/* ADDRESS: GOLDTL 0x00499950 */
int __cdecl fcn_00499950(int a, char* b)
{
    char buf[0xf8];
    int e;
    int v;

    if (*(char*) b != 7)
        return 0;
    e = (int) gm_LookupEntityRecordById(*(int*) (b + 4));
    if (e == 0)
        return 0;
    memset(buf, 0, sizeof(buf));
    buf[4] = 0x1a;
    *(int*) (buf + 8) = *(int*) (a + 4);
    *(int*) (buf + 0xc) =
        (*(int*) (a + 0x170) != 0) ? *(int*) (*(int*) (a + 0x170) + 1) : -1;
    v = *(int*) (b + 0x10);
    *(char*) (buf + 0x36) = 1;
    *(int*) (buf + 0x84) = v;
    *(int*) (buf + 0x60) = *(int*) (e + 4);
    *(int*) (buf + 0x58) = gm_SelectRandomEntityCandidate(e);
    g_1008540[0x18].saved_effects[0].value =
        g_1008540[0x18].effects[0].value * *(float*) (b + 0x14);
    g_1008540[0x18].saved_effects[1].value =
        g_1008540[0x18].effects[1].value * *(float*) (b + 0x14);
    g_1008540[0x18].saved_effects[2].value =
        g_1008540[0x18].effects[2].value * *(float*) (b + 0x14);
    g_1008540[0x18].saved_effects[3].value =
        g_1008540[0x18].effects[3].value * *(float*) (b + 0x14);
    cm_SendLogAction("pruegel");
    cm_SendCopyEntityData(buf);
    cm_SendTraceEnd("pruegel");
    return 0x18;
}
