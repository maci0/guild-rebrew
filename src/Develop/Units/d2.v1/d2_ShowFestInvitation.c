/* Reconstructed from native disassembly; frame slots follow the decompiler map. */

#include <math.h>
#include <string.h>
#include "Develop/client_types.h"

typedef struct {
  unsigned int ent;
  struct { unsigned int ent; int value; } members[4];
  unsigned int a;
  unsigned int b;
  int text;
  unsigned char count;
} Party5c18e0;
extern pos14_7f4c00 gm_GameTime;
extern int d2_DialogButtonAction, io_RightButtonReleased, d2_CurrentElementId; extern int gm_TargetPersonTypeMask, g_66601c, d2_CurrentWindowId,
	d2_DialogCloseRequested; extern unsigned short gm_LocalPlayerSlot;
int __cdecl d3_FreeObjectAnimation();
int __cdecl d3_SetNodePosition();
int __cdecl d3_SetObjectRotation();
int __cdecl CompareVector3WithinTolerance();
int __cdecl d2_LoadForm();
int __cdecl d2_CenterDialogWindows();
int __cdecl d2_DestroyForm();
int __cdecl d2_GetWindowListItem();
int __cdecl d2_SetElementEnabled();
int __cdecl d2_SetForm();
int __cdecl d2_SetOverlayAnimation();
int __cdecl gm_ResolveDinnerParty();
int __cdecl cm_BeginPacketFieldDelta();
int __cdecl cm_AppendPacketFieldDelta();
int __cdecl cm_RequestChangeAttribute();
int __cdecl cm_SendCopyEntityData();
int __cdecl gm_AddTime();
int __cdecl fcn_00502850();
int __cdecl fcn_00502cd0();
int __cdecl fcn_00503fe0();
int __cdecl gm_LookupEntityRecordById();
int __cdecl io_AppendText();
int __cdecl io_FormatTextBuffer();
int __cdecl d3_AnimateCameraToStoredTransform();
int __cdecl sv_ResetSelectionState();
int __cdecl d3_EndCameraAndUiMode();
int __cdecl d2_CreateButtonRow();
int __cdecl d2_InitWindowBounds();
int __cdecl main_RunFrameLoop();
int __cdecl he_fn_Handlung();
int __cdecl he_StartHandlungSearch();
int __cdecl d2_OpenTargetPicker();

