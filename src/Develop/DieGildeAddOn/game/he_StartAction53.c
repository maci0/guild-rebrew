typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

void* __cdecl gm_LookupEntityRecordById(int a1);
int __cdecl cm_SendSetHE(char a1, unsigned char* e);
void* __cdecl he_StartHandlungSearch(int n, ...);
void* __cdecl he_fn_Handlung(void);
void __cdecl he_NotifyObjektMessage(void* a1);
void __cdecl gm_AddTime(void* clock, int a2, int a3, int a4);
void __cdecl gm_ModifyHealth(int id, int amount);
int __cdecl gm_TryRecordCrime(int idx, int id, int a3, int a4, int a5);
int __cdecl gm_RandomMod(int);
float __cdecl gm_GetEntitySkill(char* entity, int idx);
int __cdecl gm_HasActiveSpecialObject(char* a1, int a2);
void __cdecl he_NotifyAction0x35Blocked(void* a1, void* a2);
void __cdecl he_NotifyAction0x35Success(void* a1);

#include "client_types.h"

extern pos14_7f4c00 gm_GameTime;

/* ADDRESS: GOLDTL 0x0054c240 */
void __cdecl he_StartAction53(u8* action)
{
    char* target;
    int cnt = 0;
    u8* clockPtr;

    if (action[0x78] & 4)
        return;

    target = gm_LookupEntityRecordById(*((u32*)(action + 0xbc)));
    if (target == 0) {
        clockPtr = action + 0x52;
        *(pos14_7f4c00*) clockPtr = gm_GameTime;
        *((u32*)(action + 0x84)) = (u32)cm_SendSetHE(-1, action);
        return;
    }

    if (he_StartHandlungSearch(1, 0, 0x35) != 0) {
        do {
            cnt++;
        } while (he_fn_Handlung() != 0);
        if (cnt > 4) {
            clockPtr = action + 0x52;
            *(pos14_7f4c00*) clockPtr = gm_GameTime;
            *((u32*)(action + 0x84)) = (u32)cm_SendSetHE(-1, action);
            return he_NotifyObjektMessage(
                (void*)(0x7f4ca0 + 540 * (u32)*(u16*)(action + 8)));
        }
    }

    clockPtr = action + 0x52;
    *(pos14_7f4c00*) clockPtr = gm_GameTime;
    *(pos14_7f4c00*) (action + 0x44) = gm_GameTime;
    *(pos14_7f4c00*) (action + 0xac) = gm_GameTime;

    gm_AddTime(clockPtr, 0, 1, 0);
    gm_AddTime(action + 0xac, 0x18, 0, 0);

    gm_ModifyHealth(*((u32*)(0x7f4ca4 + 540 * (u32)*(u16*)(action + 8))), -1);

    {
        u32 ownerPtr = *((u32*)(0x7f4e10 + 540 * (u32)*(u16*)(action + 8)));
        int ownerId;
        if (ownerPtr)
            ownerId = *((u32*)(ownerPtr + 1));
        else
            ownerId = -1;
        gm_TryRecordCrime(3, 1,
                     *((u32*)(0x7f4ca4 + 540 * (u32)*(u16*)(action + 8))),
                     *((u32*)(action + 0xbc)), ownerId);
    }

    *((u32*)(action + 0xc4)) = (u32)(gm_RandomMod(0x300) & 0xffff);
    *((u32*)(action + 0xc8)) = *((u32*)(0x664398 +
                              4 * (u32)(gm_RandomMod(0x10) & 0xffff)));
    *((float*)(action + 0xd0)) = gm_GetEntitySkill(
        (char*)(0x7f4ca0 + 540 * (u32)*(u16*)(action + 8)), 4);
    *((u32*)(action + 0xcc)) = 0x300;

    if (gm_HasActiveSpecialObject(target, 0x15c) != 0) {
        *(pos14_7f4c00*) clockPtr = gm_GameTime;
        *((u32*)(action + 0x84)) = (u32)cm_SendSetHE(-1, action);
        he_NotifyAction0x35Blocked(target,
            (void*)(0x7f4ca0 + 540 * (u32)*(u16*)(action + 8)));
        return;
    }

    he_NotifyAction0x35Success(target);
    *((u32*)(action + 0x84)) = (u32)cm_SendSetHE(0, action);
}
