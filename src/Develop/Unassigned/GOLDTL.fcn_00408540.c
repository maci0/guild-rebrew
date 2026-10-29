/* Reconstructed from native disassembly; frame slots follow the decompiler map. */

#include <math.h>

int __cdecl fcn_00402610();
int __cdecl fcn_00405960();
int __cdecl fcn_00405a50();
int __cdecl fcn_00407760();
int __cdecl fcn_00407e30();
int __cdecl fcn_00408250();
int __cdecl fcn_00408270();
int __cdecl fcn_004082d0();
int __cdecl fcn_00408320();
int __cdecl fcn_00413190();
int __cdecl fcn_0041db70();
int __cdecl fcn_0041ddd0();
int __cdecl fcn_00421350();
int __cdecl fcn_0045b920();
int __cdecl fcn_0045b990();
int __cdecl fcn_0064d228();

/* ADDRESS: GOLDTL 0x00408540 */
int __cdecl fcn_00408540(int a0,int a1,int *a2)
{
  float *v1;
  int v10;
  unsigned int *v11;
  char *v12;
  unsigned int v13;
  int *v14; 
  unsigned int v15; 
  unsigned int v16; 
  unsigned int v17; 
  unsigned int v18; 
  unsigned int v19; 
  int v2;
  unsigned int v20 [95];
  char v21 [4];
  unsigned int v22; 
  int *v23; 
  int *v24; 
  char v25 [2049];
  unsigned int v26; 
  int v27;
  int v28;
  unsigned int *v29;
  unsigned int *v3;
  int v30; 
  float v31;
  float v32; 
  float v33; 
  unsigned int v34; 
  unsigned int v35; 
  int v36; 
  int v37; 
  char v4; 
  short v5; 
  int v6;
  unsigned char *v7;
  unsigned int v8;
  char *v9;
  v27 = a0;
  v13 = 0;
  v28 = *(int *)(a0 + 0x128);
  v6 = fcn_00413190(*(unsigned int *)(a0 + 0x88));
  if (*(char *)(v28 + 9) != '-')
    return -1;
  v37 = v6;
  v35 = fcn_00402610(v27);
  fcn_00408250((*(int *)0x6b5c5c),v35);
  v36 = fcn_0064d228();
  if (0xb <= v36)
    v36 = 10;
  v10 = *(int *)(v28 + 0xf8);
  if (*(int *)((*(int *)0x67a370) + 0xac + v6 * 0x3dc)) 
    *(unsigned int *)((*(int *)0x6b5c5c) + 0x10) = 0x42700000;
  else {
    *(unsigned int *)((*(int *)0x6b5c5c) + 0x10) = 0x42700000;
  }
  v9 = (char *)(*(int *)(v28 + 0xf4) + v10 * 2);
  fcn_004082d0(v35,*v9,v9[1],(*(int *)0x6b5c5c),&v15,&v14);
  v28 = (*(int *)0x6b5c5c);
  if (*(int **)(v27 + 0x124))
    fcn_00408270((*(int *)0x6b5c5c),**(int **)(v27 + 0x124) + 0x4c,&v17,&v16);
  fcn_00408270(v28,*(int *)(v27 + 0x34) + 0x4c,&v19,&v18);
  v26 = 0;
  if (a1 <= 0)
    return 0;
  v24 = a2;
label_40869c:
  if (!(v13 & 1)) {
    v10 = 0;
    v7 = (unsigned char *)(v27 + 0x94);
    v28 = *v24;
    v6 = *(int *)(v28 + 0x128);
    do {
      if ((*(int *)&v7[-4] == v28) && (*v7 & 1)) break;
      v10 += 1;
      v7 = &v7[8];
    } while (v10 < 0x10);
    fcn_00408320(v35,v28,v20);
    v28 = 0;
    v11 = v20;
    do {
      v8 = v11[2];
      if (!v8) break;
      if (v8 & 2) { 
        if (*v11 == v15) {
          v30 = (int *)v11[1] == v14;
label_408759:
          if (v30) goto label_408905;
        }
      }
      else {
        if (v8 & 1) {
          v8 = *v11;
          if ((v8 != v19) || (v11[1] != v18)) {
            if ((v8 != v15) || ((int *)v11[1] != v14)) {
              if (((!v6) || (*(char *)(v6 + 9) != '-')) || (*(int *)(v6 + 0x154) != -1)) goto label_40874a;
              goto label_40875f;
            }
            if (((v6) && (*(char *)(v6 + 9) == '-')) && (*(int *)(v6 + 0x154) == -1)) {
              v28 = 0x90;
              goto label_408870;
            }
          }
label_4088fe:
          v13 = 5;
          break;
        }
        if (v8 & 8) {
          v8 = *v11;
          if ((v8 != v15) || ((int *)v11[1] != v14)) {
label_40874a:
            if (v8 == v17) {
              v30 = v11[1] == v16;
              goto label_408759;
            }
          }
          else {
            if (((!v6) || (*(char *)(v6 + 9) != '-')) || (*(int *)(v6 + 0x154) != -1)) goto label_4088fe;
            v10 = 0x90;
            do {
              if (!*(int *)(v10 + v27)) break;
              if ((*(int *)(*v24 + v10) == v27) && (*(unsigned char *)(*v24 + 4 + v10) & 2)) {
                v13 = 1;
                goto label_40875f;
              }
              v10 += 8;
            } while (v10 < 0x110);
            v10 = *(int *)(v27 + 0x34);
            v2 = **(int **)(*v24 + 0x124);
            v31 = *(float *)(v10 + 0x4c) - *(float *)(v2 + 0x4c);
            v32 = *(float *)(v10 + 0x50) - *(float *)(v2 + 0x50);
            v33 = *(float *)(v10 + 0x54) - *(float *)(v2 + 0x54);
            v31 = sqrtf(v31 * v31 + v32 * v32 + v33 * v33) * (*(int *)0x662910) * (*(int *)0x6628cc);
            *(float *)(v27 + 0x1a4) = v31;
            if ((*(int *)0x6628a0) < v31)
              v31 = (*(int *)0x6628a0);
            *(float *)(v27 + 0x1a4) = v31;
            v13 = 2;
          }
        }
      }
label_40875f:
      v28 += 1;
      v11 = &v11[3];
    } while (v28 < 0x20);
    goto label_40890a;
  }
  goto label_40892d;
  while( 1 ) {
    if ((*(int *)(*v24 + v28) == v27) && (*(unsigned char *)(*v24 + 4 + v28) & 2)) goto label_408905;
    v28 += 8;
    if (0x110 <= v28) break;
label_408870:
    if (!*(int *)(v28 + v27)) break;
  }
  v28 = *(int *)(v27 + 0x34);
  v6 = *(int *)(*v24 + 0x34);
  v31 = *(float *)(v28 + 0x4c) - *(float *)(v6 + 0x4c);
  v32 = *(float *)(v28 + 0x50) - *(float *)(v6 + 0x50);
  v33 = *(float *)(v28 + 0x54) - *(float *)(v6 + 0x54);
  v31 = sqrtf(v31 * v31 + v32 * v32 + v33 * v33) * (*(int *)0x662910) * (*(int *)0x6628cc);
  *(float *)(v27 + 0x1a4) = v31;
  if ((*(int *)0x6628a0) < v31)
    v31 = (*(int *)0x6628a0);
  *(float *)(v27 + 0x1a4) = v31;
  v13 = 2;
label_40890a:
  v26 += 1;
  v24 = &v24[1];
  if (a1 <= (int)v26) goto label_40892d;
  goto label_40869c;
label_408905:
  v13 = 1;
  goto label_40890a;
label_40892d:
  if (!v13)
    return 0;
  v28 = 0;
  v6 = 0x20;
  v29 = (unsigned int *)(v27 + 0x90);
  while (v6) {
    v3 = &v29[1];
    *v29 = 0;
    v6 -= 1;
    v29 = v3;
  }
  v11 = (unsigned int *)(v27 + 0x94);
  do {
    v8 = a2[v28];
    *v11 = v13;
    v11[-1] = v8;
    v28 += 1;
    v11 = &v11[2];
  } while (v28 < a1);
  if (!(v13 & 1))
    return 0;
  if (*(float *)(v27 + 0x1a4) < (float)(*(int *)0x662908))
    *(unsigned int *)(v27 + 0x1a4) = 0x3f000000;
  v26 = 0;
  do {
    v28 = *(int *)(a2[v26] + 0x128);
    if (((v28) && (*(char *)(v28 + 9) == '-')) && ((*(int *)(v28 + 0xf4) && (*(int *)(v28 + 0x154) == -1)))) {
      v27 = v36;
      if (4 <= v36)
        v27 = 3;
      if (*(int *)(a2[v26] + 0x124)) 
        v6 = *(int *)(v28 + 0xf8) + -2;
      else {
        v6 = *(int *)(v28 + 0xf8);
      }
      if (v6 <= 0)
        v6 = 1;
      v10 = v6 + 2;
      for (; (v6 < v10 && (v6 < *(int *)(v28 + 0xf0))); v6 = v6 + 1) {
        v23 = (int *)(unsigned int)*(unsigned char *)(*(int *)(v28 + 0xf4) + v6 * 2);
        v22 = (unsigned int)*(unsigned char *)(*(int *)(v28 + 0xf4) + 1 + v6 * 2);
        v34 = (v6 != *(int *)(v28 + 0xf0) + -1) ? 1 : 0xd; 
        fcn_00405a50(v23,v22,v37,v34,v27);
      }
    }
    v26 += 1;
  } while ((int)v26 < a1);
  v28 = 0;
  do {
    v13 = v35;
    v27 = a2[v28];
    v6 = *(int *)(v27 + 0x128);
    if ((((v6) && (*(char *)(v6 + 9) == '-')) && (*(int *)(v6 + 0xf4))) && (*(int *)(v6 + 0x154) == -1)) {
      v4 = fcn_0045b990(v35,*(int *)(v27 + 0x34) + 0x4c,&v23,&v22,v21);
      if (v4)
        fcn_00405a50(v23,v22,v37,0,v36);
      if ((*(int **)(a2[v28] + 0x124)) && (v4 = fcn_0045b990(v35,**(int **)(a2[v28] + 0x124) + 0x4c,&v23,&v22,v21), v4)) {
        v34 = 0;
        v27 = v36;
        fcn_00405a50(v23,v22,v37,v34,v27 * 2); 
      }
    }
    else {
      v4 = fcn_0045b990(v35,*(int *)(v27 + 0x34) + 0x4c,&v23,&v22,v21);
      v27 = v36;
      if (v4) {
        v10 = 9;
        if (v36 <= 9)
          v10 = v36;
        if ((v6) && (*(int *)(v6 + 0x154) != -1))
          v34 = 0;
        else {
          v34 = 0xd;
        }
        fcn_00405a50(v23,v22,v37,v34,v10);
      }
      if ((*(int **)(a2[v28] + 0x124)) && (v6 = **(int **)(a2[v28] + 0x124), fcn_0045b990(v13,v6 + 0x4c,&v23,&v22,v21))) {
        v34 = 0xd;
        fcn_00405a50(v23,v22,v37,v34,v27 * 2);
      }
    }
    v28 += 1;
    if (a1 <= v28) {
      v28 = *(int *)(a0 + 0x128);
      v4 = fcn_0045b990(v35,*(int *)(*(int *)(v28 + 0x14) + 0x34) + 0x4c,&v24,&v15,v21);
      if (!v4)
        return 0;
      v6 = *(int *)(v28 + 0xf8) + 0x10;
      v27 = *(int *)(v28 + 0xf0) + -1;
      if (v6 < v27)
        v27 = v6;
      v6 = v27 + 1;
      v10 = 0;
      if (v6 < *(int *)(v28 + 0xf0)) {
        v12 = v25;
        v9 = (char *)(*(int *)(v28 + 0xf4) + v6 * 2);
        do {
          v12 = &v12[2];
          v10 += 1;
          v12[-1] = *v9;
          *v12 = v9[1];
          v9 = &v9[2];
          v6 += 1;
        } while (v6 < *(int *)(v28 + 0xf0));
      }
      v23 = (int *)(unsigned int)*(unsigned char *)(*(int *)(v28 + 0xf4) + v27 * 2);
      v22 = (unsigned int)*(unsigned char *)(*(int *)(v28 + 0xf4) + 1 + v27 * 2);
      if ((*(int *)(a0 + 0x88) == 0x10432c0) || (v27 = 2, (*(int *)0x6b8300)))
        v27 = 5;
      v4 = fcn_00407e30(v35,*(int *)(a0 + 0x34) + 0x4c,v28 + 0x144,v23,v22,&v14,&v26,v36 * v27,*(unsigned int *)(v28 + 0x160) | 1);
      v13 = v35;
      if (!v4) {
        fcn_00405960(v35);
        return -1;
      }
      v23 = v14;
      v22 = v26;
      (*(int *)0x14d0c28) = 0x14cfc20;
      (*(int *)0x14d0c24) = 0x200;
      if (*(int *)(*(int *)(v35 + 0x24) + (int)(*(int *)(v35 + 0x20) * v15 + (int)v24) * 0x1c) != 0xd) { 
        v8 = v15;
        v14 = v24;
      }
      else {
        if ((*(int *)(a0 + 0x88) == 0x10432c0) || (v27 = 2, (*(int *)0x6b8300)))
          v27 = 5;
        v4 = fcn_00407e30(v35,*(int *)(a0 + 0x34) + 0x4c,v28 + 0x144,v24,v15,&v14,&v26,v36 * v27,*(unsigned int *)(v28 + 0x160) | 1);
        if (v4) { 
          v24 = v14;
          v15 = v26;
          v8 = v26;
        }
        else {
          v8 = v15;
          v14 = v24;
        }
      }
      v5 = fcn_00421350(0x14d0c20,v13,v14,v8,v23,v22,*(char *)(a0 + 0x240));
      v27 = (*(int *)0x14d0c20);
      if (v5 == -1) {
        fcn_00405960(v13);
        return -1;
      }
      if (*(int *)(v28 + 0xf4)) {
        fcn_0041ddd0(*(int *)(v28 + 0xf4));
        *(unsigned int *)(v28 + 0xf4) = 0;
      }
      v34 = fcn_0041db70((v27 + v10) * 2,(char *)0x675ac8);
      *(unsigned int *)(v28 + 0xf4) = v34;
      v16 = fcn_00407760(a0,0x14d0c20,v34,v13);
      v27 = 0;
      if (1 <= v10) {
        v6 = v16 * 2;
        do {
          v2 = v27 * 2;
          v27 += 1;
          *(char *)(v6 + *(int *)(v28 + 0xf4)) = v25[v2 + 1];
          *(char *)(*(int *)(v28 + 0xf4) + 1 + v6) = v25[v27 * 2];
          v6 += 2;
        } while (v27 < v10);
      }
      *(unsigned int *)(v28 + 0xf0) = v16 + v10;
      *(unsigned int *)(v28 + 0xf8) = 0;
      *(unsigned int *)(v28 + 0xfc) = 0xffffffff;
      v23 = (int *)(unsigned int)*(unsigned char *)(*(int *)(v28 + 0xf4) + -2 + (v16 + v10) * 2);
      v1 = (float *)(v28 + 0x124);
      v22 = (unsigned int)*(unsigned char *)(*(int *)(v28 + 0xf4) + -1 + *(int *)(v28 + 0xf0) * 2);
      v18 = v13;
      fcn_0045b920(v13,v23,v22,v1);
      v27 = *(int *)(v28 + 0xf0);
      *v1 = (*(int *)0x6b5c38) + *v1;
      *(float *)(v28 + 0x128) = (*(int *)0x6b5c3c) + *(float *)(v28 + 0x128);
      *(float *)(v28 + 300) = (*(int *)0x6b5c40) + *(float *)(v28 + 300);
      if (((2 <= v27) && (v6 = *(int *)(v28 + 0xf4), *(char *)(v6 + -2 + v27 * 2) == *(char *)(v6 + -4 + v27 * 2))) && (*(char *)(v6 + -1 + v27 * 2) == *(char *)(v6 + -3 + v27 * 2)))
        *(int *)(v28 + 0xf0) = v27 + -1;
      fcn_00405960(v13);
      *(char *)(a0 + 0x8e) = 4;
      if ((v24 == v23) && (v15 == v22))
        return -2;
      return v16;
    }
  } while( 1 );
}
