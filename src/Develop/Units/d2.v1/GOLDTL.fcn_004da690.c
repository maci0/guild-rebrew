/* Council election/removal session cutscene controller. Coordinates the six
 * Sitzung scenes, the ABSETZUNG/AMTSWAHL script resources, chamber votes and
 * the result scenes. Slot layout follows the native frame (0x900). */

#include <stddef.h>

extern int g_1015ea0;
extern int g_772500;
extern int g_772514;
extern int g_774970;
extern void __cdecl fcn_004e4de0(int);

int __cdecl fcn_00420780();
int __cdecl fcn_00420840();
int __cdecl fcn_0046f2c0();
int __cdecl fcn_00470820();
int __cdecl fcn_00471af0();
int __cdecl fcn_00471d80();
int __cdecl fcn_00471e30();
int __cdecl d2_SetForm();
int __cdecl fcn_004c4450();
int __cdecl fcn_004c54c0();
int __cdecl fcn_004da4d0();
int __cdecl fcn_004da510();
int __cdecl fcn_004e44b0();
int __cdecl fcn_004e44f0();
int __cdecl fcn_004e45c0();
int __cdecl fcn_004e4730();
int __cdecl fcn_004e48b0();
int __cdecl fcn_004e4910();
int __cdecl fcn_004e4ae0();
int __cdecl fcn_004e4b00();
int __cdecl fcn_004e4b40();
int __cdecl fcn_004e4e90();
int __cdecl fcn_004e3640();
int __cdecl fcn_004e51d0();
int __cdecl fcn_004e6cb0();
int __cdecl fcn_004e8240();
int __cdecl fcn_004e8b80();
int __cdecl fcn_004e9180();
int __cdecl fcn_004e99e0();
int __cdecl fcn_004ea130();
int __cdecl fcn_004ea2b0();
int __cdecl fcn_004ea350();
int __cdecl fcn_004fda30();
int __cdecl gm_LookupEntityRecordById();
int __cdecl io_AppendText();
int __cdecl io_FormatTextBuffer();
int __cdecl fcn_005358e0();
int __cdecl fcn_00535960();
int __cdecl fcn_0057e880();
int __cdecl fcn_005ca560();
int __cdecl fcn_005ca740();
int __cdecl fcn_64d41a();

