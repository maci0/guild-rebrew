#include <stdlib.h>
#include <string.h>
#include "game_player.h"
#include "spiel.h"
#include "Develop/Units/d2.v1/client_dialog_state.h"
#include "Develop/Units/d2.v1/d2_gui.h"

#pragma intrinsic(memset)

extern unsigned char gm_ActiveTownIndex;
#include "Develop/DieGildeAddOn/game/entity_record.h"
extern float flt_6;
extern float flt_4;
extern char str_NACHRICHTEN_HS_22[];
#include "Develop/DieGildeAddOn/game/game_data.h"

int __cdecl d2_LoadForm(short, short, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl d2_GetWindowListItem(int, int, int);
int __cdecl gm_AccumulateTyped2(char*);
int __cdecl d2_ClampAmountToRange(int, int, int, int*);
int __cdecl gm_AmountToUnits(int, unsigned char);
void __cdecl d2_DrawLawCandidateStatus(int*);
int __cdecl d2_GetControlValue(int);
int __cdecl gm_ConvertUnitsToAmount(int, unsigned char);
int __cdecl gm_CheckEntityStock(void*, int, unsigned char);
void __cdecl cm_RequestMoveCredits(int, int, char, int);
/* The native caller consumes the command queue index returned in EAX. */
int __cdecl cm_RequestCopyEntityData(int, int, int, int);
int __cdecl cm_GetCommandStatus(int);
void __cdecl cm_StepCommandQueue(void);
void __cdecl io_FormatTextBuffer(char*, int, ...);
int __cdecl he_PostEntityMessage(int, int, char*, int, int, char*);
int __cdecl gm_TryRecordCrime(int, int, int, int, int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);

/* Inferred payment dialog callback; record accesses are slot +0, kind +2, id +4. */
extern float g_664330;

/* ADDRESS: GOLDTL 0x005c02a0 */
int __cdecl d2_RunPaymentTargetDialog(char* entity)
{
    int result;
    int dlg;
    int edit;
    int accept;
    int cancel;
    int text_id;
    int amount;
    int limit;
    int command;
    short* stats;
    float duration;
    int ids[6];
    char text[0x400];

    result = 0;
    if (entity == 0)
        return 0;
    dlg = d2_LoadForm(0, 0, "misc\\perga_rolle");
    d2_CenterDialogWindows(dlg);
    d2_SetOverlayAnimation(0, 0);
    d2_SetForm(dlg, 1);
    text_id = io_AppendText(0x174d, *(unsigned short*)entity, gm_ActiveTownIndex);
    edit = d2_GetWindowListItem(dlg, 1, text_id);
    accept = d2_GetWindowListItem(dlg, 1, text_id + 1);
    amount = gm_WalkEntityChain(gm_LocalPlayerSlot);
    amount = (int)(abs(amount + gm_WalkEntityChain(*(unsigned short*)entity)) * 0.0007843137136660516f);
    command = gm_AccumulateTyped2(((char*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[gm_LocalPlayerSlot]));
    d2_ClampAmountToRange(amount, command, 0x20, &limit);
    d2_SetElementValue(edit, gm_AmountToUnits(amount, gm_ActiveTownIndex),
        gm_AmountToUnits(limit, gm_ActiveTownIndex), gm_AmountToUnits(amount, gm_ActiveTownIndex));
    cancel = d2_GetWindowListItem(dlg, 1, io_AppendText(0x174e));
    memset(ids, 0xff, sizeof(ids));
    ids[0] = dlg;
    ids[1] = 2;
    ids[2] = 3;
    ids[3] = 4;
    ids[4] = 2;
    ids[5] = 0x10;
    d2_DrawLawCandidateStatus(ids);
    d2_DialogButtonAction = -1;
    do {
        if (io_RightButtonReleased != 0)
            d2_DialogCloseRequested = 1;
        if (d2_DialogButtonAction != -1) {
            if (d2_CurrentElementId == accept) {
                amount = d2_GetControlValue(edit);
                amount = gm_ConvertUnitsToAmount(amount, gm_ActiveTownIndex);
                if (gm_CheckEntityStock(((char*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[gm_LocalPlayerSlot]), amount, gm_ActiveTownIndex)) {
                    stats = gm_GetEntityTableEntry(((char*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[gm_LocalPlayerSlot]));
                    if (stats != 0)
                        *(int*)((char*)stats + 0x28) += amount;
                    cm_RequestMoveCredits(*(int*)(entity + 4), *(int*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[gm_LocalPlayerSlot].entity_id, gm_ActiveTownIndex, amount);
                    duration = amount * ((*(int*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[gm_LocalPlayerSlot].flags_1cc & 0x800)
                        ? flt_6 : flt_4) * g_664330;
                    command = gm_WalkEntityChain(gm_LocalPlayerSlot);
                    command += gm_WalkEntityChain(*(unsigned short*)entity);
                    command = (int)(duration / command);
                    command = cm_RequestCopyEntityData(*(int*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[gm_LocalPlayerSlot].entity_id, *(int*)(entity + 4), command, 1);
                    while (!cm_GetCommandStatus(command))
                        cm_StepCommandQueue();
                    if (entity[2] == 6 || entity[2] == 7) {
                        io_FormatTextBuffer(text, 0x1751, gm_LocalPlayerSlot, amount);
                        he_PostEntityMessage(*(int*)(entity + 4), -1, text, 0, 0x5fb, str_NACHRICHTEN_HS_22);
                    }
                    gm_TryRecordCrime(0x10, 1, *(int*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[gm_LocalPlayerSlot].entity_id, *(int*)(entity + 4), -1);
                    d2_DialogCloseRequested = 1;
                    result = 1;
                }
            } else if (d2_CurrentElementId == cancel)
                d2_DialogCloseRequested = 1;
        }
    } while (main_RunFrameLoop((void*)d2_RunPaymentTargetDialog, 0x677c7));
    d2_DestroyForm(dlg);
    return result;
}
