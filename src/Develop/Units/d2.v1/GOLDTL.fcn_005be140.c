/* Reconstructed from native disassembly; stack slots bound to the native frame offsets. */

#include <math.h>

int __cdecl fcn_0046f9b0();
int __cdecl fcn_00470820();
int __cdecl fcn_00471b60();
int __cdecl fcn_00471e30();
int __cdecl fcn_00472170();
int __cdecl fcn_00472640();
int __cdecl d2_SetForm();
int __cdecl fcn_00473a90();
int __cdecl fcn_004c4450();
int __cdecl fcn_004c5150();
int __cdecl fcn_004c5530();
int __cdecl fcn_00502cd0();
int __cdecl fcn_00509570();
int __cdecl fcn_0050b810();
int __cdecl fcn_00519190();
int __cdecl fcn_0051af00();
int __cdecl fcn_00525fb0();
int __cdecl fcn_00526010();
int __cdecl fcn_00526120();
int __cdecl fcn_00532ef0();
int __cdecl fcn_00533a60();
int __cdecl fcn_00533dc0();
int __cdecl fcn_00535960();
int __cdecl fcn_005373e0();
int __cdecl he_fn_Handlung();
int __cdecl fcn_005463a0();
int __cdecl fcn_0057e880();
int __cdecl fcn_0057ecc0();
int __cdecl fcn_00594340();
int __cdecl fcn_00595e20();
int __cdecl fcn_005963f0();
int __cdecl fcn_005974e0();
int __cdecl fcn_00597940();
int __cdecl fcn_005bdfc0();

#define v23 (*(int *)(frame + 0x1c))
#define v28 (*(int *)(frame + 0x0))
#define v29 (*(int *)(frame + 0x8))
#define v30 (*(int *)(frame + 0x20))
#define v31 (*(char *)(frame + 0x40))
#define v32 (*(unsigned int *)(frame + 0x44))
#define v33 (*(unsigned int *)(frame + 0x48))
#define v34 (*(unsigned int *)(frame + 0x64))
#define v35 (*(unsigned int *)(frame + 0x68))
#define v36 (*(unsigned int *)(frame + 0x6c))
#define v37 (*(unsigned short *)(frame + 0x70))
#define v38 (*(char *)(frame + 0x72))
#define v39 (*(unsigned int *)(frame + 0x94))
#define v40 (*(unsigned int *)(frame + 0x98))
#define v41 (*(unsigned int *)(frame + 0x9c))
#define v42 (*(char *)(frame + 0x138))
#define v43 (*(unsigned int *)(frame + 0x13c))
#define v44 (*(unsigned int *)(frame + 0x140))
#define v45 (*(unsigned int *)(frame + 0x15c))
#define v46 (*(unsigned int *)(frame + 0x160))
#define v47 (*(unsigned int *)(frame + 0x164))
#define v48 (*(unsigned short *)(frame + 0x168))
#define v49 (*(char *)(frame + 0x16a))
#define v50 (*(unsigned int *)(frame + 0x18c))
#define v51 (*(unsigned int *)(frame + 0x190))
#define v52 (*(unsigned int *)(frame + 0x194))
#define v53 (*(char *)(frame + 0x230))
#define v54 (*(unsigned int *)(frame + 0x234))
#define v55 (*(unsigned int *)(frame + 0x238))
#define v56 (*(unsigned int *)(frame + 0x254))
#define v57 (*(unsigned int *)(frame + 0x258))
#define v58 (*(unsigned int *)(frame + 0x25c))
#define v59 (*(unsigned short *)(frame + 0x260))
#define v60 (*(char *)(frame + 0x262))
#define v61 (*(unsigned int *)(frame + 0x284))
#define v62 (*(unsigned int *)(frame + 0x288))

