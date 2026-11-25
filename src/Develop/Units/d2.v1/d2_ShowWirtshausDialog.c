/* Wirtshaus dialog routine (0x5a1430). Opens locations\wirtshaus\WSIntro and
 * builds the dialog from the player record at g_774970, then polls the modal
 * choice loop. Chosen action opens the guest/order subdialog, runs the Wirtshaus
 * action helpers (0x5a0cd0, 0x492d60, 0x493000) and formats the result lines.
 * Stack slots are bound to the native frame offsets (frame 0x390). */
extern int g_774654; extern int g_14ce8e0; extern int g_100f1dc;
extern int d2_CurrentWindowId; extern unsigned char g_773d75; extern unsigned short g_774970; extern unsigned short g_7f4c04; extern char g_7f4ca4[];
#include <math.h>
#include <string.h>

float __cdecl fcn_0042e450(void);
int __cdecl fcn_00433780();
int __cdecl fcn_00438b40();
int __cdecl d3_SetObjectRotation();
int __cdecl CompareVector3WithinTolerance();
int __cdecl d2_ClearWindowChildren();
int __cdecl fcn_00470820();
int __cdecl fcn_00471af0();
int __cdecl d2_CenterDialogWindows();
int __cdecl fcn_00471e30();
int __cdecl fcn_00472250();
int __cdecl d2_SetForm();
int __cdecl d2_SetOverlayAnimation();
int __cdecl fcn_004927c0();
int __cdecl fcn_00492950();
int __cdecl fcn_00492d60();
int __cdecl fcn_00492e50();
int __cdecl fcn_00493000();
int __cdecl fcn_004c51a0();
int __cdecl fcn_00502850();
int __cdecl fcn_00502cd0();
int __cdecl fcn_00503fe0();
int __cdecl fcn_00509570();
int __cdecl fcn_0050b710(int a,unsigned char b);
int __cdecl fcn_0050dac0(unsigned short a);
int __cdecl io_AppendText();
int __cdecl io_FormatTextBuffer();
int __cdecl d3_AnimateCameraToStoredTransform();
int __cdecl fcn_00530510();
int __cdecl fcn_005340f0();
int __cdecl fcn_005373e0();
int __cdecl d2_ShowWirtshausRules();
int __cdecl fcn_005a0cd0();
int __cdecl fcn_005a1130();
void __cdecl fcn_00532ef0(void);

#define v13 ((int *)(frame + 0x18))
#define v14 (*(unsigned int *)(frame + 0x14))
#define v18 (*(char *)(frame + 0x78))
#define v19 (*(char *)(frame + 0x184))
#define v20 (*(char *)(frame + 0x290))
#define v21 ((int *)(frame + 0x44))
#define v22 ((int *)(frame + 0x6c))
#define v28 (*(int *)(frame + 0x0))
#define v29 (*(int *)(frame + 0x8))
#define v30 (*(int *)(frame + 0xc))
#define v2 (*(int *)(frame + 0x8))
#define v3 (*(int *)(frame + 0x4))
#define v25 (*(int *)(frame + 0x0))
#define v31 (*(int *)(frame + 0x10))
#define v32 (*(unsigned int *)(frame + 0x3c))
#define v33 (*(unsigned int *)(frame + 0x60))
#define v34 (*(unsigned int *)(frame + 0x68))
#define v35 (*(unsigned int *)(frame + 0x178))
#define v36 (*(unsigned int *)(frame + 0x17c))
#define v37 (*(unsigned int *)(frame + 0x180))
#define v38 (*(unsigned int *)(frame + 0x284))
#define v39 (*(unsigned int *)(frame + 0x288))
#define v40 (*(unsigned int *)(frame + 0x28c))
#define v41 (*(unsigned int *)(frame + 0x370))
#define v42 (*(int *)(frame + 0x374))
#define v43 (*(int *)(frame + 0x378))
#define v44 (*(int *)(frame + 0x37c))
#define v45 (*(int *)(frame + 0x380))
#define v46 (*(int *)(frame + 0x384))
#define v47 (*(unsigned int *)(frame + 0x388))

