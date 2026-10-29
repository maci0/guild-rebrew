/*
 * Network game browser: poll the advertised sessions, build one list row per
 * compatible host (name, map, players, ping) and drive the modal dialog.
 */

extern int g_100f1dc;           /* 0x0100f1dc */
extern char* g_1015ea0;         /* 0x01015ea0 */
extern int g_14ac5e4;           /* 0x014ac5e4 */
extern int g_14ac614;           /* 0x014ac614 */
extern int g_14ac618;           /* 0x014ac618 */
extern int g_14ac61c;           /* 0x014ac61c */
extern int g_14ce8e0;           /* 0x014ce8e0 */
extern char g_14cf950;          /* 0x014cf950 */
extern int g_67d370;            /* 0x0067d370 */
extern int g_6b7fac;            /* 0x006b7fac */
extern int g_6b7fdc;            /* 0x006b7fdc */
extern int g_772514;            /* 0x00772514 */
extern int g_7725c8;            /* 0x007725c8 */
extern int g_774654;            /* 0x00774654 */
extern unsigned char g_7747b0;  /* 0x007747b0 */
extern int g_9badc0;            /* 0x009badc0 */
extern int g_9badc4;            /* 0x009badc4 */
extern int g_9badc8;            /* 0x009badc8 */
extern int g_9badcc;            /* 0x009badcc */

extern char s_6a1e4c[]; /* "Network" */
extern char s_6a2e24[]; /* "_STADTWAPPEN_BERLIN" */
extern char s_6a2e38[]; /* "_STADTWAPPEN_%s" */
extern char s_6a3a4c[]; /* "Host" */
extern char s_6a3a54[]; /* "Gamedata\\network\\%s.SAV" */
extern char s_6a3a6c[]; /* "Menu\\SEARCH_NETWORK" */

int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471db0(int, int);
void __cdecl fcn_00471d80(int, int);
void __cdecl d2_SetForm(int, int);
int __cdecl fcn_005340f0(int);
int __cdecl fcn_00519190(int, ...);
int __cdecl fcn_00533a60(int, int, int*, int, int, int, int);
int __cdecl fcn_00472640(int, int);
int __cdecl fcn_005373e0(int, int);
int __cdecl fcn_005268c0(int, int);
int __cdecl fcn_00402370(int, int, char*, int);
int __cdecl fcn_00471e30(int);
int __cdecl fcn_0046f2c0(int, int);
int __cdecl fcn_00469510(int);
int* __cdecl d2_CreateRadioGroup(int);
int __cdecl vfs_Tfopen(char*, int, int);
int __cdecl fcn_00521eb0(int, char*);
int __cdecl CloseVfsStream(int);
int __cdecl __strupr(char*);
int __cdecl sprintf(char*, const char*, ...);
int __cdecl fcn_00465950(char*);
int __cdecl fcn_0046f740(int, int, int, int);
int __cdecl fcn_00469470(int, int);
int __cdecl fcn_0046f100(int, int, int, int, int, int);
int __cdecl fcn_00472900(int, int);
int __cdecl fcn_00471af0(int, int);
int __cdecl fcn_005397c0(void);
int __cdecl fcn_004695a0(int, int);
int __cdecl WritePrivateProfileStringA(char*, char*, char*, char*);

