/* Reconstructed from native disassembly; frame slots follow the decompiler map. */

#include <math.h>

int __cdecl fcn_00433780();
int __cdecl fcn_00438b40();
int __cdecl fcn_00438cb0();
int __cdecl fcn_00451840();
int __cdecl fcn_00470820();
int __cdecl fcn_00471b60();
int __cdecl fcn_00471e30();
int __cdecl fcn_00472250();
int __cdecl fcn_00472640();
int __cdecl d2_SetForm();
int __cdecl fcn_00473a90();
int __cdecl fcn_00494470();
int __cdecl fcn_004c4510();
int __cdecl fcn_004c4570();
int __cdecl fcn_004c5360();
int __cdecl fcn_004c5530();
int __cdecl fcn_00500bb0();
int __cdecl fcn_00502850();
int __cdecl fcn_00502cd0();
int __cdecl fcn_00503fe0();
int __cdecl fcn_00508e40();
int __cdecl fcn_00519190();
int __cdecl fcn_0051af00();
int __cdecl fcn_0052d820();
int __cdecl fcn_00530510();
int __cdecl fcn_00533a60();
int __cdecl fcn_005340f0();
int __cdecl fcn_005373e0();
int __cdecl he_fn_Handlung();
int __cdecl fcn_005463a0();
int __cdecl fcn_005cd440();