/* ADDRESS: GOLDTL 0x004da690 */
void __cdecl fcn_004da690(unsigned int *a0)
{
  char *v1;
  unsigned int v10; 
  unsigned int v100; 
  unsigned short v101; 
  char v102; 
  unsigned int v103; 
  unsigned short v104; 
  char v105; 
  char v106 [4]; 
  char v107 [4]; 
  char v108 [4]; 
  char v109 [4]; 
  unsigned int v11; 
  char v110 [2]; 
  char v111; 
  char v112 [4]; 
  char v113 [4]; 
  char v114 [4]; 
  char v115 [4]; 
  char v116 [4]; 
  char v117 [4]; 
  char v118 [4]; 
  char v119 [4]; 
  int v12; 
  char v120 [2]; 
  char v121 [4]; 
  char v122 [4]; 
  char v123 [4]; 
  char v124 [4]; 
  char v125 [2]; 
  char v126 [4]; 
  char v127 [4]; 
  char v128 [4]; 
  char v129 [4]; 
  int v13;
  char v130 [2]; 
  unsigned int v131; 
  unsigned int v132; 
  unsigned int *v14;
  unsigned int v15; 
  char *v16;
  unsigned int v17; 
  unsigned int v18; 
  unsigned short *v19;
  char *v2;
  unsigned short *v20; 
  unsigned short *v21; 
  unsigned int v22; 
  int v23;
  int v24;
  int *v25;
  unsigned int *v26;
  int v27; 
  unsigned int v28; 
  int v29;
  unsigned int *v3;
  unsigned int *v30; 
  unsigned int *v31; 
  char v32 [21];
  int v33;
  unsigned int v34 [7];
  unsigned int v35 [8];
  unsigned int v36 [7];
  unsigned int v37 [7];
  unsigned int v38 [7];
  unsigned int v39 [7];
  int *v4;
  unsigned int v40 [6];
  int v41;
  char v42 [25];
  char v43 [25];
  char v44 [25];
  unsigned int v45 [69];
  int v46 [8];
  char v47 [4];
  int v48 [12]; 
  int v49;
  unsigned short **v5;
  int v50 [6];
  char v51 [128];
  char v52 [256];
  unsigned short *v53 [5]; 
  int v54;
  unsigned int v55; 
  int v56 [83];
  int v57 [7]; 
  int v58;
  char v59 [256];
  unsigned short v6;
  unsigned char v60 [4];
  int v61;
  unsigned short *v62 [4]; 
  int v63 [4];
  int v64 [55]; 
  unsigned int v65; 
  int v66;
  int v67;
  unsigned int *v68;
  char *v69;
  unsigned short v7;
  unsigned int *v70;
  unsigned int *v71; 
  unsigned short **v72;
  unsigned int v73; 
  unsigned char *v74; 
  int v75; 
  unsigned int *v76; 
  int v77; 
  int *v78; 
  int *v79; 
  int v8;
  int v80; 
  int v81; 
  int v82; 
  int v83; 
  int v84; 
  unsigned char v85; 
  unsigned int v86; 
  char v87; 
  unsigned int v88; 
  unsigned int v89; 
  int v9;
  unsigned int v90; 
  unsigned int v91; 
  unsigned int v92; 
  unsigned short v93; 
  unsigned int v94; 
  unsigned int v95; 
  char v96; 
  unsigned int v97; 
  unsigned short v98; 
  char v99; 
  v14 = a0;
  v24 = 5;
  v16 = (char *)0x68c328;
  v69 = v32;
  while (v24) {
    v2 = &v69[4];
    v1 = &v16[4];
    *(unsigned int *)v69 = *(unsigned int *)v16;
    v24 -= 1;
    v16 = v1;
    v69 = v2;
  }
  *v69 = *v16;
  v24 = 6;
  v26 = &v33;
  while (v24) {
    v70 = &v26[1];
    *v26 = 0;
    v24 -= 1;
    v26 = v70;
  }
  *(unsigned short *)v26 = 0;
  *(char *)((int)v26 + 2) = 0;
  v107[0] = *(int *)(0x68c314 + 4);
  v106[0] = *(int *)(0x68c314 + 0);
  v108[0] = *(int *)(0x68c314 + 8);
  v109[0] = *(int *)(0x68c314 + 0xc);
  v110[0] = *(short *)(0x68c314 + 0x10);
  v111 = *(char *)(0x68c314 + 0x12);
  v24 = 7;
  v26 = v34;
  while (v24) {
    v70 = &v26[1];
    *v26 = 0;
    v24 -= 1;
    v26 = v70;
  }
  v48[0] = 6;
  *(char *)v26 = 0;
  v113[0] = *(int *)(0x68c304 + 4);
  v112[0] = *(int *)(0x68c304 + 0);
  v115[0] = *(int *)(0x68c304 + 0xc);
  v114[0] = *(int *)(0x68c304 + 8);
  v24 = 8;
  v26 = v35;
  while (v24) {
    v70 = &v26[1];
    *v26 = 0;
    v24 -= 1;
    v26 = v70;
  }
  v116[0] = *(int *)(0x68c2f0 + 0);
  v117[0] = *(int *)(0x68c2f0 + 4);
  v118[0] = *(int *)(0x68c2f0 + 8);
  v119[0] = *(int *)(0x68c2f0 + 0xc);
  v120[0] = *(short *)(0x68c2f0 + 0x10);
  v24 = 7;
  v26 = v36;
  while (v24) {
    v70 = &v26[1];
    *v26 = 0;
    v24 -= 1;
    v26 = v70;
  }
  *(unsigned short *)v26 = 0;
  v122[0] = *(int *)(0x68c2dc + 4);
  v121[0] = *(int *)(0x68c2dc + 0);
  v125[0] = *(short *)(0x68c2dc + 0x10);
  v124[0] = *(int *)(0x68c2dc + 0xc);
  v123[0] = *(int *)(0x68c2dc + 8);
  v24 = 7;
  v26 = v37;
  while (v24) {
    v70 = &v26[1];
    *v26 = 0;
    v24 -= 1;
    v26 = v70;
  }
  v48[1] = 5;
  v48[2] = 4;
  v48[3] = 3;
  v48[4] = 2;
  v48[5] = 1;
  *(unsigned short *)v26 = 0;
  v127[0] = *(int *)(0x68c2c8 + 4);
  v126[0] = *(int *)(0x68c2c8 + 0);
  v128[0] = *(int *)(0x68c2c8 + 8);
  v130[0] = *(short *)(0x68c2c8 + 0x10);
  v129[0] = *(int *)(0x68c2c8 + 0xc);
  v24 = 7;
  v26 = v38;
  while (v24) {
    v70 = &v26[1];
    *v26 = 0;
    v24 -= 1;
    v26 = v70;
  }
  *(unsigned short *)v26 = 0;
  v66 = 0;
  v24 = 7;
  v16 = (char *)0x68c2ac;
  v26 = v39;
  while (v24) {
    v70 = &v26[1];
    v69 = &v16[4];
    *v26 = *(unsigned int *)v16;
    v24 -= 1;
    v16 = v69;
    v26 = v70;
  }
  v91 = 0;
  v24 = 6;
  v16 = (char *)0x68c290;
  v26 = v40;
  while (v24) {
    v70 = &v26[1];
    v69 = &v16[4];
    *v26 = *(unsigned int *)v16;
    v24 -= 1;
    v16 = v69;
    v26 = v70;
  }
  *(unsigned short *)v26 = *(unsigned short *)v16;
  v92 = 0;
  v93 = 0;
  v24 = 5;
  v16 = (char *)0x68c278;
  v26 = &v41;
  while (v24) {
    v70 = &v26[1];
    v69 = &v16[4];
    *v26 = *(unsigned int *)v16;
    v24 -= 1;
    v16 = v69;
    v26 = v70;
  }
  *(unsigned short *)v26 = *(unsigned short *)v16;
  *(char *)((int)v26 + 2) = v16[2];
  v94 = 0;
  v95 = 0;
  v96 = 0;
  v24 = 6;
  v16 = (char *)0x68c25c;
  v69 = v42;
  while (v24) {
    v2 = &v69[4];
    v1 = &v16[4];
    *(unsigned int *)v69 = *(unsigned int *)v16;
    v24 -= 1;
    v16 = v1;
    v69 = v2;
  }
  *v69 = *v16;
  v97 = 0;
  v98 = 0;
  v99 = 0;
  v24 = 6;
  v16 = (char *)0x68c240;
  v69 = v43;
  while (v24) {
    v2 = &v69[4];
    v1 = &v16[4];
    *(unsigned int *)v69 = *(unsigned int *)v16;
    v24 -= 1;
    v16 = v1;
    v69 = v2;
  }
  *v69 = *v16;
  v100 = 0;
  v101 = 0;
  v102 = 0;
  v24 = 6;
  v16 = (char *)0x68c224;
  v69 = v44;
  while (v24) {
    v2 = &v69[4];
    v1 = &v16[4];
    *(unsigned int *)v69 = *(unsigned int *)v16;
    v24 -= 1;
    v16 = v1;
    v69 = v2;
  }
  *v69 = *v16;
  v103 = 0;
  v104 = 0;
  v24 = 0x45;
  v26 = a0;
  v70 = v45;
  while (v24) {
    v3 = &v70[1];
    v68 = &v26[1];
    *v70 = *v26;
    v24 -= 1;
    v26 = v68;
    v70 = v3;
  }
  v105 = 0;
  v82 = 0;
  v10 = fcn_004e4ae0((char *)0x68c214,0);
  v11 = fcn_004e4ae0((char *)0x68c204,0);
  fcn_004e4e90(0);
  v24 = 0;
  v84 = 0;
  if (*(char *)&v14[0xc]) {
    v26 = &v14[0xd];
    do {
      v12 = gm_LookupEntityRecordById(*v26);
      if (v12) {
        v46[v66] = v12;
        v66 += 1;
      }
      v24 += 1;
      v26 = &v26[1];
    } while (v24 < (int)(unsigned int)*(unsigned char *)&v14[0xc]);
    v84 = v66;
  }
  if (v66 <= 7) {
    v24 = 8 - v66;
    v25 = &v46[v66];
    while (v24) {
      v4 = &v25[1];
      *v25 = 0;
      v24 -= 1;
      v25 = v4;
    }
  }
  v81 = 0;
  do {
    v24 = v48[v81];
    v12 = fcn_004e8b80(v24,6,v47);
    v67 = 0;
    v66 = 0;
    v77 = 0;
    if (1 <= v12) {
      v14 = &v49;
      do {
        v13 = gm_LookupEntityRecordById(*v14);
        if ((v13) && (!*(char *)(v13 + 0x1b1))) {
          v48[v66 + 6] = v67;
          v50[v66] = v13;
          v66 += 1;
        }
        v67 += 1;
        v14 = &v14[6];
      } while (v67 < v12);
      v77 = v66;
    }
    fcn_005358e0(0x6b5c60);
    if (fcn_004ea130(v24)) { 
      if (v12 <= 5) {
        v67 = 6 - v12;
        v25 = &v50[v12];
        while (v67) {
          v4 = &v25[1];
          *v25 = 0;
          v67 -= 1;
          v25 = v4;
        }
      }
      v67 = 0;
      if (1 <= v66) {
        v14 = (unsigned int *)0x9b0ebc;
        v26 = &a0[0xd];
        do {
          v13 = v50[v67];
          v67 += 1;
          v68 = &v26[1];
          v70 = &v14[0xd7];
          *v26 = *(unsigned int *)(v13 + 4);
          v14[-0x23] = *(unsigned int *)(v13 + 4);
          *v14 = 0;
          v14[-0x26] = 0;
          v14[-0x25] = 1;
          v14 = v70;
          v26 = v68;
        } while (v67 < v66);
      }
      v13 = 0;
      v67 = v66;
      if (1 <= v84) {
        v14 = (unsigned int *)(v66 * 0x35c + 0x9b0e24);
        v76 = &a0[v66 + 0xd];
        do {
          v29 = 0;
          if (1 <= v66) {
            v25 = (int *)0x9b0e30;
            do {
              if (*v25 == *(int *)(v46[v13] + 4)) goto label_4dabf6;
              v29 += 1;
              v25 = &v25[0xd7];
            } while (v29 < v66);
          }
          v29 = v46[v13];
          v26 = &v76[1];
          v67 += 1;
          *v76 = *(unsigned int *)(v29 + 4);
          v14[3] = *(unsigned int *)(v29 + 4);
          *v14 = 0;
          v14[1] = 1;
          v14[0x26] = 1;
          v14 = &v14[0xd7];
          v76 = v26;
label_4dabf6:
          v13 += 1;
        } while (v13 < v84);
      }
      *(char *)&a0[0xc] = (char)v67;
      if (v67 <= 0xf) {
        v26 = &a0[v67 + 0xd];
        v14 = (unsigned int *)(v67 * 0x35c + 0x9b0e30);
        do {
          *v26 = 0xffffffff;
          *v14 = 0xffffffff;
          v14 = &v14[0xd7];
          v26 = &v26[1];
        } while ((int)v14 < 0x9b43f0);
      }
      fcn_005358e0(0x6b5c60);
      v15 = fcn_00470820(0,0,(char *)0x68c1ec);
      fcn_00471af0(v15,0);
      fcn_00471d80(v15,3);
      v67 = 0;
      v80 = 0;
      if (1 <= v12) {
        v16 = v51;
        v13 = v12;
        do {
          if (*v16 == '\x02')
            v67 += 1;
          v16 = &v16[0x18];
          v13 -= 1;
        } while (v13);
        v80 = v67;
      }
      v9 = 0;
      if (v67) {
        fcn_004e4730(&v32[v81 * 0x30]);
        if (!v82)
          v82 = fcn_00420780((char *)0x68c1d0,0x40);
        v67 = 0;
        if (1 <= v66) {
          do {
            v13 = fcn_004fda30(*(unsigned short *)v50[v67]);
            if (v13) 
              fcn_64d41a(v52,(char *)0x68c1c8,v48[v67 + 6],v13 + 4);
            else {
              fcn_64d41a(v52,(char *)0x68c1b0,v48[v67 + 6]);
            }
            fcn_004e44b0((char *)0x68c184,v52);
            v67 += 1;
          } while (v67 < v66);
        }
        v67 = 0;
        if (1 <= v66) {
          do {
            fcn_64d41a(v52,0x67d444,v48[v67 + 6]);
            fcn_004e44b0((char *)0x68c158,v52);
            v67 += 1;
          } while (v67 < v66);
        }
        io_FormatTextBuffer(v52,(char *)0x68c140,&v39[v81 * 8]);
        fcn_004e44f0(fcn_004e44b0(v52,0x6b5c60));
        v9 = 1;
        fcn_005358e0(0x6b5c60);
      }
      v83 = 0;
      if (1 <= v12) {
        v74 = (unsigned int *)&v49;
        do {
          if (!v80) break;
          v57[0] = 0;
          v57[1] = 0;
          v57[2] = 0;
          if (fcn_004ea2b0(v24,(unsigned int *)((int)v74 + -4))) {
            v67 = 0;
            v13 = 0;
            if (1 <= v66) {
              do {
                if (*(char *)(v50[v67] + 0x166))
                  v13 += 1;
                v67 += 1;
              } while (v67 < v66);
            }
            v17 = fcn_00470820(0,0,(char *)0x68c124);
            fcn_00471d80(v17,3);
            v18 = fcn_00470820(0,0,(char *)0x68c104);
            fcn_00471d80(v18,3);
            v80 -= 1;
            v19 = (unsigned short *)gm_LookupEntityRecordById(*(unsigned int *)v74);
            v20 = (unsigned short *)gm_LookupEntityRecordById(*(unsigned int *)((int)v74 + 0x10));
            d2_SetForm(v18,1);
            v131 = 0;
            v132 = 0;
            v53[0] = v19;
            fcn_005ca560(v53);
            fcn_005ca740(0x28,0,g_772514,0x54,v53,1);
            d2_SetForm(v18,2);
            fcn_004da510(g_772514,1,0);
            fcn_004e4b40(0xfffffff8,v10,(char *)0x68c0f0,v24 + -1,0x32);
            fcn_00471af0(v15,1);
            d2_SetForm(v15,0);
            io_AppendText(0x6811b0);
            io_AppendText(0x12c4);
            io_AppendText(0x12c5,v24 + 0x12a9,v24 + 0x12bb,*v20,*v19);
            fcn_004e4de0(0x9c4);
            d2_SetForm(v17,0);
            fcn_0046f2c0(g_772514,1);
            if (1 <= v13) {
              v67 = 0;
              v29 = 0;
              v66 = (800U - *(short *)(g_772500 + 0x1ebd8) * v13) / (v13 + 1);
              if (1 <= v77) {
                v25 = &v54;
                v13 = v66;
                do {
                  if (*(char *)(v50[v67] + 0x166)) {
                    *v25 = v50[v67];
                    v25[5] = 0;
                    v25[0xc] = 0;
                    fcn_005ca560(v25);
                    fcn_005ca740(*(short *)(g_772500 + 0x1ebd8) * v29 + v13,0,g_772514,0x54,v25,0);
                    v29 += 1;
                    v13 += v66;
                  }
                  v67 += 1;
                  v25 = &v25[0xe];
                } while (v67 < v77);
              }
            }
            fcn_004e4de0(0x9c4);
            v87 = *(char *)((int)v74 + -4);
            v89 = *(unsigned int *)v74;
            v88 = (unsigned int)*(unsigned char *)((int)v74 + 4);
            v90 = *(unsigned int *)((int)v74 + 0x10);
            v55 = 1;
            fcn_00471af0(v15,0);
            fcn_004e51d0(a0,&v55);
            fcn_004e4de0(1000);
            fcn_00471af0(v15,1);
            if (1 <= v77) { 
              v25 = v56;
              v71 = (unsigned int *)0x9b0eb4;
              v76 = (unsigned int *)v77;
              do {
                if (*v71 <= 2) {
                  v21 = (unsigned short *)gm_LookupEntityRecordById(v71[-0x21]);
                  v57[*v71] = v57[*v71] + 1;
                  d2_SetForm(v15,0);
                  *(unsigned int *)(g_1015ea0 + 0x3c + *v25 * 0x2f4) = 1;
                  io_AppendText(0x6811b0);
                  io_AppendText(0x12c7,*v21);
                  fcn_004e4de0(1000);
                  d2_SetForm(v15,0);
                  if (*v71) { 
                    if (*v71 == 1) {
                      v22 = fcn_004e6cb0(4,100);
                      fcn_004e4b40(*v21,v10,(char *)0x68c0d0,v22);
                      io_AppendText(0x12ca);
                      if (v71[1] != 1) { 
                        if (v71[1] == 2) {
                          v6 = *v19;
                          io_AppendText(fcn_004e6cb0(2,v6) + 0x12d1);
                        }
                        d2_SetForm(v18,2);
                        v22 = 1;
                      }
                      else {
                        v6 = *v20;
                        v7 = *v19;
                        io_AppendText(fcn_004e6cb0(2,v7,v6) + 0x12cd);
                        d2_SetForm(v18,2);
                        v22 = 1;
                      }
                      goto label_4db1e1;
                    }
                    v22 = fcn_004e6cb0(4,100);
                    fcn_004e4b40(*v21,v10,(char *)0x68c0b8,v22);
                    io_AppendText(0x12c9);
                    d2_SetForm(v18,2);
                    fcn_004da510(g_772514,0,2);
                  }
                  else {
                    v22 = fcn_004e6cb0(4,100);
                    fcn_004e4b40(*v21,v10,(char *)0x68c0e0,v22);
                    io_AppendText(0x12c8);
                    if (v71[1] != 1) { 
                      if (v71[1] == 2) {
                        v6 = *v20;
                        v66 = fcn_004e6cb0(2,v6) + 0x12cf;
                        io_AppendText(v66);
                      }
                    }
                    else {
                      v6 = *v20;
                      v66 = fcn_004e6cb0(2,v6) + 0x12cb;
                      io_AppendText(v66);
                    }
                    d2_SetForm(v18,2);
                    v22 = 0;
label_4db1e1:
                    fcn_004da510(g_772514,0,v22);
                  }
                  fcn_004e4de0(4000);
                  *(unsigned int *)(g_1015ea0 + 0x3c + *v25 * 0x2f4) = 0;
                  fcn_004e4de0(1000);
                }
                v71 = &v71[0xd7];
                v25 = &v25[0xe];
                v76 = (int)((int)v76 + -1);
              } while (v76);
              if (v57[0] <= v57[1]) goto label_4db44e;
              fcn_004e4b40(0xfffffff8,v10,(char *)0x68c098,fcn_004e6cb0(3,100));
              d2_SetForm(v15,0);
              io_AppendText(0x6811b0);
              io_AppendText(0x12d6,v57[0],v57[1],*v19);
              fcn_004e4de0(4000);
              if (a0[3] == *(int *)((unsigned int)g_774970 * 0x21c + 0x7f4ca4)) {
                v25 = (int *)0x9b0e30;
                v14 = a0;
                v66 = v77;
                do {
                  if (*v25 != *(int *)&v19[2]) {
                    if (v25[0x21]) { 
                      v22 = (v25[0x21] != 1) ? 0xffffffec : 10; 
                    }
                    else {
                      v22 = 0xffffffd8;
                    }
                    fcn_004c54c0(*v25,*(int *)&v19[2],v22,1);
                    v14 = v30;
                  }
                  v25 = &v25[0xd7];
                  v66 -= 1;
                } while (v66);
                v22 = fcn_004e8240(*(char *)((int)v74 + -4),0,0,3,0xff);
                v66 = fcn_004c4450(v22);
                while (!v66) {
                  fcn_00535960();
                  v66 = fcn_004c4450(v22);
                }
              }
            }
            else {
label_4db44e:
              v67 = gm_LookupEntityRecordById(*(unsigned int *)v74);
              fcn_004e4b40(0xfffffff8,v10,(char *)0x68c074,fcn_004e6cb0(3,100));
              d2_SetForm(v15,0);
              io_AppendText(0x6811b0);
              io_AppendText(0x12d7,v57[0],v57[1],*v19,*v19);
              fcn_004e4de0(4000);
              v66 = (unsigned int)g_774970 * 0x87;
              if (a0[3] == *(int *)((unsigned int)g_774970 * 0x21c + 0x7f4ca4)) {
                v14 = a0;
                if (1 <= v77) {
                  v25 = (int *)0x9b0e30;
                  v76 = (unsigned int *)v77;
                  do {
                    v66 = *(int *)&v19[2];
                    if (*v25 != v66) {
                      if (v25[0x21]) { 
                        v22 = (v25[0x21] != 1) ? 5 : 10; 
                      }
                      else {
                        v22 = 0xffffffd8;
                      }
                      fcn_004c54c0(*v25,v66,v22,1);
                      v66 = v27;
                      v14 = v31;
                    }
                    v25 = &v25[0xd7];
                    v76 = (int)((int)v76 + -1);
                  } while (v76);
                }
                if (v67) { 
                  v22 = *(char *)((int)v74 + -4);
                  v73 = 1;
                }
                else {
                  v22 = *(char *)((int)v74 + -4);
                  v73 = 4;
                  v67 = 0;
                }
                v22 = fcn_004e8240(v22,v67,0,v73,0xff);
                v66 = fcn_004c4450(v22);
                while (!v66) {
                  fcn_00535960();
                  v66 = fcn_004c4450(v22);
                }
              }
            }
            d2_SetForm(v15,0);
            fcn_00471af0(v15,0);
            io_AppendText(0x6811b0);
            fcn_00471e30(v18);
            fcn_00471e30(v17);
            fcn_004e4de0(1000);
            fcn_005358e0(0x6b5c60);
            v66 = v77;
          }
          v83 += 1;
          v74 = (unsigned int *)((int)v74 + 0x18);
        } while (v83 < v12);
      }
      v67 = 0;
      v80 = 0;
      if (1 <= v12) {
        v25 = &v58;
        v13 = v12;
        do {
          if (((char)v25[1] == '\x03') && (*v25))
            v67 += 1;
          v25 = &v25[6];
          v13 -= 1;
        } while (v13);
        v80 = v67;
        if ((v67) && (!v9)) {
          fcn_004e4730(&v32[v81 * 0x30]);
          if (!v82)
            v82 = fcn_00420780((char *)0x68c1d0,0x40);
          v13 = 0;
          if (1 <= v66) {
            do {
              v29 = fcn_004fda30(*(unsigned short *)v50[v13]);
              if (v29) 
                fcn_64d41a(v59,(char *)0x68c1c8,v48[v13 + 6],v29 + 4);
              else {
                fcn_64d41a(v59,(char *)0x68c1b0,v48[v13 + 6]);
              }
              fcn_004e44b0((char *)0x68c184,v59);
              v13 += 1;
            } while (v13 < v66);
          }
          v13 = 0;
          if (1 <= v66) {
            do {
              fcn_64d41a(v59,0x67d444,v48[v13 + 6]);
              fcn_004e44b0((char *)0x68c158,v59);
              v13 += 1;
            } while (v13 < v66);
          }
          io_FormatTextBuffer(v59,(char *)0x68c140,&v39[v81 * 8]);
          fcn_004e44f0(fcn_004e44b0(v59,0x6b5c60));
          v9 = 1;
          fcn_005358e0(0x6b5c60);
        }
      }
      v83 = 0;
      if (1 <= v12) {
        v74 = v60;
        while (v67) {
          v57[3] = 0;
          v57[4] = 0;
          v57[5] = 0;
          v57[6] = 0;
          if ((v74[8] == 3) && (*(int *)&v74[4])) {
            v80 -= 1;
            v86 = (unsigned int)*v74;
            v85 = v74[-8];
            v66 = 0;
            v65 = 2;
            v78 = NULL;
            if (1 <= v77) {
              v78 = NULL;
              do {
                v67 = v50[v66];
                v13 = fcn_004e9180(v67,v86);
                if ((v13) && (!*(char *)(v67 + 0x1b1)))
                  v78 = (int)((int)v78 + 1);
                v66 += 1;
              } while (v66 < v77);
            }
            v17 = fcn_00470820(0,0,(char *)0x68c124);
            fcn_00471d80(v17,3);
            v18 = fcn_00470820(0,0,(char *)0x68c058);
            fcn_00471d80(v18,2);
            d2_SetForm(v18,0);
            v25 = &v61;
            v19 = (unsigned short *)0x7f4ca0;
            v66 = 0;
            do {
              v67 = v66;
              if ((*(int *)&v74[4] <= v66) || (4 <= v66)) break;
              if (*(unsigned char *)&v19[0xb4] == *v74) {
                v67 = v66 + 1;
                v62[v66] = v19;
                d2_SetForm(v18,v67);
                *v25 = (int)v19;
                v25[5] = 0;
                v25[0xb] = 0;
                v25[0xc] = 0;
                fcn_005ca560(v25);
                fcn_005ca740((0xa0U - (int)*(short *)(g_772500 + 0x1ebd8)) / 2,0,g_772514,0x54,v25,1);
                v63[v66] = *(int *)&v19[2];
                v25 = &v25[0xe];
              }
              v19 = &v19[0x10e];
              v66 = v67;
            } while ((int)v19 < 0x85a0a0);
            if (v67) {
              if (v67 <= 3) {
                v28 = 4U - v67 & 0x3fffffff;
                v25 = &v63[v67];
                while (v28) {
                  v4 = &v25[1];
                  *v25 = -1;
                  v28 -= 1;
                  v25 = v4;
                }
                v28 = 4U - v67 & 0x3fffffff;
                v72 = &v62[v67];
                while (v28) {
                  v5 = &v72[1];
                  *v72 = NULL;
                  v28 -= 1;
                  v72 = v5;
                }
              }
              fcn_004e4b40(0xfffffff8,v11,(char *)0x68c050,v24 + -1,100);
              fcn_004e4b40(0xfffffff8,v11,(char *)0x68c044,v67 + -1,500);
              fcn_00471af0(v15,1);
              d2_SetForm(v15,0);
              io_AppendText(0x6811b0);
              io_AppendText(0x12d8);
              io_AppendText(0x12d9,v24 + 0x12a9,v24 + 0x12bb,*v74 + 0x253);
              v66 = 0;
              if (1 <= v67) {
                do {
                  io_AppendText(0x12db,*v62[v66],*v62[v66]);
                  v66 += 1;
                } while (v66 < v67);
              }
              fcn_004e4de0(0x9c4);
              d2_SetForm(v17,0);
              fcn_0046f2c0(g_772514,1);
              if (1 <= (int)v78) {
                v13 = 0;
                v66 = (800U - (int)*(short *)(g_772500 + 0x1ebd8) * (int)v78) / ((int)v78 + 1);
                v75 = 0;
                if (1 <= v77) {
                  v25 = &v54;
                  v29 = v66;
                  do {
                    v23 = fcn_004e9180(v50[v75],v86);
                    if (v23) {
                      *v25 = v50[v75];
                      v25[5] = 0;
                      v25[0xc] = 0;
                      fcn_005ca560(v25);
                      fcn_005ca740(*(short *)(g_772500 + 0x1ebd8) * v13 + v29,0,g_772514,0x54,v25,0);
                      v13 += 1;
                      v29 += v66;
                    }
                    v75 += 1;
                    v25 = &v25[0xe];
                  } while (v75 < v77);
                }
              }
              fcn_004e4de0(0x9c4);
              if (v67 != 1) { 
                if (v78) { 
                  fcn_00471af0(v15,0);
                  fcn_004e51d0(a0,&v65);
                  fcn_004e4de0(1000);
                  fcn_00471af0(v15,1);
                  v75 = 0;
                  if (1 <= v77) {
                    v78 = v56;
                    v79 = (int *)0x9b0eb4;
                    do {
                      if ((*v79 != -1) && (v66 = 0, 1 <= v67)) {
                        do {
                          if (v63[v66] == *v79) {
                            *(unsigned int *)(g_1015ea0 + 0x3c + *v78 * 0x2f4) = 1;
                            d2_SetForm(v15,0);
                            io_AppendText(0x6811b0);
                            io_AppendText(0x12de,*(unsigned short *)v50[v75]);
                            v57[v66 + 3] = v57[v66 + 3] + 1;
                            fcn_004e4de0(1000);
                            *(unsigned int *)(g_1015ea0 + 0x3c + v64[v66 * 0xe] * 0x2f4) = 1;
                            d2_SetForm(v18,v66 + 1);
                            fcn_004da4d0(v66 + 1,&v64[v66 * 0xe + -1]);
                            d2_SetForm(v15,0);
                            io_AppendText(0x12df,*v62[v66]);
                            fcn_004e4de0(4000);
                            *(unsigned int *)(g_1015ea0 + 0x3c + *v78 * 0x2f4) = 0;
                            *(unsigned int *)(g_1015ea0 + 0x3c + v64[v66 * 0xe] * 0x2f4) = 0;
                            break;
                          }
                          v66 += 1;
                        } while (v66 < v67);
                      }
                      v75 += 1;
                      v79 = &v79[0xd7];
                      v78 = &v78[0xe];
                    } while (v75 < v77);
                  }
                  v8 = 0;
                  v29 = 0;
                  v13 = -1;
                  v66 = -1;
                  if (1 <= v67) {
                    do {
                      v23 = v57[v29 + 3];
                      if (v23 <= v13) { 
                        if (v23 == v13)
                          v8 = 1;
                      }
                      else {
                        v8 = 0;
                        v66 = v29;
                        v13 = v23;
                      }
                      v29 += 1;
                    } while (v29 < v67);
                    if (v8) {
                      if (v66 != -1) {
                        v23 = fcn_004e6cb0(v67);
                        v29 = v67;
                        do {
                          if (v57[v23 + 3] == v13) {
                            v66 = v23;
                            break;
                          }
                          v29 -= 1;
                          v23 = (v23 + 1) % v67;
                        } while (v29);
                        fcn_004e4b40(0xfffffff8,v11,(char *)0x68c038,2,100);
                        d2_SetForm(v15,0);
                        io_AppendText(0x6811b0);
                        io_AppendText(0x12e3);
                        fcn_004e4de0(1000);
                        v19 = v62[v66];
                        *(unsigned int *)(g_1015ea0 + 0x3c + v64[v66 * 0xe] * 0x2f4) = 1;
                        io_AppendText(0x12e4,*v19);
                        fcn_004e4de0(4000);
                        if (a0[3] == *(int *)((unsigned int)g_774970 * 0x21c + 0x7f4ca4)) {
                          v22 = fcn_004e8240(v74[-8],v19,0,1,0xff);
                          v66 = fcn_004c4450(v22);
                          while (!v66) {
                            fcn_00535960();
                            v66 = fcn_004c4450(v22);
                          }
                        }
                      }
                    }
                    else if (v66 != -1) {
                      *(unsigned int *)(g_1015ea0 + 0x3c + v64[v66 * 0xe] * 0x2f4) = 1;
                      fcn_004e4b40(0xfffffff8,v11,(char *)0x68c038,3,100);
                      d2_SetForm(v15,0);
                      io_AppendText(0x6811b0);
                      v19 = v62[v66];
                      io_AppendText(0x12e5,*v74 + 0x253,*v19);
                      fcn_004e4de0(4000);
                      v66 = *(int *)((unsigned int)g_774970 * 0x21c + 0x7f4ca4);
                      if (a0[3] == v66) {
                        v22 = fcn_004e8240(v74[-8],v19,0,1,0xff);
                        v66 = fcn_004c4450(v22);
                        while (!v66) {
                          fcn_00535960();
                          v66 = fcn_004c4450(v22);
                        }
                      }
                    }
                  }
                }
                else {
                  v66 = fcn_004e6cb0(v67);
                  fcn_004e4b40(0xfffffff8,v11,(char *)0x68c038,1,100);
                  d2_SetForm(v15,0);
                  io_AppendText(0x6811b0);
                  io_AppendText(0x12e1);
                  fcn_004e4de0(1000);
                  v19 = v62[v66];
                  *(unsigned int *)(g_1015ea0 + 0x3c + v64[v66 * 0xe] * 0x2f4) = 1;
                  io_AppendText(0x12e2,*v19);
                  fcn_004e4de0(4000);
                  if (a0[3] == *(int *)((unsigned int)g_774970 * 0x21c + 0x7f4ca4)) {
                    v22 = fcn_004e8240(v74[-8],v19,0,1,0xff);
                    v66 = fcn_004c4450(v22);
                    while (!v66) {
                      fcn_00535960();
                      v66 = fcn_004c4450(v22);
                    }
                  }
                }
              }
              else {
                fcn_004e4b40(0xfffffff8,v11,(char *)0x68c038,0,100);
                *(unsigned int *)(g_1015ea0 + 0x3c + v64[0] * 0x2f4) = 1;
                d2_SetForm(v15,0);
                io_AppendText(0x6811b0);
                v19 = v62[0];
                io_AppendText(0x12e0,*v62[0],*v74 + 0x253);
                fcn_004e4de0(4000);
                if (a0[3] == *(int *)((unsigned int)g_774970 * 0x21c + 0x7f4ca4)) {
                  v22 = fcn_004e8240(v74[-8],v19,0,1,0xff);
                  v66 = fcn_004c4450(v22);
                  while (!v66) {
                    fcn_00535960();
                    v66 = fcn_004c4450(v22);
                  }
                }
              }
              d2_SetForm(v15,0);
              io_AppendText(0x6811b0);
              fcn_00471af0(v15,0);
              fcn_00471e30(v18);
              fcn_00471e30(v17);
              fcn_004e4de0(1000);
              fcn_005358e0(0x6b5c60);
            }
          }
          v83 += 1;
          v74 = &v74[0x18];
          if (v12 <= v83) break;
          v67 = v80;
        }
      }
      if (v9) {
        fcn_004e48b0();
        fcn_004e4de0(1000);
        fcn_004e45c0(fcn_004e44b0((char *)0x68c010,0x6b5c60));
        fcn_004e4910();
      }
      fcn_00471e30(v15);
    }
    else if (a0[3] == *(int *)((unsigned int)g_774970 * 0x21c + 0x7f4ca4))
      fcn_004e99e0(v24,v12,v47);
    v81 += 1;
    if (6 <= v81) {
      if (a0[3] == *(int *)((unsigned int)g_774970 * 0x21c + 0x7f4ca4))
        fcn_004ea350();
      fcn_004e4b00(v10);
      fcn_004e4b00(v11);
      if (v82)
        fcn_00420840(v82);
      fcn_004e3640();
      v24 = 0x45;
      v14 = v45;
      v26 = a0;
      while (v24) {
        v68 = &v26[1];
        v70 = &v14[1];
        *v26 = *v14;
        v24 -= 1;
        v14 = v70;
        v26 = v68;
      }
      fcn_0057e880(0x30,0,0,0);
      return;
    }
  } while (1);
}