/* ADDRESS: GOLDTL 0x005be140 */
void __cdecl fcn_005be140(unsigned char *a0,int a1)
{
	unsigned int *  v1;
	int v10;
	unsigned int v11;
	int v12;
	int v13;
	unsigned int *  v14;
	unsigned int v15;
	unsigned int v16;
	unsigned int v17;
	int v18;
	unsigned int v19;
	unsigned char *  v2;
	unsigned int v20;
	unsigned int v21;
	unsigned int v22;
	int v24;
	int v25;
	char v26[1024];
	int v27;
	int v3;
	short *  v4;
	unsigned int v5;
	int v6;
	int v7;
	unsigned int v8;
	int v9;
	unsigned char frame[0x724];
  v2 = a0;
  v3 = fcn_00525fb0(a0);
  if (v3)
    return;
  v18 = (*(int *)0x868050) + (unsigned int)*v2 * 0x24d;
  v3 = a1;
  if (!a1) {
    v3 = fcn_00502cd0(*(unsigned int *)&v2[0x5d],1,4,2);
    if (v3) // branch-flip
      v3 = *(int *)(v3 + 0x14);
    else {
      v3 = *(int *)&v2[0x5d];
    }
  }
  v4 = (short *)fcn_00502cd0(v3,2,0,0x2a,6);
  if (((!v4) && (v4 = (short *)fcn_00502cd0(v3,2,0,0x116,6), !v4)) && (v4 = (short *)fcn_00502cd0(*(unsigned int *)&v2[0x5d],2,0,0x2a,6), !v4))
    return;
  fcn_0057e880(0x1d,v2,0,0);
  v5 = fcn_00470820(0,0,(char *)0x6ac468);
  fcn_00471b60(v5);
  d2_SetForm(v5,3);
  fcn_00519190(0xfa);
  d2_SetForm(v5,0);
  fcn_00533dc0((*(int *)0x772514),0x70b,0x740);
  d2_SetForm(v5,4);
  fcn_00533a60((*(int *)0x772514),0,&v23,2,(*(int *)0x14a570c),(*(int *)0x14a5710));
  v29 = v23;
  v28 = v30;
  if ((*(int *)0x7747b0) <= '\xff')
    fcn_00472640(v30,0);
  fcn_00594340();
  fcn_00473a90(0,0);
  do {
    v3 = fcn_005463a0(2,0,0x12,3,*(unsigned int *)&v2[1]);
    while ((v3 && (!*(int *)(v3 + 0xb0)))) {
      v3 = he_fn_Handlung();
    }
    v6 = fcn_005463a0(2,0,0x12,3,*(unsigned int *)&v2[1]);
    while ((v6 && (!*(int *)(v6 + 0xb4)))) {
      v6 = he_fn_Handlung();
    }
    v7 = fcn_005463a0(2,0,0x13,3,*(unsigned int *)&v2[1]);
    d2_SetForm(v5,2);
    if (*v4 != 0x116) { // branch-flip
      fcn_00519190(0xfe,(char)v4[0xe],*(char *)(v18 + 0x240));
      fcn_00519190(0xff,8000);
      if (v3) // branch-flip
        fcn_00519190(0x100,*(unsigned int *)(v3 + 0xb0));
      else {
        fcn_00519190(0x101);
      }
      fcn_00519190(0x102,*(char *)((int)v4 + 0x1d),*(char *)(v18 + 0x241));
      fcn_00519190(0xff,8000);
      if (v6) // branch-flip
        fcn_00519190(0x100,*(unsigned int *)(v6 + 0xb4));
      else {
        v11 = 0x101;
label_5be43c:
        fcn_00519190(v11);
      }
    }
    else {
      fcn_00519190(0x104,(char)v4[0xe],*(char *)(v18 + 0x242));
      fcn_00519190(0x105,8000);
      if (!v3) {
        v11 = 0x107;
        goto label_5be43c;
      }
      fcn_00519190(0x106,*(unsigned int *)(v3 + 0xb0));
    }
    fcn_00519190(0x103,*(int *)&v4[7] + 0x107,0x3200);
    if ((*(int *)0x100f1dc) != -1) {
      if ((*(int *)0x67d370) != v29) { // branch-flip
        if ((((*(int *)0x67d370) == v28) && ('\0' <= (*(int *)0x7747b0))) && (v11 = CONCAT31((unsigned int)((unsigned int)(*(int *)0x67d370) >> 8),(*(int *)0x773d75)),
             v15 = (unsigned int)(*(int *)0x774970), fcn_00526010(v15 * 0x21c + 0x7f4ca0,0x3200,v11))) {
          fcn_0051af00(v26,0x113,0x3200);
          fcn_00526120(v26,0x101);
          if (v13) {
            v11 = fcn_004c5150(0xffffffff,*(unsigned int *)((unsigned int)(*(int *)0x774970) * 0x21c + 0x7f4ca4),CONCAT31((unsigned int)((unsigned int)v22 >> 8),(*(int *)0x773d75)),0x3200);
            v12 = fcn_004c4450(v11);
            while (!v12) {
              fcn_00535960();
              v12 = fcn_004c4450(v11);
            }
            if (fcn_004c4450(v11) == 1) {
              v12 = fcn_00509570((unsigned int)(*(int *)0x774970) * 0x21c + 0x7f4ca0);
              if (v12)
                *(int *)(v12 + 0x50) = *(int *)(v12 + 0x50) + 0x3200;
              if (!v7) {
                v12 = 0x3e;
                v14 = &v27;
                while (v12) {
                  v1 = &v14[1];
                  *v14 = 0;
                  v12 -= 1;
                  v14 = v1;
                }
                v53 = 0x13;
                v60 = 1;
                v62 = 1;
                v55 = *(unsigned int *)&v2[1];
                v54 = *(unsigned int *)((unsigned int)*(unsigned short *)&v2[0x27] * 0x21c + 0x7f4ca4);
                v56 = (*(int *)0x7f4c00);
                v57 = (*(int *)0x7f4c04);
                v61 = *(unsigned int *)&v4[1];
                v58 = (*(int *)0x7f4c08);
                v59 = (*(int *)0x7f4c0c);
                v14 = &v27;
                goto label_5be96f;
              }
              *(int *)(v7 + 0xb0) = *(int *)(v7 + 0xb0) + 1;
            }
          }
        }
      }
      else {
        v15 = (unsigned int)*(unsigned char *)&v4[0xe];
        if (v3)
          v15 += *(int *)(v3 + 0xb0);
        v8 = (unsigned int)*(unsigned char *)((int)v4 + 0x1d);
        if (v6)
          v8 += *(int *)(v6 + 0xb4);
        fcn_005bdfc0(v4,v2,v15,v8);
        fcn_0050b810(*(unsigned int *)((unsigned int)(*(int *)0x774970) * 0x21c + 0x7f4e18),CONCAT31((unsigned int)((unsigned int)v19 >> 8),(*(int *)0x773d75)));
        if (v9 != 1) { // branch-flip
          if ((v9 == 2) && (v11 = CONCAT31((unsigned int)((unsigned int)v16 >> 8),(*(int *)0x773d75)), v15 = (unsigned int)(*(int *)0x774970), fcn_00526010(v15 * 0x21c + 0x7f4ca0,8000,v11))) {
            v11 = fcn_004c5150(0xffffffff,*(unsigned int *)((unsigned int)(*(int *)0x774970) * 0x21c + 0x7f4ca4),CONCAT31((unsigned int)((unsigned int)v17 >> 8),(*(int *)0x773d75)),8000);
            v12 = fcn_004c4450(v11);
            while (!v12) {
              fcn_00535960();
              v12 = fcn_004c4450(v11);
            }
            if (fcn_004c4450(v11) == 1) {
              v12 = fcn_00509570((unsigned int)(*(int *)0x774970) * 0x21c + 0x7f4ca0);
              if (v12)
                *(int *)(v12 + 0x50) = *(int *)(v12 + 0x50) + 8000;
              if (!v6) {
                v11 = *(unsigned int *)&v2[1];
                v12 = 0x3e;
                v14 = &v25;
                while (v12) {
                  v1 = &v14[1];
                  *v14 = 0;
                  v12 -= 1;
                  v14 = v1;
                }
                v42 = 0x12;
                v47 = (*(int *)0x7f4c08);
                v14 = &v25;
                v49 = 1;
                v51 = 0;
                v52 = 1;
                v43 = *(unsigned int *)((unsigned int)*(unsigned short *)&v2[0x27] * 0x21c + 0x7f4ca4);
                v45 = (*(int *)0x7f4c00);
                v46 = (*(int *)0x7f4c04);
                v50 = *(unsigned int *)&v4[1];
                v48 = (*(int *)0x7f4c0c);
                v44 = v11;
                goto label_5be970;
              }
              *(int *)(v6 + 0xb4) = *(int *)(v6 + 0xb4) + 1;
            }
          }
        }
        else {
          fcn_00526010((unsigned int)(*(int *)0x774970) * 0x21c + 0x7f4ca0,8000,CONCAT31((unsigned int)((unsigned int)v20 >> 8),(*(int *)0x773d75)));
          if (v10) {
            v11 = fcn_004c5150(0xffffffff,*(unsigned int *)((unsigned int)(*(int *)0x774970) * 0x21c + 0x7f4ca4),CONCAT31((unsigned int)((unsigned int)v21 >> 8),(*(int *)0x773d75)),8000);
            v12 = fcn_004c4450(v11);
            while (!v12) {
              fcn_00535960();
              v12 = fcn_004c4450(v11);
            }
            if (fcn_004c4450(v11) == 1) {
              v12 = fcn_00509570((unsigned int)(*(int *)0x774970) * 0x21c + 0x7f4ca0);
              if (v12)
                *(int *)(v12 + 0x50) = *(int *)(v12 + 0x50) + 8000;
              if (v3) // branch-flip
                *(int *)(v3 + 0xb0) = *(int *)(v3 + 0xb0) + 1;
              else {
                v12 = 0x3e;
                v14 = &v24;
                while (v12) {
                  v1 = &v14[1];
                  *v14 = 0;
                  v12 -= 1;
                  v14 = v1;
                }
                v31 = 0x12;
                v38 = 1;
                v40 = 1;
                v41 = 0;
                v33 = *(unsigned int *)&v2[1];
                v32 = *(unsigned int *)((unsigned int)*(unsigned short *)&v2[0x27] * 0x21c + 0x7f4ca4);
                v34 = (*(int *)0x7f4c00);
                v35 = (*(int *)0x7f4c04);
                v39 = *(unsigned int *)&v4[1];
                v36 = (*(int *)0x7f4c08);
                v37 = (*(int *)0x7f4c0c);
                v14 = &v24;
label_5be96f:
label_5be970:
                fcn_004c5530(v14);
              }
            }
          }
        }
      }
    }
    if (*v4 != 0x116) { // branch-flip
      v8 = (unsigned int)*(unsigned char *)(v18 + 0x240);
      if (v3)
        v8 -= *(int *)(v3 + 0xb0);
      v15 = (unsigned int)*(unsigned char *)(v18 + 0x241);
      if (v6)
        v15 -= *(int *)(v6 + 0xb4);
      if (((int)v8 <= (int)(unsigned int)*(unsigned char *)&v4[0xe]) && ((int)v15 <= (int)(unsigned int)*(unsigned char *)((int)v4 + 0x1d))) {
label_5bea02:
        if (v29 != -1) {
          *(unsigned int *)(v29 * 0x2f4 + 0x60 + (*(int *)0x1015ea0)) = 1;
          *(unsigned int *)(v29 * 0x2f4 + 0x4c + (*(int *)0x1015ea0)) = 1;
        }
      }
    }
    else {
      v15 = 0;
      v8 = (unsigned int)*(unsigned char *)(v18 + 0x242);
      if (v3)
        v8 -= *(int *)(v3 + 0xb0);
      if ((int)v8 <= (int)(unsigned int)*(unsigned char *)&v4[0xe]) goto label_5bea02;
    }
    if ((3 <= *(int *)&v4[7]) || (v7)) {
      if (v28 != -1) {
        *(unsigned int *)(v28 * 0x2f4 + 0x60 + (*(int *)0x1015ea0)) = 1;
        *(unsigned int *)(v28 * 0x2f4 + 0x4c + (*(int *)0x1015ea0)) = 1;
        if (!v7) goto label_5bea6c;
        v11 = (*(int *)0x14a5714);
        fcn_0046f9b0(v28,v11); // crossjump-dupe
      }
    }
    else if (v28 != -1) {
      *(unsigned int *)(v28 * 0x2f4 + 0x60 + (*(int *)0x1015ea0)) = 0;
      *(unsigned int *)(v28 * 0x2f4 + 0x4c + (*(int *)0x1015ea0)) = 0;
label_5bea6c:
      v11 = (*(int *)0x14a5710);
      fcn_0046f9b0(v28,v11);
    }
    if (((3 <= *(int *)&v4[7]) && ((int)v8 <= (int)(unsigned int)*(unsigned char *)&v4[0xe])) && ((int)v15 <= (int)(unsigned int)*(unsigned char *)((int)v4 + 0x1d))) {
      if (v28 != -1)
        fcn_00472170(v28,0);
      d2_SetForm(v5,4);
      fcn_00519190(0x112);
      v28 = -1;
      v29 = -1;
    }
    if (*v4 != 0x116) { // branch-flip
      fcn_00595e20(v2,v4);
      fcn_005963f0(v5,1,0,v2);
    }
    else {
      fcn_005974e0();
      fcn_00597940(v5,1,1,v2,v4);
    }
    if (((*(int *)0x14ce8e0)) && (fcn_0057ecc0() == 1))
      (*(int *)0x774654) = 1;
    if (!fcn_005373e0(0x5be140,0x657c7)) {
      fcn_00532ef0();
      fcn_00471e30(v5);
      fcn_0057e880(0x1d,v2,1,0);
      return;
    }
  } while( 1 );
}
