typedef unsigned char u8;
typedef unsigned short u16;
#include "Develop/DieGildeAddOn/game/game_data.h"

int __cdecl ahm_GetWorkshopOwner(int a1);
int __cdecl gm_CheckEntityStock(void* tbl, int a2, char a3);
int __cdecl fcn_00526120(void* buf, int a2);
void __cdecl io_FormatTextBuffer(void* buf, int id, ...);
int __cdecl ahm_DispatchAlchemistCommand(int a1, int a2);
int __cdecl cm_GetCommandStatus(int a1);
int __cdecl main_RunFrameLoop(int a1, int a2);
void __cdecl ahm_ClearDrawSlot(int a1);
void __cdecl cm_RequestMoveCredits(int a1, int a2, char a3, int a4);

/* ADDRESS: GOLDTL 0x00584f00 */
int __cdecl d2_DispatchAlchemyOrder(int building, char* order, int cost)
{
    char buf[0x200];
    int h;
    int r;

    h = ahm_GetWorkshopOwner(building);
    if (gm_CheckEntityStock((void*) (540 * g_774970 + 0x7f4ca0), cost,
                     g_773d75) != 0) {
        if (h != 0) {
            fcn_00526120((void*) *(int*) 0x14b5440, 0x100);
        } else {
            io_FormatTextBuffer(buf, 0x4044,
                         *(int*) (0x14b5908 + *(int*) (order + 0x10) * 4),
                         *(int*) (0x14b596c + *(int*) (order + 0x14) * 4));
            if (fcn_00526120(buf, 1) != 0) {
                r = ahm_DispatchAlchemistCommand(building, (int) order);
                if (r != -1) {
                    int q;

                    while ((q = cm_GetCommandStatus(r)) == 0)
                        main_RunFrameLoop(q, 0x20007);
                }
                if (cm_GetCommandStatus(r) == 1) {
                    ahm_ClearDrawSlot((int) order);
                    cm_RequestMoveCredits(-1, *(int*) (0x7f4ca4 + 540 * g_774970),
                                 g_773d75, cost);
                    return 1;
                }
            }
        }
    }
    return 0;
}
