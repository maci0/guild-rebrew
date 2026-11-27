#include <string.h>

extern unsigned char g_773d75;
extern char g_67e330[];

short* __cdecl gm_GetEntityTableEntry(char* entity);
void __cdecl cm_SendLogAction(char* s);
void __cdecl cm_SendTraceEnd(char* s);
void __cdecl cm_RequestMoveCredits(int a, int b, char c, int n);
void __cdecl cm_SendCopyEntityData(char* msg);

/* ADDRESS: GOLDTL 0x004978d0 */
int __cdecl ai_RunRepairBuilding(char* entity, char* repairReq, char* treasuryReq)
{
    char msg[0xf8];
    char* entry;

    memset(msg, 0, sizeof(msg));
    msg[4] = 0x1c;
    *(int*) (msg + 8) = *(int*) (entity + 4);
    *(int*) (msg + 0xc) = -1;
    msg[0x36] = 1;
    *(int*) (msg + 0x58) = *(int*) (repairReq + 4);
    *(int*) (msg + 0x5c) = *(int*) (repairReq + 0x10);
    cm_SendLogAction(g_67e330);
    cm_RequestMoveCredits(-1, *(int*) (treasuryReq + 4), (char) g_773d75,
        (int) (*(float*) (repairReq + 0x14)));
    cm_SendCopyEntityData(msg);
    cm_SendTraceEnd(g_67e330);
    entry = (char*) gm_GetEntityTableEntry(entity);
    if (entry != 0) {
        *(int*) (entry + 0x44) = *(int*) (entry + 0x44) + *(float*) (repairReq + 0x14);
    }
    return 0xf;
}