/* ADDRESS: GOLDTL 0x005c18e0 */
void __cdecl fcn_005c18e0(int a0,int a1)
{
  unsigned int *v1;
  int v10;
  unsigned int v11; 
  int v12;
  unsigned int v13;
  unsigned int *v14;
  unsigned int v15 [4]; 
  unsigned int v16; 
  int v17 [6];
  unsigned int v18; 
  char v19; 
  unsigned short *v2;
  int v20 [6]; 
  unsigned int v21 [8];
  char v22 [224];
  char v23 [256];
  int v24; 
  unsigned int v25 [13];
  char v26 [4];
  int v27; 
  unsigned int v28; 
  unsigned int v29; 
  int v3;
  unsigned int v30; 
  unsigned short v31; 
  unsigned short v32; 
  unsigned short v33; 
  unsigned short v34; 
  unsigned short v35; 
  int v36; 
  unsigned int v37; 
  int v38; 
  unsigned int v39; 
  int v4;
  unsigned int v40; 
  unsigned int v41; 
  unsigned int v42; 
  int v43; 
  unsigned int v44; 
  unsigned int v45; 
  char v46; 
  unsigned int v47; 
  unsigned int v48; 
  char v49; 
  unsigned int v5;
  unsigned int v50; 
  unsigned int v51; 
  unsigned int v52; 
  unsigned short v53; 
  unsigned int v54; 
  unsigned int v55; 
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
  v16 = (*(int *)0x7f4c00);
  v32 = (unsigned short)((unsigned int)(*(int *)0x7f4c04) >> 0x10);
  v31 = (unsigned short)(*(int *)0x7f4c04);
  v35 = (*(int *)0x7f4c0c);
  v34 = (unsigned short)((unsigned int)(*(int *)0x7f4c08) >> 0x10);
  v33 = (unsigned short)(*(int *)0x7f4c08);
  v12 = 0x14;
  v14 = v15;
  while (v12) {
    v1 = &v14[1];
    *v14 = 0;
    v12 -= 1;
    v14 = v1;
  }
  v29 = 6;
  v44 = 6;
  v27 = 0;
  v20[0] = 0;
  v20[1] = 0;
  v20[2] = 0;
  v20[3] = 0;
  v30 = 5;
  v15[1] = 0x400;
  v15[2] = (*(int *)0x666018);
  v15[3] = (*(int *)0x66601c);
  fcn_00500bb0(&v16,0x18,0,0);
  v31 = 0x14;
  v33 = 0;
  v32 = 0;
  v12 = fcn_005463a0(1,0,0x37);
  v10 = a0;
  while ((v12 && (*(int *)(v12 + 0x10) != *(int *)(v10 + 1)))) {
    v12 = he_fn_Handlung();
  }
  v8 = fcn_00502cd0(*(unsigned int *)(v10 + 0x5d),1,0,0x18);
  v10 = a1;
  v37 = (unsigned int)(v8 != 0);
  if (v12) { 
    v16 = *(unsigned int *)(v12 + 0x52);
    v14 = (unsigned int *)(a1 + 0x1c);
    v32 = (unsigned short)((unsigned int)*(unsigned int *)(v12 + 0x56) >> 0x10);
    v31 = (unsigned short)*(unsigned int *)(v12 + 0x56);
    v34 = (unsigned short)((unsigned int)*(unsigned int *)(v12 + 0x5a) >> 0x10);
    v33 = (unsigned short)*(unsigned int *)(v12 + 0x5a);
    v35 = *(unsigned short *)(v12 + 0x5e);
    v12 = 0;
    do {
      v9 = *v14;
      v20[v12] = fcn_00508e40(v9);
      v12 += 1;
      v14 = &v14[1];
    } while (v12 < 4);
    v29 = (unsigned int)*(unsigned char *)(v10 + 0x2c);
    v30 = (unsigned int)*(unsigned char *)(v10 + 0x2d);
label_5c221e:
    v5 = v30;
    v13 = v29;
    v40 = v30;
    v39 = v29;
    v41 = 0;
    v20[5] = (unsigned int)(*(int *)0x774970) * 0x21c + 0x7f4ca0;
    v9 = fcn_00470820(0,0,(char *)0x6ac5bc);
    v28 = v9;
    d2_SetForm(v9,0);
    fcn_005340f0((*(int *)0x772514));
    fcn_00471b60(v9);
    fcn_00473a90(0,0);
    d2_SetForm(v9,1);
    fcn_00519190(0x6811b0);
    fcn_00519190(0x1780,&v16);
    v42 &= 0xffffff00;
    v12 = 0;
    do {
      v2 = (unsigned short *)v20[v12];
      if (v2) {
        v21[(v42 & 0xff) * 2] = v2;
        v42 = ((v42 & 0xffffff00) | (((char)v42 + '\x01') & 0xff));
        fcn_00519190(0x1781,*v2);
      }
      v12 += 1;
    } while (v12 < 4);
    fcn_00519190(0x1782,v13 + 0x1773);
    if (v37)
      fcn_00519190(0x1783,v5 + 0x177a);
    fcn_00494470(&v20[5],0);
    fcn_00519190(0x1784,v41);
    (*(int *)0x100f1dc) = -1;
    do {
      if ((*(int *)0x14ce8e0))
        (*(int *)0x774654) = 1;
    } while (fcn_005373e0(0x5c18e0,0x677c7));
  }
  else {
    v9 = fcn_00470820(0,0,(char *)0x6ac5bc);
    v28 = v9;
    d2_SetForm(v9,0);
    fcn_005340f0((*(int *)0x772514));
    fcn_00471b60(v9);
    fcn_00473a90(0,0);
    (*(int *)0x100f1dc) = 0xffffffff;
    d2_SetForm(v9,1);
    fcn_00519190(0x6811b0);
    fcn_00519190(0x1772);
    v18 &= 0xffffff00;
    do {
      v13 = v18 & 0xff;
      v12 = fcn_00472250(v9,1,fcn_00519190((char *)0x6ac5b0,v13 + 0x1773));
      v17[v18 & 0xff] = v12;
      v6 = (char)v18 + 1;
      v18 = ((v18 & 0xffffff00) | ((v6) & 0xff));
    } while (v6 < 5);
    v10 = fcn_00472250(v9,1,fcn_00519190((char *)0x6ac5a4,v6 + 0x1773));
    v12 = a1;
    (*(int *)0x100f1dc) = -1;
    v17[v18 & 0xff] = v10;
    v10 = v27;
    do {
      if ((*(int *)0x14ce8e0)) {
        v10 = 0;
        (*(int *)0x774654) = 1;
      }
      if ((*(int *)0x100f1dc) != -1) {
        v6 = 0;
        v18 &= 0xffffff00;
        do {
          if ((*(int *)0x67d370) == v17[v18 & 0xff]) {
            fcn_004c4510(v12,*(unsigned int *)(v12 + 2));
            fcn_004c4570(1,1,0x2c,&v18);
            fcn_004c5360();
            (*(int *)0x774654) = 1;
            v29 = v18 & 0xff;
            v10 = 1;
            break;
          }
          v6 += 1;
          v18 = ((v18 & 0xffffff00) | ((v6) & 0xff));
        } while (v6 < 6);
      }
      v8 = fcn_005373e0(0x5c18e0,0x677c7);
      v9 = v28;
    } while (v8);
    v27 = v10;
    if (v10) {
      if (v37) { 
        d2_SetForm(v28,1);
        fcn_00519190(0x6811b0);
        fcn_00519190(0x1779);
        v18 &= 0xffffff00;
        do {
          v13 = v18 & 0xff;
          v12 = fcn_00472250(v9,1,fcn_00519190((char *)0x6ac5b0,v13 + 0x177a));
          v17[v18 & 0xff] = v12;
          v6 = (char)v18 + 1;
          v18 = ((v18 & 0xffffff00) | ((v6) & 0xff));
        } while (v6 < 5);
        v12 = fcn_00472250(v9,1,fcn_00519190((char *)0x6ac5a4,v6 + 0x177a));
        v10 = a1;
        (*(int *)0x100f1dc) = -1;
        v17[v18 & 0xff] = v12;
        v12 = v27;
        do {
          if ((*(int *)0x14ce8e0)) {
            v12 = 0;
            (*(int *)0x774654) = 1;
          }
          if ((*(int *)0x100f1dc) != -1) {
            v6 = 0;
            v18 &= 0xffffff00;
            do {
              if ((*(int *)0x67d370) == v17[v18 & 0xff]) {
                fcn_004c4510(v10,*(unsigned int *)(v10 + 2));
                fcn_004c4570(1,1,0x2d,&v18);
                fcn_004c5360();
                (*(int *)0x774654) = 1;
                v30 = v18 & 0xff;
                v12 = 1;
                break;
              }
              v6 += 1;
              v18 = ((v18 & 0xffffff00) | ((v6) & 0xff));
            } while (v6 < 6);
          }
        } while (fcn_005373e0(0x5c18e0,0x677c7));
        v27 = v12;
      }
      else {
        v19 = 5;
        fcn_004c4510(a1,*(unsigned int *)(a1 + 2));
        fcn_004c4570(1,1,0x2d,&v19);
        fcn_004c5360();
        v12 = v27;
      }
      if (v12) {
        fcn_00471e30(v28);
        v36 = -1;
        v18 = 1;
        v20[4] = -1;
        v38 = -1;
        v9 = fcn_00470820(0,0,(char *)0x6ac58c);
        v28 = v9;
        d2_SetForm(v9,0);
        fcn_005340f0((*(int *)0x772514));
        fcn_00471b60(v9);
        fcn_00473a90(0,0);
        (*(int *)0x100f1dc) = -1;
        v12 = -1;
        do {
          if (v18) {
            v12 = 0;
            v18 = 0;
            d2_SetForm(v9,1);
            fcn_00519190(0x6811b0);
            fcn_00519190(0x1769,&v16);
            v41 = 0;
            v10 = 0;
            v42 &= 0xffffff00;
            v40 = v30;
            v20[5] = (unsigned int)(*(int *)0x774970) * 0x21c + 0x7f4ca0;
            v39 = v29;
            do {
              v2 = *(unsigned short **)((int)v20 + v12);
              if (v2) { 
                v11 = fcn_00519190(0x176a,*v2);
                *(unsigned int *)((int)v17 + v12) = fcn_00472250(v9,1,v11);
                v21[(v42 & 0xff) * 2] = v2;
                v10 += 1;
                v42 = ((v42 & 0xffffff00) | (((char)v42 + '\x01') & 0xff));
              }
              else {
                *(unsigned int *)((int)v17 + v12) = 0xffffffff;
              }
              v12 += 4;
            } while (v12 < 0x10);
            fcn_00494470(&v20[5],0);
            d2_SetForm(v9,2);
            fcn_00519190(0x6811b0);
            v11 = fcn_00519190(0x176b,v41);
            v12 = fcn_00472250(v9,2,v11);
            v36 = v12;
            if (v10 == 4)
              fcn_00472640(v12,0);
            d2_SetForm(v9,3);
            fcn_00519190(0x6811b0);
            fcn_0051af00(v22,0x176c);
            fcn_0051af00(v23,0x176d);
            fcn_00533a60((*(int *)0x772514),0,&v24,2,v22,v23);
            v20[4] = v24;
            v38 = v43;
            if (!v10)
              fcn_00472640(v24,0);
          }
          if ((*(int *)0x100f1dc) != -1) {
            if ((*(int *)0x14ce8e0)) {
              v27 = 0;
              (*(int *)0x774654) = 1;
            }
            if ((*(int *)0x67d370) != v12) { 
              if ((*(int *)0x67d370) != v20[4]) { 
                if ((*(int *)0x67d370) != v38) { 
                  v10 = 0;
                  do {
                    if ((*(int *)0x67d370) == *(int *)((int)v17 + v10)) {
                      *(unsigned int *)((int)v20 + v10) = 0;
                      v18 = 1;
                    }
                    v10 += 4;
                  } while (v10 < 0x10);
                }
                else {
                  v27 = 0;
                  (*(int *)0x774654) = 1;
                }
              }
              else {
                v8 = 0;
                v27 = -1;
                v46 = 0x37;
                v55 = 0;
                v49 = 2;
                v47 = *(unsigned int *)((unsigned int)(*(int *)0x774970) * 0x21c + 0x7f4ca4);
                v48 = *(unsigned int *)(a0 + 1);
                fcn_004c5530(v26);
                v10 = 0;
                do {
                  v12 = v20[v8];
                  if (v12) {
                    fcn_004c4510(a1,*(unsigned int *)(a1 + 2));
                    fcn_004c4570(4,1,v10 * 4 + 0x1c,(unsigned int *)(v12 + 4));
                    fcn_004c5360();
                    v46 = 0x36;
                    v47 = *(unsigned int *)(v12 + 4);
                    v54 = 0;
                    v48 = *(unsigned int *)(a0 + 1);
                    v51 = CONCAT22(v32,v31);
                    v52 = CONCAT22(v34,v33);
                    v50 = v16;
                    v53 = v35;
                    if ((*(char *)(v12 + 2) == '\x06') || (v49 = 1, *(char *)(v12 + 2) == '\a'))
                      v49 = 9;
                    fcn_004c5530(v26);
                    v10 += 1;
                  }
                  v4 = a1;
                  v8 += 1;
                  v9 = v28;
                  v12 = v36;
                } while (v8 < 4);
                while (v28 = v9, v36 = v12, v10 <= 3) {
                  fcn_004c4510(v4,*(unsigned int *)(v4 + 2));
                  fcn_004c4570(4,1,v10 * 4 + 0x1c,&v27);
                  fcn_004c5360();
                  v10 += 1;
                  v9 = v28;
                  v12 = v36;
                }
                v27 = 1;
                (*(int *)0x774654) = 1;
              }
            }
            else {
              v10 = 8;
              v14 = v25;
              while (v10) {
                v1 = &v14[1];
                *v14 = 0xffffffff;
                v10 -= 1;
                v14 = v1;
              }
              v14 = v25;
              v45 |= 2;
              v10 = 0;
              do {
                if ((unsigned short *)v20[v10]) {
                  *(unsigned short *)v14 = *(unsigned short *)v20[v10];
                  v14 = (unsigned int *)((int)v14 + 2);
                }
                v10 += 1;
              } while (v10 < 4);
              v10 = fcn_005cd440(v15,(char *)0x6ac578,0,0);
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
        } while (fcn_005373e0(0x5c18e0,0x677c7));
        if (v27) {
          fcn_00471e30(v9);
          goto label_5c221e;
        }
      }
    }
  }
  fcn_00471e30(v28);
  v3 = 0;
  if ((*(int *)0x6b5cc0)) {
    v61 = 0x3dcccccd;
    v60 = 0x7e3a40;
    v59 = 0x14ce880;
    v58 = 0x532f13;
    v61 = (*(int *)0x6b8014);
    if (fcn_00451840()) { 
      v60 = 0x532f25;
      fcn_00433780();
      v60 = 0x7e3a40;
      v59 = (*(int *)0x6b8014);
      (*(int *)0x6b5cc0) = 0;
      (*(int *)0x6b5cbc) = 0;
      v3 = 1;
      v58 = 0x532f47;
      fcn_00438b40();
      v58 = 0x7e3a50;
      v57 = (*(int *)0x6b8014);
      v56 = 0x532f58;
      fcn_00438cb0();
    }
    else {
      v60 = 0x532f62;
      fcn_00433780();
      (*(int *)0x6b5cc0) = 0;
      (*(int *)0x6b5cbc) = 0;
    }
  }
  if (((*(int *)0x774650) <= (*(int *)0x774658)) || (v3)) {
    v61 = 0x3dcccccd;
    v59 = (*(int *)0x6b8014) + 0x84;
    v60 = 0x7e3a50;
    v58 = 0x533015;
    if (fcn_00451840()) {
      v61 = 0x3dcccccd;
      v59 = (*(int *)0x6b8014) + 0x4c;
      v60 = 0x7e3a40;
      v58 = 0x533034;
      if (fcn_00451840()) goto label_533077;
    }
    if (!v3) {
      v61 = 0x533044;
      fcn_0052d820();
      if ((*(int *)0x7746a8)) {
        v12 = *(int *)((*(int *)0x7746a8) + 0x1d4);
        if ((v12) && (*(int *)(v12 + 0x18c))) {
          v60 = v12 + 400;
          v61 = 0;
          v59 = 3;
          v58 = (*(int *)0x7746a8);
          v57 = 0x53306e;
          (*(int (__cdecl **)())(v12 + 0x18c))();
        }
        (*(int *)0x7746a8) = 0;
      }
    }
  }
  else if ((*(int *)0x774650) - (*(int *)0x774654) <= (*(int *)0x77465c)) {
    v61 = 0x532f9f;
    fcn_0052d820();
    (*(int *)0x77465c) = (*(int *)0x774650) - (*(int *)0x774654);
    if ((*(int *)0x7746a8)) {
      v12 = *(int *)((*(int *)0x7746a8) + 0x1d4);
      if ((v12) && (*(int *)(v12 + 0x18c))) {
        v60 = v12 + 400;
        v61 = 0;
        v59 = 3;
        v58 = (*(int *)0x7746a8);
        v57 = 0x532fdd;
        (*(int (__cdecl **)())(v12 + 0x18c))();
      }
      (*(int *)0x7746a8) = 0;
    }
    if (!(*(int *)0x7e2a9c))
      return;
    v61 = 0x532ff7;
    fcn_00530510();
  }
label_533077:
  if (!(*(int *)0x7e2a9c))
    return;
  (*(int *)0x7e2a9c) = 0;
  (*(int *)0x7e2aa0) = 0;
  (*(int *)0x7ea3bc) = 0;
  (*(int *)0x7746c0) = 0;
  v12 = (*(int *)0x7746c8);
  if ((*(int *)0x7746c4)) { 
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
    v62 = 0x44;
    v61 = 0;
    v60 = 1;
    v59 = 0x530547;
    v12 = fcn_00503fe0();
  }
  if (!v12)
    return;
label_530554:
  (*(int *)0x7746f4) = 0;
  v60 = *(unsigned int *)(v12 + 0x5d);
  v62 = 5;
  v61 = 1;
  v59 = 0x530567;
  v7 = (unsigned short *)fcn_00502cd0();
  if (!v7)
    return;
  do {
    if (*(char *)((*(int *)0x99ec10) + (unsigned int)*v7 * 0x41) == '\x1d')
      *(unsigned int *)&v7[0x10] = *(unsigned int *)&v7[0x10] & 0xfffffffd;
    v61 = 0x530590;
    v7 = (unsigned short *)fcn_00502850();
  } while (v7);
  return;
}