/* ADDRESS: GOLDTL 0x00539930 */
unsigned int __cdecl fcn_00539930(int a0)
{
	int v17[24];
	int v18[225];
	int v20[8];
	int v23[33];
	int v28[16];
	char v16[22];
	char v19[32];
	char v21[260];
	char v22[49];
	char v24[128];
	char v25[128];
	unsigned char v26[36];
	char v27[260];
	char v29[16];
	char v30[16];
	int v36;
	int v38;
	int v4;
	int v5;
	int v12;
	int v14;
	int v15;
	int v32;
	char v2;
	unsigned char v3;
	int v34;
	int v35;
	int v37;
	int v39;
	int v40;
	unsigned int v41;
	unsigned int v42;
	unsigned int v43;
	unsigned int v44;
	int* v31;
	int* v13;
	int* v33;
	char* v7;
	char* v8;
	unsigned char* v9;

	v38 = 0;
	v4 = 1;
	v36 = g_6b7fac;
	v14 = -1;
	v5 = fcn_00470820(0, 0, s_6a3a6c);
	fcn_00471db0(v5, 1);
	fcn_00471d80(v5, 2);
	d2_SetForm(v5, 0);
	fcn_005340f0(g_772514);
	d2_SetForm(v5, 1);
	fcn_00519190(0x1ca5);
	d2_SetForm(v5, 3);
	fcn_00533a60(g_772514, 0, &v15, 3, g_14ac614, g_14ac618, g_14ac61c);
	fcn_00472640(v15, 0);
	if (fcn_005373e0(0x539930, 0x24087) != 0) {
		do {
			if (v36 + 0x5dc < g_6b7fac || v4 != 0) {
				int v6;
				v4 = 1;
				g_7725c8 = 1;
				v6 = fcn_005268c0(g_14ac5e4, 0);
				v36 = fcn_00402370(0x3039, 3000, v16, 8);
				fcn_00471e30(v6);
				v32 = 0;
				g_7725c8 = 0;
				d2_SetForm(v5, 2);
				fcn_0046f2c0(g_772514, 1);
				if (v14 != -1) {
					fcn_00469510(v14);
				}
				v14 = (int) d2_CreateRadioGroup(0);
				if (v36 >= 1) {
					v12 = -0x116;
					v34 = 0;
					v35 = 0xc;
					v31 = v17;
					v37 = -0x116;
					do {
						int v11;
						v11 = *(int*) ((int) v18 + v32);
						*v31 = -1;
						if (v11 == 0x3f) {
							if (a0 == 0) {
								goto label_539d27;
							}
							goto label_539ae5;
						}
label_539ae5:
						if (v11 == 0x7f) {
							if (a0 == 0) {
								goto label_539d27;
							}
						}
						if (v11 != 0x3f) {
							v13 = (int*) ((int) v20 + v32);
							sprintf(v21, s_6a3a54, &v26[v32 + 4]);
							v32 = vfs_Tfopen(v21, 0x6750e8, g_6b7fdc);
							if (v32 != 0) {
								v4 = 1;
								fcn_00521eb0(v32, v22);
								v12 = 0;
								if ((v44 & 0xff) != 0) {
									do {
										if (*v13 != v23[v12]) {
											v4 = 0;
											goto label_539ba4;
										}
										v12 += 1;
										v13 = &v13[1];
									} while (v12 < (int) (v44 & 0xff));
									CloseVfsStream(v32);
								} else {
label_539ba4:
									CloseVfsStream(v32);
								}
							} else {
								v4 = 0;
							}
							v8 = &v19[v34];
							v7 = v8;
							do {
								v2 = *v7;
								v7[v37] = v2;
								v7 = &v7[1];
							} while (v2 != 0);
							v12 = v37;
							v32 = v34;
						} else {
							v8 = &v19[v32];
							v7 = v8;
							do {
								v2 = *v7;
								v7[v12] = v2;
								v7 = &v7[1];
							} while (v2 != 0);
						}
						if (v4 != 0) {
							__strupr(v24);
							sprintf(v25, s_6a2e38, v24);
							v32 = fcn_00465950(v25);
							if (v32 == -1) {
								v32 = fcn_00465950(s_6a2e24);
							}
							d2_SetForm(v5, 2);
							v32 = fcn_0046f740(8, v34, v32, g_772514);
							*v31 = v32;
							*(int*) (v32 * 0x2f4 + 0x5c + (int) g_1015ea0) = 1;
							if (*(int*) ((int) v18 + v34) == 0x3f
									&& v26[v34] <= v26[v34 + 1]) {
								fcn_00472640(v32, 0);
							}
							*(int*) (v32 * 0x2f4 + 0x1d0 + (int) g_1015ea0) = 3;
							fcn_00469470(v14, v32);
							v32 = fcn_0046f100(0x88, v35, 400, 0x78, 0x10, g_772514);
							v31[1] = v32;
							fcn_00472900(*(int*) (g_772514 * 0x3cc + 0x10161bc), 0x53);
							fcn_00519190(0x1cbc, &v16[v34], v8, v26[v34]);
							v12 = v37;
							v32 = v34;
						} else {
							*v31 = -1;
						}
label_539d27:
						v31 = &v31[3];
						v32 += 0x80;
						v12 -= 0x80;
						v35 += 0x80;
						v36 -= 1;
						v34 = v32;
						v37 = v12;
					} while (v36 != 0);
				}
				v4 = 0;
				v36 = g_6b7fac;
			}
			if (g_14ce8e0 != 0 || g_14cf950 == 1) {
				g_774654 = 1;
			}
			if (g_100f1dc != -1) {
				int v40b;
				int v39b;
				v40b = v40;
				v39b = v39;
				if (g_67d370 != v34) {
					if (g_67d370 != v39b) {
						if (g_67d370 == v40b) {
							fcn_00471af0(v5, 0);
							if (fcn_005397c0() != 0) {
								g_774654 = 1;
								v38 = 1;
							}
							fcn_00471af0(v5, 1);
						}
					} else {
						v4 = 1;
					}
				} else {
					v32 = *(int*) (v14 * 0x8c + 0x102cbc8);
					if (v32 != -1) {
						v12 = v32 * 0x80;
						v8 = &v16[v12];
						v7 = v8;
						do {
							v2 = *v7;
							v7[0x7e2000 - (int) v8] = v2;
							v7 = &v7[1];
						} while (v2 != 0);
						WritePrivateProfileStringA(s_6a1e4c, s_6a3a4c, (char*) 0x7e2000, (char*) 0x7e22c0);
						g_774654 = 1;
						v38 = 1;
						{
							int v11b;
							unsigned int* v33b;
							v11b = 0x20;
							v33b = (unsigned int*) 0x9baa60;
							while (v11b != 0) {
								unsigned int* v1;
								v1 = &v33b[1];
								v7 = &v8[4];
								*v33b = *(unsigned int*) v8;
								v11b -= 1;
								v8 = v7;
								v33b = v1;
							}
						}
						if (a0 != 0 && v18[v32 * 0x20] == 0x7f) {
							unsigned char* v10;
							v8 = &v19[v12];
							v32 = 0x7e1d00 - (int) v8;
							do {
								v2 = *v8;
								v8[v32] = v2;
								v8 = &v8[1];
							} while (v2 != 0);
							v10 = &v26[v12 + 4];
							v32 = -(int) v10;
							v9 = v10;
							do {
								v3 = *v9;
								v9[v32 + 0x7e21a0] = v3;
								v9 = &v9[1];
							} while (v3 != 0);
							do {
								v3 = *v10;
								v10[v32 + 0x7e254a] = v3;
								v10 = &v10[1];
							} while (v3 != 0);
							g_7747b0 |= 0x40;
							sprintf(v27, s_6a3a54, (char*) 0x7e21a0);
							v32 = 0x3f;
							v31 = v28;
							while (v32 != 0) {
								v13 = &v31[1];
								*v31 = 0;
								v32 -= 1;
								v31 = v13;
							}
							v32 = vfs_Tfopen(v27, 0x6750e8, g_6b7fdc);
							if (v32 != 0) {
								fcn_00521eb0(v32, (char*) v28);
								CloseVfsStream(v32);
							}
							v32 = 0xc;
							v33 = (int*) 0x9bada0;
							while (v32 != 0) {
								int* v1;
								v1 = &v33[1];
								*v33 = 0;
								v32 -= 1;
								v33 = v1;
							}
							g_9badc0 = v41 & 0xff;
							g_9badc4 = v43 & 0xff;
							v32 = 0;
							do {
								v2 = v29[v32];
								*(char*) (v32 + 0x9bada0) = v2;
								v32 += 1;
							} while (v2 != 0);
							if (v28[0] >= 0x10054) {
								v32 = 0;
								do {
										v2 = v30[v32];
									*(char*) (v32 + 0x9badb0) = v2;
									v32 += 1;
								} while (v2 != 0);
								g_9badc8 = (int) (v41 >> 0x18);
								g_9badcc = v42;
							}
						}
					}
				}
			}
			fcn_00472640(v34, *(int*) (v14 * 0x8c + 0x102cbc8) != -1);
		} while (fcn_005373e0(0x539930, 0x24087) != 0);
		if (v14 != -1) {
			fcn_00469510(v14);
		}
	}
	fcn_00471e30(v5);
	return v38;
}
