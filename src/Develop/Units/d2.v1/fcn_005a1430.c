/* Wirtshaus dialog routine (0x5a1430). Opens locations\wirtshaus\WSIntro and
 * builds the dialog from the player record at g_774970, then polls the modal
 * choice loop. Chosen action opens the guest/order subdialog, runs the Wirtshaus
 * action helpers (0x5a0cd0, 0x492d60, 0x493000) and formats the result lines.
 * Stack slots are bound to the native frame offsets (frame 0x390). */

#include <math.h>

int __cdecl fcn_0042e450();
int __cdecl fcn_00433780();
int __cdecl fcn_00438b40();
int __cdecl fcn_00438cb0();
int __cdecl fcn_00451840();
int __cdecl fcn_0046f2c0();
int __cdecl fcn_00470820();
int __cdecl fcn_00471af0();
int __cdecl fcn_00471b60();
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
int __cdecl fcn_0050b710();
int __cdecl fcn_0050dac0();
int __cdecl io_AppendText();
int __cdecl io_FormatTextBuffer();
int __cdecl fcn_0052d820();
int __cdecl fcn_00530510();
int __cdecl fcn_005340f0();
int __cdecl fcn_005373e0();
int __cdecl fcn_005a0960();
int __cdecl fcn_005a0cd0();
int __cdecl fcn_005a1130();

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
void __cdecl fcn_005a1430(unsigned int a0,unsigned int a1)
{
	unsigned int *  v1;
	int *  v10;
	int v11;
	int *  v12;
	int v15;
	int v16;
	int v17;
	int v2;
	unsigned int *  v23;
	int *  v24;
	int v25;
	float v26;
	double v27;
	int v3;
	unsigned short *  v4;
	unsigned int v5;
	unsigned int v6;
	int v7;
	int v8;
	unsigned int v9;
	unsigned char frame[0x390];
  v5 = (unsigned int)(*(int *)0x774970);
  v14 = 0;
  v3 = v5 * 0x21c + 0x7f4ca0;
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
  v6 = fcn_0050dac0(CONCAT22((short)((unsigned int)a1 >> 0x10),(*(int *)0x774970)),(*(int *)0x773d75));
  v11 = fcn_0050b710(v6);
  v7 = fcn_00509570(v3);
  v6 = fcn_00470820(0,0,(char *)0x6aa908);
  d2_SetForm(v6,0);
  fcn_005340f0((*(int *)0x772514));
  fcn_00471b60(v6);
  d2_SetForm(v6,1);
  d2_SetOverlayAnimation(0,0);
  io_AppendText(0x1874);
  v27 = (double)fcn_0042e450();
  if ((((double)*(float *)(v7 + 0x5c) <= v27) || ((*(int *)0x7f4c04) <= 0xb)) || (v11 < 10000)) {
    d2_SetForm(v6,2);
    io_AppendText(0x1875);
    if (0xc <= (*(int *)0x7f4c04)) {
      v26 = *(float *)(v7 + 0x5c) * (*(int *)0x664178) - (*(int *)0x6628ac);
      goto label_5a15b5;
    }
  }
  else {
    d2_SetForm(v6,2);
    io_AppendText(0x1876);
    d2_SetForm(v6,3);
    v29 = fcn_00472250(v6,3,io_AppendText(0x1877));
    v28 = fcn_00472250(v6,3,io_AppendText(0x1878));
    v30 = fcn_00472250(v6,3,io_AppendText(0x1879));
    v26 = *(float *)(v7 + 0x5c) * (*(int *)0x664178) - (*(int *)0x662a3c);
label_5a15b5:
    *(float *)(v7 + 0x5c) = v26;
  }
  /* Phase 2: modal choice poll (0x5a1536-0x5a15f0). */
  v2 = 1;
  (*(int *)0x100f1dc) = -1;
  do {
    if ((*(int *)0x14ce8e0)) { // branch-flip
      (*(int *)0x774654) = 1;
      v2 = 1;
    }
    else if ((*(int *)0x100f1dc) != -1) {
      if ((*(int *)0x67d370) != v30) { // branch-flip
        if ((*(int *)0x67d370) != v28) { // branch-flip
          if ((*(int *)0x67d370) == v29) {
            fcn_00471af0(v6,0);
            fcn_005a0960();
            fcn_00471af0(v6,1);
          }
        }
        else {
          (*(int *)0x774654) = 1;
          v2 = 0;
        }
      }
      else {
        (*(int *)0x774654) = 1;
        v2 = 1;
      }
    }
  } while (fcn_005373e0(0x5a1430,0x677c7));
  /* Phase 3: guest/order subdialog opened from the Wirtshaus menu. */
  if ((!v2) && (*(char *)((unsigned int)(*(int *)0x774970) * 0x21c + 0x7f4ca8))) {
    d2_SetForm(v6,3);
    io_AppendText(0x6811b0);
    v11 = fcn_00472250(v6,3,io_AppendText(0x187a));
    v7 = fcn_00472250(v6,3,io_AppendText(0x187b));
    v8 = fcn_00472250(v6,3,io_AppendText(0x187c));
    (*(int *)0x100f1dc) = -1;
    do {
      if ((*(int *)0x100f1dc) != -1) {
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
        (*(int *)0x774654) = 1;
      }
    } while (fcn_005373e0(0x5a1430,0x777c7));
    if (*(char *)((unsigned int)(*(int *)0x774970) * 0x21c + 0x7f4ca8)) {
      d2_SetForm(v6,2);
      io_AppendText(0x6811b0);
      v9 = (v13[2] != v3) ? 0x187d : 0x187e; // branch-flip
      io_AppendText(v9,v14);
      d2_SetForm(v6,3);
      io_AppendText(0x6811b0);
      io_AppendText(0x187f);
      (*(int *)0x100f1dc) = -1;
      do {
        if ((*(int *)0x100f1dc) == 2)
          (*(int *)0x774654) = 1;
      } while (fcn_005373e0(0x5a1430,0x777c7));
      if (*(char *)((unsigned int)(*(int *)0x774970) * 0x21c + 0x7f4ca8)) {
        fcn_00471e30(v6);
        v22[1] = 2;
        v22[0] = -1;
        v22[2] = 0;
        v18 = 0;
        v2 = 1;
        v11 = 0x3f;
        v23 = &v15;
        while (v11) {
          v1 = &v23[1];
          *v23 = 0;
          v11 -= 1;
          v23 = v1;
        }
        *(unsigned short *)v23 = 0;
        *(char *)((int)v23 + 2) = 0;
        v35 = 0xffffffff;
        v36 = 3;
        v37 = 0;
        v19 = 0;
        v11 = 0x3f;
        v23 = &v16;
        while (v11) {
          v1 = &v23[1];
          *v23 = 0;
          v11 -= 1;
          v23 = v1;
        }
        *(unsigned short *)v23 = 0;
        *(char *)((int)v23 + 2) = 0;
        v38 = 0xffffffff;
        v39 = 4;
        v40 = 0;
        v20 = 0;
        v11 = 0x3f;
        v23 = &v17;
        while (v11) {
          v1 = &v23[1];
          *v23 = 0;
          v11 -= 1;
          v23 = v1;
        }
        *(unsigned short *)v23 = 0;
        *(char *)((int)v23 + 2) = 0;
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
        v6 = fcn_00470820(0,0,(char *)0x6aa8f0);
        d2_SetForm(v6,0);
        fcn_005340f0((*(int *)0x772514));
        fcn_00471b60(v6);
        d2_SetForm(v6,1);
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
        fcn_005a0cd0(&v14,v10,1,v6,v9,0x96,0);
        if (*(char *)((unsigned int)(*(int *)0x774970) * 0x21c + 0x7f4ca8)) {
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
          fcn_005a0cd0(&v14,v10,1,v6,v9,0x14,1);
          if (*(char *)((unsigned int)(*(int *)0x774970) * 0x21c + 0x7f4ca8)) {
            if (v25) {
              v9 = 3;
              v10 = v24;
            }
            else {
              v9 = 2;
              v10 = v12;
            }
            fcn_005a0cd0(&v14,v10,1,v6,v9,0x96,0);
            if (*(char *)((unsigned int)(*(int *)0x774970) * 0x21c + 0x7f4ca8)) {
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
              fcn_005a0cd0(&v14,v10,1,v6,v9,0x14,1);
              if (*(char *)((unsigned int)(*(int *)0x774970) * 0x21c + 0x7f4ca8)) {
                if ((v13[1] != 5) && (v13[1] != 6)) {
                  if (v25) {
                    v9 = fcn_00492e50(&v14,*v12);
                    fcn_005a0cd0(&v14,v12,v9,v6,2,0x96,0);
                    if (*(char *)((unsigned int)(*(int *)0x774970) * 0x21c + 0x7f4ca8)) {
                      fcn_00492d60(&v14,*v12,v9);
                      fcn_00493000(&v14);
                      fcn_005a0cd0(&v14,v12,v9,v6,2,0x14,1);
                      if (*(char *)((unsigned int)(*(int *)0x774970) * 0x21c + 0x7f4ca8)) goto label_5a1b81;
                    }
                    goto label_532ef0;
                  }
label_5a1b81:
                  v25 = 0;
                  (*(int *)0x100f1dc) = -1;
                  do {
                    if (v25)
                      (*(int *)0x774654) = 1;
                    else if (v2) {
                      v2 = 0;
                      d2_SetForm(v6,4);
                      fcn_0046f2c0((*(int *)0x772514),1);
                      io_AppendText(0x6811b0);
                      v10 = v22;
                      v31 = 3;
                      do {
                        v11 = v10[1];
                        if (fcn_00492950(&v14,v3,v11)) { // branch-flip
                          v9 = io_AppendText(&v10[3]);
                          *v10 = fcn_00472250(v6,4,v9);
                        }
                        else {
                          *v10 = -1;
                        }
                        v10 = &v10[0x43];
                        v31 -= 1;
                      } while (v31);
                    }
                    else if ((*(int *)0x100f1dc) != -1) {
                      v11 = 0;
                      v10 = v22;
                      do {
                        if ((*(int *)0x67d370) == *v10) {
                          v2 = 1;
                          d2_SetForm(v6,4);
                          io_AppendText(0x6811b0);
                          fcn_0046f2c0((*(int *)0x772514),1);
                          fcn_005a0cd0(&v14,v24,v22[v11 * 0x43 + 1],v6,3,0x96,0);
                          fcn_00492d60(&v14,v3,v22[v11 * 0x43 + 1]);
                          fcn_00493000(&v14);
                          fcn_005a0cd0(&v14,v24,v22[v11 * 0x43 + 1],v6,3,0x14,1);
                          if ((v13[1] != 5) && (v13[1] != 6)) {
                            v9 = fcn_00492e50(&v14,*v12);
                            fcn_005a0cd0(&v14,v12,v9,v6,2,0x96,0);
                            fcn_00492d60(&v14,*v12,v9);
                            fcn_00493000(&v14);
                            fcn_005a0cd0(&v14,v12,v9,v6,2,0x14,1);
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
                if (*(char *)((unsigned int)(*(int *)0x774970) * 0x21c + 0x7f4ca8)) {
                  fcn_005a1130(&v14,v6);
                  if (((v13[1] == 5) || (v13[2] = v21[0], v13[1] == 6)) && (v3 == v13[2]))
                    fcn_004c51a0(*(unsigned int *)(v5 * 0x21c + 0x7f4ca4),0xffffffff,0,v34);
                  do {
                    if ((*(int *)0x14ce8e0))
                      (*(int *)0x774654) = 1;
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
  fcn_00471e30(v6);
  v2 = 0;
  if ((*(int *)0x6b5cc0)) {
    v46 = 0x3dcccccd;
    v45 = 0x7e3a40;
    v44 = 0x14ce880;
    v43 = 0x532f13;
    v46 = (*(int *)0x6b8014);
    if (fcn_00451840()) { // branch-flip
      v45 = 0x532f25;
      fcn_00433780();
      v45 = 0x7e3a40;
      v44 = (*(int *)0x6b8014);
      (*(int *)0x6b5cc0) = 0;
      (*(int *)0x6b5cbc) = 0;
      v2 = 1;
      v43 = 0x532f47;
      fcn_00438b40();
      v43 = 0x7e3a50;
      v42 = (*(int *)0x6b8014);
      v41 = 0x532f58;
      fcn_00438cb0();
    }
    else {
      v45 = 0x532f62;
      fcn_00433780();
      (*(int *)0x6b5cc0) = 0;
      (*(int *)0x6b5cbc) = 0;
    }
  }
  if (((*(int *)0x774650) <= (*(int *)0x774658)) || (v2)) {
    v46 = 0x3dcccccd;
    v44 = (*(int *)0x6b8014) + 0x84;
    v45 = 0x7e3a50;
    v43 = 0x533015;
    if (fcn_00451840()) {
      v46 = 0x3dcccccd;
      v44 = (*(int *)0x6b8014) + 0x4c;
      v45 = 0x7e3a40;
      v43 = 0x533034;
      if (fcn_00451840()) goto label_533077;
    }
    if (!v2) {
      v46 = 0x533044;
      fcn_0052d820();
      if ((*(int *)0x7746a8)) {
        v3 = *(int *)((*(int *)0x7746a8) + 0x1d4);
        if ((v3) && (*(int *)(v3 + 0x18c))) {
          v45 = v3 + 400;
          v46 = 0;
          v44 = 3;
          v43 = (*(int *)0x7746a8);
          v42 = 0x53306e;
          (*(int (__cdecl **)())(v3 + 0x18c))();
        }
        (*(int *)0x7746a8) = 0;
      }
    }
  }
  else if ((*(int *)0x774650) - (*(int *)0x774654) <= (*(int *)0x77465c)) {
    v46 = 0x532f9f;
    fcn_0052d820();
    (*(int *)0x77465c) = (*(int *)0x774650) - (*(int *)0x774654);
    if ((*(int *)0x7746a8)) {
      v3 = *(int *)((*(int *)0x7746a8) + 0x1d4);
      if ((v3) && (*(int *)(v3 + 0x18c))) {
        v45 = v3 + 400;
        v46 = 0;
        v44 = 3;
        v43 = (*(int *)0x7746a8);
        v42 = 0x532fdd;
        (*(int (__cdecl **)())(v3 + 0x18c))();
      }
      (*(int *)0x7746a8) = 0;
    }
    if (!(*(int *)0x7e2a9c))
      return;
    v46 = 0x532ff7;
    fcn_00530510();
  }
label_533077:
  if (!(*(int *)0x7e2a9c))
    return;
  (*(int *)0x7e2a9c) = 0;
  (*(int *)0x7e2aa0) = 0;
  (*(int *)0x7ea3bc) = 0;
  (*(int *)0x7746c0) = 0;
  v3 = (*(int *)0x7746c8);
  if ((*(int *)0x7746c4)) { // branch-flip
    if (!(*(int *)0x7746c8)) {
      (*(int *)0x7746c0) = 0;
      (*(int *)0x7e2a9c) = 0;
      (*(int *)0x7e2aa0) = 0;
      (*(int *)0x7ea3bc) = 0;
      return;
    }
  }
  else {
    if ((*(int *)0x7746c8)) goto label_530554;
    v47 = 0x44;
    v46 = 0;
    v45 = 1;
    v44 = 0x530547;
    v3 = fcn_00503fe0();
  }
  if (!v3)
    return;
label_530554:
  (*(int *)0x7746f4) = 0;
  v45 = *(unsigned int *)(v3 + 0x5d);
  v47 = 5;
  v46 = 1;
  v44 = 0x530567;
  v4 = (unsigned short *)fcn_00502cd0();
  if (!v4)
    return;
  do {
    if (*(char *)((*(int *)0x99ec10) + (unsigned int)*v4 * 0x41) == '\x1d')
      *(unsigned int *)&v4[0x10] = *(unsigned int *)&v4[0x10] & 0xfffffffd;
    v46 = 0x530590;
    v4 = (unsigned short *)fcn_00502850();
  } while (v4);
  return;
}