/* ADDRESS: GOLDTL 0x005c18e0 */
void __cdecl d2_ShowFestInvitation(int a0,int a1)
{
  unsigned int *v1;
  int v10;
  unsigned int v11; 
  int v12;
  unsigned int v13;
  unsigned int *v14;
  unsigned int v15 [20]; 
  pos14_7f4c00 timer;
  Party5c18e0 party;
  int buttons[2]; 
  int v17 [6];
  unsigned int v18; 
  char v19; 
  unsigned short *v2;
  int v20 [4];
  int commit; 
  char buttonLabelA [256];
  char buttonLabelB [256];
  char message [0xf8];
  int v27; 
  unsigned int v28; 
  unsigned int v29; 
  int v3;
  unsigned int v30; 
  int v36; 
  unsigned int v37; 
  int v38; 
 
  int v4;
 
 
 
  unsigned int v5;
  unsigned int v56; 
  int v57; 
  int v58; 
  int v59; 
  unsigned char v6; 
  int v60; 
  int v61; 
  unsigned int v62; 
  unsigned short *v7; 
  int v8; 
  unsigned int v9;
  timer = gm_GameTime;
  memset(v15, 0, sizeof(v15));
  v29 = 6;
  v15[4] = 6;
  v27 = 0;
  v20[0] = 0;
  v20[1] = 0;
  v20[2] = 0;
  v20[3] = 0;
  v30 = 5;
  v15[1] = 0x400;
  v15[2] = gm_TargetPersonTypeMask;
  v15[3] = g_66601c;
  gm_AddTime(&timer,0x18,0,0);
  timer.b = 0x14;
  *(unsigned short*) &timer.c = 0;
  v12 = he_StartHandlungSearch(1,0,0x37);
  v10 = a0;
  while ((v12 && (*(int *)(v12 + 0x10) != *(int *)(v10 + 1)))) {
    v12 = he_fn_Handlung();
  }
  v8 = fcn_00502cd0(*(unsigned int *)(v10 + 0x5d),1,0,0x18);
  v10 = a1;
  v37 = (unsigned int)(v8 != 0);
  if (v12) { 
    timer = *(pos14_7f4c00*) (v12 + 0x52);
    v14 = (unsigned int*) (a1 + 0x1c);
    v12 = 0;
    do {
      v9 = *v14;
      v20[v12] = gm_LookupEntityRecordById(v9);
      v12 += 1;
      v14 = &v14[1];
    } while (v12 < 4);
    v29 = (unsigned int)*(unsigned char *)(v10 + 0x2c);
    v30 = (unsigned int)*(unsigned char *)(v10 + 0x2d);
label_5c221e:
    v5 = v30;
    v13 = v29;
    party.b = v30;
    party.a = v29;
    party.text = 0;
    party.ent = (unsigned int)gm_LocalPlayerSlot * 0x21c + 0x7f4ca0;
    v9 = d2_LoadForm(0,0,(char *)0x6ac5bc);
    v28 = v9;
    d2_SetForm(v9,0);
    d2_InitWindowBounds(d2_CurrentWindowId);
    d2_CenterDialogWindows(v9);
    d2_SetOverlayAnimation(0,0);
    d2_SetForm(v9,1);
    io_AppendText(0x6811b0);
    io_AppendText(0x1780,&timer);
    party.count = 0;
    v12 = 0;
    do {
      v2 = (unsigned short *)v20[v12];
      if (v2) {
        party.members[party.count].ent = v2;
        party.count++;
        io_AppendText(0x1781,*v2);
      }
      v12 += 1;
    } while (v12 < 4);
    io_AppendText(0x1782,v13 + 0x1773);
    if (v37)
      io_AppendText(0x1783,v5 + 0x177a);
    gm_ResolveDinnerParty(&party,0);
    io_AppendText(0x1784,party.text);
    d2_DialogButtonAction = -1;
    do {
      if (io_RightButtonReleased)
        d2_DialogCloseRequested = 1;
    } while (main_RunFrameLoop(0x5c18e0,0x677c7));
  }
  else {
    v9 = d2_LoadForm(0,0,(char *)0x6ac5bc);
    v28 = v9;
    d2_SetForm(v9,0);
    d2_InitWindowBounds(d2_CurrentWindowId);
    d2_CenterDialogWindows(v9);
    d2_SetOverlayAnimation(0,0);
    d2_DialogButtonAction = 0xffffffff;
    d2_SetForm(v9,1);
    io_AppendText(0x6811b0);
    io_AppendText(0x1772);
    v18 = 0;
    do {
      v13 = v18 & 0xff;
      v12 = d2_GetWindowListItem(v9,1,io_AppendText((char *)0x6ac5b0,v13 + 0x1773));
      v17[v18 & 0xff] = v12;
      v6 = (char)v18 + 1;
      v18 = ((v18 & 0xffffff00) | ((v6) & 0xff));
    } while (v6 < 5);
    v10 = d2_GetWindowListItem(v9,1,io_AppendText((char *)0x6ac5a4,v6 + 0x1773));
    v12 = a1;
    d2_DialogButtonAction = -1;
    v17[v18 & 0xff] = v10;
    v10 = v27;
    do {
      if (io_RightButtonReleased) {
        v10 = 0;
        d2_DialogCloseRequested = 1;
      }
      if (d2_DialogButtonAction != -1) {
        v6 = 0;
        v18 = 0;
        do {
          if (d2_CurrentElementId == v17[v18 & 0xff]) {
            cm_BeginPacketFieldDelta(v12,*(unsigned int *)(v12 + 2));
            cm_AppendPacketFieldDelta(1,1,0x2c,&v18);
            cm_RequestChangeAttribute();
            d2_DialogCloseRequested = 1;
            v29 = v18 & 0xff;
            v10 = 1;
            break;
          }
          v6 += 1;
          v18 = ((v18 & 0xffffff00) | ((v6) & 0xff));
        } while (v6 < 6);
      }
      v8 = main_RunFrameLoop(0x5c18e0,0x677c7);
      v9 = v28;
    } while (v8);
    v27 = v10;
    if (v10) {
      if (v37) { 
        d2_SetForm(v28,1);
        io_AppendText(0x6811b0);
        io_AppendText(0x1779);
        v18 = 0;
        do {
          v13 = v18 & 0xff;
          v12 = d2_GetWindowListItem(v9,1,io_AppendText((char *)0x6ac5b0,v13 + 0x177a));
          v17[v18 & 0xff] = v12;
          v6 = (char)v18 + 1;
          v18 = ((v18 & 0xffffff00) | ((v6) & 0xff));
        } while (v6 < 5);
        v12 = d2_GetWindowListItem(v9,1,io_AppendText((char *)0x6ac5a4,v6 + 0x177a));
        v10 = a1;
        d2_DialogButtonAction = -1;
        v17[v18 & 0xff] = v12;
        v12 = v27;
        do {
          if (io_RightButtonReleased) {
            v12 = 0;
            d2_DialogCloseRequested = 1;
          }
          if (d2_DialogButtonAction != -1) {
            v6 = 0;
            v18 = 0;
            do {
              if (d2_CurrentElementId == v17[v18 & 0xff]) {
                cm_BeginPacketFieldDelta(v10,*(unsigned int *)(v10 + 2));
                cm_AppendPacketFieldDelta(1,1,0x2d,&v18);
                cm_RequestChangeAttribute();
                d2_DialogCloseRequested = 1;
                v30 = v18 & 0xff;
                v12 = 1;
                break;
              }
              v6 += 1;
              v18 = ((v18 & 0xffffff00) | ((v6) & 0xff));
            } while (v6 < 6);
          }
        } while (main_RunFrameLoop(0x5c18e0,0x677c7));
        v27 = v12;
      }
      else {
        v19 = 5;
        cm_BeginPacketFieldDelta(a1,*(unsigned int *)(a1 + 2));
        cm_AppendPacketFieldDelta(1,1,0x2d,&v19);
        cm_RequestChangeAttribute();
        v12 = v27;
      }
      if (v12) {
        d2_DestroyForm(v28);
        v36 = -1;
        v18 = 1;
        commit = -1;
        v38 = -1;
        v9 = d2_LoadForm(0,0,(char *)0x6ac58c);
        v28 = v9;
        d2_SetForm(v9,0);
        d2_InitWindowBounds(d2_CurrentWindowId);
        d2_CenterDialogWindows(v9);
        d2_SetOverlayAnimation(0,0);
        d2_DialogButtonAction = -1;
        v12 = -1;
        do {
          if (v18) {
            v12 = 0;
            v18 = 0;
            d2_SetForm(v9,1);
            io_AppendText(0x6811b0);
            io_AppendText(0x1769,&timer);
            party.text = 0;
            v10 = 0;
            party.count = 0;
            party.b = v30;
            party.ent = (unsigned int)gm_LocalPlayerSlot * 0x21c + 0x7f4ca0;
            party.a = v29;
            do {
              v2 = *(unsigned short **)((int)v20 + v12);
              if (v2) { 
                v11 = io_AppendText(0x176a,*v2);
                *(unsigned int *)((int)v17 + v12) = d2_GetWindowListItem(v9,1,v11);
                party.members[party.count].ent = v2;
                v10 += 1;
                party.count++;
              }
              else {
                *(unsigned int *)((int)v17 + v12) = 0xffffffff;
              }
              v12 += 4;
            } while (v12 < 0x10);
            gm_ResolveDinnerParty(&party,0);
            d2_SetForm(v9,2);
            io_AppendText(0x6811b0);
            v11 = io_AppendText(0x176b,party.text);
            v12 = d2_GetWindowListItem(v9,2,v11);
            v36 = v12;
            if (v10 == 4)
              d2_SetElementEnabled(v12,0);
            d2_SetForm(v9,3);
            io_AppendText(0x6811b0);
            io_FormatTextBuffer(buttonLabelA,0x176c);
            io_FormatTextBuffer(buttonLabelB,0x176d);
            d2_CreateButtonRow(d2_CurrentWindowId,0,buttons,2,buttonLabelA,buttonLabelB);
            commit = buttons[0];
            v38 = buttons[1];
            if (!v10)
              d2_SetElementEnabled(buttons[0],0);
          }
          if (d2_DialogButtonAction != -1) {
            if (io_RightButtonReleased) {
              v27 = 0;
              d2_DialogCloseRequested = 1;
            }
            if (d2_CurrentElementId != v36) { 
              if (d2_CurrentElementId != commit) { 
                if (d2_CurrentElementId != v38) { 
                  v10 = 0;
                  do {
                    if (d2_CurrentElementId == *(int *)((int)v17 + v10)) {
                      *(unsigned int *)((int)v20 + v10) = 0;
                      v18 = 1;
                    }
                    v10 += 4;
                  } while (v10 < 0x10);
                }
                else {
                  v27 = 0;
                  d2_DialogCloseRequested = 1;
                }
              }
              else {
                v8 = 0;
                v27 = -1;
                *(unsigned char*) (message + 4) = 0x37;
                *(unsigned int*) (message + 0x6c) = 0;
                *(unsigned char*) (message + 0x36) = 2;
                *(unsigned int*) (message + 8) = *(unsigned int *)((unsigned int)gm_LocalPlayerSlot * 0x21c + 0x7f4ca4);
                *(unsigned int*) (message + 0xc) = *(unsigned int *)(a0 + 1);
                cm_SendCopyEntityData(message);
                v10 = 0;
                do {
                  v12 = v20[v8];
                  if (v12) {
                    cm_BeginPacketFieldDelta(a1,*(unsigned int *)(a1 + 2));
                    cm_AppendPacketFieldDelta(4,1,v10 * 4 + 0x1c,(unsigned int *)(v12 + 4));
                    cm_RequestChangeAttribute();
                    *(unsigned char*) (message + 4) = 0x36;
                    *(unsigned int*) (message + 8) = *(unsigned int *)(v12 + 4);
                    *(unsigned int*) (message + 0x68) = 0;
                    *(unsigned int*) (message + 0xc) = *(unsigned int *)(a0 + 1);
                    *(int*) (message + 0x5c) = timer.b;
                    *(int*) (message + 0x60) = timer.c;
                    *(int*) (message + 0x58) = timer.a;
                    *(unsigned short*) (message + 0x64) = timer.d;
                    if ((*(char *)(v12 + 2) == '\x06') || (*(unsigned char*) (message + 0x36) = 1, *(char *)(v12 + 2) == '\a'))
                      *(unsigned char*) (message + 0x36) = 9;
                    cm_SendCopyEntityData(message);
                    v10 += 1;
                  }
                  v4 = a1;
                  v8 += 1;
                  v9 = v28;
                  v12 = v36;
                } while (v8 < 4);
                while (v28 = v9, v36 = v12, v10 <= 3) {
                  cm_BeginPacketFieldDelta(v4,*(unsigned int *)(v4 + 2));
                  cm_AppendPacketFieldDelta(4,1,v10 * 4 + 0x1c,&v27);
                  cm_RequestChangeAttribute();
                  v10 += 1;
                  v9 = v28;
                  v12 = v36;
                }
                v27 = 1;
                d2_DialogCloseRequested = 1;
              }
            }
            else {
              memset(v15 + 7, 0xff, 8 * sizeof(int));
              v14 = v15 + 7;
              v15[5] |= 2;
              v10 = 0;
              do {
                if ((unsigned short *)v20[v10]) {
                  *(unsigned short *)v14 = *(unsigned short *)v20[v10];
                  v14 = (unsigned int *)((int)v14 + 2);
                }
                v10 += 1;
              } while (v10 < 4);
              v10 = d2_OpenTargetPicker(v15,(char *)0x6ac578,0,0);
              if (v10) {
                v8 = 0;
                do {
                  if (!v20[v8]) {
                    v20[v8] = v10;
                    v18 = 1;
                    break;
                  }
                  v8 += 1;
                } while (v8 < 4);
              }
            }
          }
        } while (main_RunFrameLoop(0x5c18e0,0x677c7));
        if (v27) {
          d2_DestroyForm(v9);
          goto label_5c221e;
        }
      }
    }
  }
  d2_DestroyForm(v28);
  d3_EndCameraAndUiMode();
}