/* ADDRESS: GOLDTL 0x005a1430 */
void __cdecl d2_ShowWirtshausDialog(void)
{
	unsigned int *  v1;
	int *  v10;
	int v11;
	int *  v12;
	int v15;
	int v16;
	int v17;
	unsigned int *  v23;
	int *  v24;
	float v26;
	unsigned short *  v4;
	unsigned int playerSlot;
	unsigned int windowId;
	int v7;
	int v8;
	unsigned int v9;
	unsigned char frame[0x390];
  playerSlot = (*(unsigned short *)&g_774970);
  v14 = 0;
  v3 = playerSlot * 0x21c + 0x7f4ca0;
  v11 = 0x15;
  v24 = v13;
  while (v11) {
    v12 = &v24[1];
    *v24 = 0;
    v11 -= 1;
    v24 = v12;
  }
  v28 = -1;
  v30 = -1;
  v29 = -1;
  v11 = fcn_0050b710(fcn_0050dac0((unsigned short)playerSlot),(*(unsigned char *)&g_773d75));
  v7 = fcn_00509570(v3);
  windowId = fcn_00470820(0,0,(char *)0x6aa908);
  d2_SetForm(windowId,0);
  fcn_005340f0((*(int *)&d2_CurrentWindowId));
  d2_CenterDialogWindows(windowId);
  d2_SetForm(windowId,1);
  d2_SetOverlayAnimation(0,0);
  io_AppendText(0x1874);
  if (((!(fcn_0042e450() < *(float *)(v7 + 0x5c))) || ((*(unsigned short *)&g_7f4c04) <= 0xb)) || (v11 < 10000)) {
    d2_SetForm(windowId,2);
    io_AppendText(0x1875);
    if ((*(unsigned short *)&g_7f4c04) > 0xb) {
      v26 = *(float *)(v7 + 0x5c) * 0.66f - 0.02f;
      goto label_5a15b5;
    }
  }
  else {
    d2_SetForm(windowId,2);
    io_AppendText(0x1876);
    d2_SetForm(windowId,3);
    v29 = fcn_00472250(windowId,3,io_AppendText(0x1877));
    v28 = fcn_00472250(windowId,3,io_AppendText(0x1878));
    v30 = fcn_00472250(windowId,3,io_AppendText(0x1879));
    v26 = *(float *)(v7 + 0x5c) * 0.66f - 0.1f;
label_5a15b5:
    *(float *)(v7 + 0x5c) = v26;
  }
  /* Phase 2: modal choice poll (0x5a1536-0x5a15f0). */
  v2 = 1;
  (*(int *)&g_100f1dc) = -1;
  do {
    if (g_14ce8e0) { // branch-flip
      g_774654 = 1;
      v2 = 1;
    }
    else if ((*(int *)&g_100f1dc) != -1) {
      if ((*(int *)0x67d370) != v30) { // branch-flip
        if ((*(int *)0x67d370) != v28) { // branch-flip
          if ((*(int *)0x67d370) == v29) {
            fcn_00471af0(windowId,0);
            d2_ShowWirtshausRules();
            fcn_00471af0(windowId,1);
          }
        }
        else {
          g_774654 = 1;
          v2 = 0;
        }
      }
      else {
        g_774654 = 1;
        v2 = 1;
      }
    }
  } while (fcn_005373e0(0x5a1430,0x677c7));
  /* Phase 3: guest/order subdialog opened from the Wirtshaus menu. */
  if ((!v2) && (*(char *)((unsigned int)(*(unsigned short *)&g_774970) * 0x21c + 0x7f4ca8))) {
    d2_SetForm(windowId,3);
    io_AppendText(0x6811b0);
    v11 = fcn_00472250(windowId,3,io_AppendText(0x187a));
    v7 = fcn_00472250(windowId,3,io_AppendText(0x187b));
    v8 = fcn_00472250(windowId,3,io_AppendText(0x187c));
    (*(int *)&g_100f1dc) = -1;
    do {
      if ((*(int *)&g_100f1dc) != -1) {
        v9 = 1;
        if ((*(int *)0x67d370) != v11) {
          if ((*(int *)0x67d370) != v7) { // branch-flip
            if ((*(int *)0x67d370) == v8)
              v9 = 4;
          }
          else {
            v9 = 2;
          }
        }
        fcn_004927c0(v3,&v14,v9);
        g_774654 = 1;
      }
    } while (fcn_005373e0(0x5a1430,0x777c7));
    if (*(char *)((unsigned int)(*(unsigned short *)&g_774970) * 0x21c + 0x7f4ca8)) {
      d2_SetForm(windowId,2);
      io_AppendText(0x6811b0);
      v9 = (v13[2] != v3) ? 0x187d : 0x187e; // branch-flip
      io_AppendText(v9,v14);
      d2_SetForm(windowId,3);
      io_AppendText(0x6811b0);
      io_AppendText(0x187f);
      (*(int *)&g_100f1dc) = -1;
      do {
        if ((*(int *)&g_100f1dc) == 2)
          g_774654 = 1;
      } while (fcn_005373e0(0x5a1430,0x777c7));
      if (*(char *)((unsigned int)(*(unsigned short *)&g_774970) * 0x21c + 0x7f4ca8)) {
        fcn_00471e30(windowId);
        v22[1] = 2;
        v22[0] = -1;
        v22[2] = 0;
        v18 = 0;
        v2 = 1;
        memset((char *)v22 + 0xd, 0, 0xff);
        v35 = 0xffffffff;
        v36 = 3;
        v37 = 0;
        v19 = 0;
        memset((char *)&v35 + 0xd, 0, 0xff);
        v38 = 0xffffffff;
        v39 = 4;
        v40 = 0;
        v20 = 0;
        memset((char *)&v38 + 0xd, 0, 0xff);
        io_FormatTextBuffer(&v18,0x1880,v13[0]);
        io_FormatTextBuffer(&v19,0x1881,v13[0]);
        io_FormatTextBuffer(&v20,0x1882);
        v25 = v3 != v13[2];
        if (v25) {
          v12 = &v13[2];
          v24 = v21;
        }
        else {
          v24 = &v13[2];
          v12 = v21;
        }
        windowId = fcn_00470820(0,0,(char *)0x6aa8f0);
        d2_SetForm(windowId,0);
        fcn_005340f0((*(int *)&d2_CurrentWindowId));
        d2_CenterDialogWindows(windowId);
        d2_SetForm(windowId,1);
        d2_SetOverlayAnimation(0,0);
        io_AppendText(0x1874);
        v32 = 0;
        v33 = 0;
        if (v25) {
          v9 = 2;
          v10 = v12;
        }
        else {
          v9 = 3;
          v10 = v24;
        }
        fcn_005a0cd0(&v14,v10,1,windowId,v9,0x96,0);
        if (*(char *)((unsigned int)(*(unsigned short *)&g_774970) * 0x21c + 0x7f4ca8)) {
          fcn_00492d60(&v14,v13[2],1);
          fcn_00493000(&v14);
          if (v25) {
            v9 = 2;
            v10 = v12;
          }
          else {
            v9 = 3;
            v10 = v24;
          }
          fcn_005a0cd0(&v14,v10,1,windowId,v9,0x14,1);
          if (*(char *)((unsigned int)(*(unsigned short *)&g_774970) * 0x21c + 0x7f4ca8)) {
            if (v25) {
              v9 = 3;
              v10 = v24;
            }
            else {
              v9 = 2;
              v10 = v12;
            }
            fcn_005a0cd0(&v14,v10,1,windowId,v9,0x96,0);
            if (*(char *)((unsigned int)(*(unsigned short *)&g_774970) * 0x21c + 0x7f4ca8)) {
              fcn_00492d60(&v14,v21[0],1);
              fcn_00493000(&v14);
              if (v25) {
                v9 = 3;
                v10 = v24;
              }
              else {
                v9 = 2;
                v10 = v12;
              }
              fcn_005a0cd0(&v14,v10,1,windowId,v9,0x14,1);
              if (*(char *)((unsigned int)(*(unsigned short *)&g_774970) * 0x21c + 0x7f4ca8)) {
                if ((v13[1] != 5) && (v13[1] != 6)) {
                  if (v25) {
                    v9 = fcn_00492e50(&v14,*v12);
                    fcn_005a0cd0(&v14,v12,v9,windowId,2,0x96,0);
                    if (*(char *)((unsigned int)(*(unsigned short *)&g_774970) * 0x21c + 0x7f4ca8)) {
                      fcn_00492d60(&v14,*v12,v9);
                      fcn_00493000(&v14);
                      fcn_005a0cd0(&v14,v12,v9,windowId,2,0x14,1);
                      if (*(char *)((unsigned int)(*(unsigned short *)&g_774970) * 0x21c + 0x7f4ca8)) goto label_5a1b81;
                    }
                    goto label_532ef0;
                  }
label_5a1b81:
                  v25 = 0;
                  (*(int *)&g_100f1dc) = -1;
                  do {
                    if (v25)
                      g_774654 = 1;
                    else if (v2) {
                      v2 = 0;
                      d2_SetForm(windowId,4);
                      d2_ClearWindowChildren((*(int *)&d2_CurrentWindowId),1);
                      io_AppendText(0x6811b0);
                      v10 = v22;
                      v31 = 3;
                      do {
                        v11 = v10[1];
                        if (fcn_00492950(&v14,v3,v11)) { // branch-flip
                          v9 = io_AppendText(&v10[3]);
                          *v10 = fcn_00472250(windowId,4,v9);
                        }
                        else {
                          *v10 = -1;
                        }
                        v10 = &v10[0x43];
                        v31 -= 1;
                      } while (v31);
                    }
                    else if ((*(int *)&g_100f1dc) != -1) {
                      v11 = 0;
                      v10 = v22;
                      do {
                        if ((*(int *)0x67d370) == *v10) {
                          v2 = 1;
                          d2_SetForm(windowId,4);
                          io_AppendText(0x6811b0);
                          d2_ClearWindowChildren((*(int *)&d2_CurrentWindowId),1);
                          fcn_005a0cd0(&v14,v24,v22[v11 * 0x43 + 1],windowId,3,0x96,0);
                          fcn_00492d60(&v14,v3,v22[v11 * 0x43 + 1]);
                          fcn_00493000(&v14);
                          fcn_005a0cd0(&v14,v24,v22[v11 * 0x43 + 1],windowId,3,0x14,1);
                          if ((v13[1] != 5) && (v13[1] != 6)) {
                            v9 = fcn_00492e50(&v14,*v12);
                            fcn_005a0cd0(&v14,v12,v9,windowId,2,0x96,0);
                            fcn_00492d60(&v14,*v12,v9);
                            fcn_00493000(&v14);
                            fcn_005a0cd0(&v14,v12,v9,windowId,2,0x14,1);
                            if ((v13[1] != 5) && (v13[1] != 6)) break;
                          }
                          v25 = 1;
                          break;
                        }
                        v11 += 1;
                        v10 = &v10[0x43];
                      } while (v11 < 3);
                    }
                  } while (fcn_005373e0(0x5a1430,0x777c7));
                }
                if (*(char *)((unsigned int)(*(unsigned short *)&g_774970) * 0x21c + 0x7f4ca8)) {
                  fcn_005a1130(&v14,windowId);
                  if (((v13[1] == 5 && v3 == v13[2]) || (v13[1] == 6 && v3 == v21[0])))
                    fcn_004c51a0(*(unsigned int *)(playerSlot * 0x21c + (unsigned long)&g_7f4ca4),0xffffffff,0,v34);
                  do {
                    if (g_14ce8e0)
                      g_774654 = 1;
                  } while (fcn_005373e0(0x5a1430,0x777c7));
                }
              }
            }
          }
        }
      }
    }
  }
label_532ef0:
	fcn_00471e30(windowId);
	fcn_00532ef0();
}
