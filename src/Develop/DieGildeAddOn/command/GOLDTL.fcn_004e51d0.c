/*
 * Run one hotkey/command step for the current object (building or vehicle):
 * refresh the selected entity list, handle the "cut" action, then dispatch
 * the per-type handler and its associated window.
 */

extern int g_1015ea0;           /* 0x01015ea0 */
extern int g_1040490;           /* 0x01040490 */
extern int g_1040494;           /* 0x01040494 */
extern int g_10421a0;           /* 0x010421a0 */
extern int g_10432a4;           /* 0x010432a4 */
extern int g_10529c8;           /* 0x010529c8 */
extern int g_14ac5e8;           /* 0x014ac5e8 */
extern int g_14ac5ec;           /* 0x014ac5ec */
extern int g_68bfb8;            /* 0x0068bfb8 */
extern int g_68bfbc;            /* 0x0068bfbc */
extern int g_6a3764;            /* 0x006a3764 */
extern int g_6a3768;            /* 0x006a3768 */
extern int g_6a376c;            /* 0x006a376c */
extern int g_6a3770;            /* 0x006a3770 */
extern int g_772f24;            /* 0x00772f24 */
extern int g_772f28;            /* 0x00772f28 */
extern int g_772f2c;            /* 0x00772f2c */
extern int g_772f30;            /* 0x00772f30 */
extern int g_772f34;            /* 0x00772f34 */
extern int g_772f38;            /* 0x00772f38 */
extern int g_772f3c;            /* 0x00772f3c */
extern int g_7747b0;            /* 0x007747b0 */
extern unsigned short g_774970; /* 0x00774970 */
extern int g_6b5c60;            /* 0x006b5c60 */

extern char s_68d580[]; /* "cut_type:%i" */
extern char s_68b300[]; /* 0x0068b300 */

int __cdecl fcn_004e6c80(void);
void __cdecl fcn_004e4f10(int);
int __cdecl gm_LookupEntityRecordById(int);
int __cdecl fcn_004c5790(int, int*);
void __cdecl fcn_005358e0(int);
int __cdecl fcn_00533a40(int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl fcn_00472500(int);
int __cdecl fcn_004c4450(int);
int __cdecl cm_RequestSendCutInfo(int, int);
int __cdecl fcn_004c4df0(int, int*);
void __cdecl fcn_00535960(void);
int __cdecl fcn_004e4fc0(unsigned int*);
void __cdecl fcn_004e5140(unsigned int*);
int __cdecl fcn_005373e0(int, int);
int __cdecl fcn_004e51a0(unsigned int*, int);
void __cdecl fcn_004e6c60(int);
int __cdecl sprintf(char*, const char*, ...);

/* ADDRESS: GOLDTL 0x004e51d0 */
void __cdecl fcn_004e51d0(unsigned int* a0, int a1)
{
	unsigned char v13[0x35c];
	unsigned char v14[0x35c];
	char v12[120];
	unsigned int v11;
	unsigned int* v6;
	int v7;
	int v8;
	int v9;
	int v10;
	int v15;
	int v17;
	int v20;
	int v21;
	int v22;
	unsigned char* v16;
	unsigned char* v18;
	unsigned char* v19;

	v7 = fcn_004e6c80();
	v6 = a0;
	fcn_004e4f10((int) a0);
	if ((g_7747b0 & 4) != 0) {
		if (v6[3] == *(int*) ((unsigned int) g_774970 * 0x21c + 0x7f4ca4)) {
			if (g_772f3c != 0) {
				goto label_4e526f;
			}
			v8 = *v6;
			v9 = 0x1f;
			v18 = (unsigned char*) &v11;
			while (v9 != 0) {
				v16 = v18 + 4;
				*(unsigned int*) v18 = 0;
				v9 -= 1;
				v18 = v16;
			}
			v11 = v8;
			sprintf(v12, s_68d580, *(char*) &v6[2]);
			fcn_004c5790(0x11, (int*) &v11);
		}
label_4e526f:
		if (g_772f3c == 0) {
			fcn_005358e0(g_14ac5e8);
		}
	}
	fcn_00533a40((int) &g_6b5c60);
	if ((g_7747b0 & 8) != 0) {
		v9 = 0;
		if (*(unsigned char*) &v6[0xc] != 0) {
			v15 = (int) v13;
			v17 = (int) &v6[0xd];
			do {
				g_772f28 = v9;
				if (*(int*) v17 != -1) {
					g_772f24 = gm_LookupEntityRecordById(*(int*) v17);
					if (g_772f24 != 0) {
						if (*(unsigned char*) (g_772f24 + 2) != 6) {
							int* v5;
							v5 = *(int**) ((unsigned int) *(unsigned char*) &v6[2] * 0x14 + 0x9b0848);
							if (v5 != 0) {
								((void (__cdecl*) (int, int)) v5)(v15, a1);
							}
						} else {
							g_772f34 = g_68bfbc + g_772f30;
							g_772f38 = 0;
							((void (__cdecl*) (int, int)) *(int*) ((unsigned int) *(unsigned char*) &v6[2] * 0x14 + 0x9b0844))(v15, a1);
						}
						d2_SetForm(v6[0xb], 0);
						io_AppendText(v15 + 0x14);
						io_AppendText(0x68b300);
					} else {
						*(int*) v17 = -1;
					}
				}
				v9 += 1;
				v17 += 4;
				v15 += 0x35c;
			} while (v9 < (int) (unsigned int) *(unsigned char*) &v6[0xc]);
		}
	} else if ((g_7747b0 & 4) != 0) {
		v9 = (unsigned int) g_774970 * 0x21c;
		g_772f24 = v9 + 0x7f4ca0;
		{
			unsigned char v3;
			v3 = *(unsigned char*) ((unsigned int) *(unsigned char*) &v6[2] * 0x14 + 0x9b084c);
			if (v3 != 1) {
				if (v3 == 0) {
					int v15b;
					v15b = 0;
					v22 = -1;
					v21 = -1;
					if (*(unsigned char*) &v6[0xc] != 0) {
						v17 = (int) &v6[0xd];
						do {
							if (*(int*) v17 == *(int*) (v9 + 0x7f4ca4)) {
								v22 = v15b;
								if (v15b != -1) {
									v21 = fcn_004e51a0(v6, v15b);
								}
								break;
							}
							v15b += 1;
							v17 += 4;
						} while (v15b < (int) (unsigned int) *(unsigned char*) &v6[0xc]);
					}
					v9 = fcn_004e4fc0(v6);
					while (v9 == 0) {
						unsigned int v8b;
						fcn_004e5140(v6);
						fcn_005373e0(0, g_68bfb8 | 0x8000);
						if (v22 != -1
								&& ((v22 == 0
									|| *(int*) (v21 * 0x35c + 0x9b0e28) == 1)
									&& *(int*) (v22 * 0x35c + 0x9b0e28) == 0)) {
							unsigned int* v18b;
							unsigned int* v16b;
							int v19b;
							g_772f28 = v22;
							v8b = v6[v22 + 0xd];
							v9 = 0xd7;
							v18b = (unsigned int*) (v22 * 0x35c + 0x9b0e20);
							v16b = (unsigned int*) v13;
							v19b = v9;
							v9 = v19b;
							while (v9 != 0) {
								unsigned int* v1;
								unsigned int* v2;
								v1 = v16b + 1;
								v2 = v18b + 1;
								*v16b = *v18b;
								v9 -= 1;
								v18b = v2;
								v16b = v1;
							}
							g_772f24 = gm_LookupEntityRecordById(v8b);
							fcn_004e5140(v6);
							g_772f34 = g_68bfbc + g_772f30;
							g_772f38 = 0;
							((void (__cdecl*) (void*, int)) *(int*) ((unsigned int) *(unsigned char*) &v6[2] * 0x14 + 0x9b0844))(v13, a1);
							*(int*) (&v13[8]) = 1;
							*(int*) (&v13[4]) = 0;
							fcn_004c4df0(0x35c, (int*) v13);
							v8b = cm_RequestSendCutInfo(*(unsigned int*) (g_772f24 + 4), *v6);
							v9 = fcn_004c4450(v8b);
							while (v9 == 0) {
								fcn_00535960();
								v9 = fcn_004c4450(v8b);
							}
							fcn_004e5140(v6);
							fcn_005373e0(0, g_68bfb8 | 0x8000);
						}
						if (v6[3] == *(int*) ((unsigned int) g_774970 * 0x21c + 0x7f4ca4)) {
							v9 = 0;
							if (*(unsigned char*) &v6[0xc] != 0) {
								int* v17b;
								int* v18c;
								v17b = (int*) 0x9b0e28;
								v18c = (int*) &v6[0xd];
label_4e5801:
								v15 = gm_LookupEntityRecordById(*v18c);
								if (v15 == 0 || *(unsigned char*) (v15 + 2) == 6
										|| *(unsigned char*) (v15 + 2) == 7
										|| (v17b != (int*) 0x9b0e28
											&& *(int*) (fcn_004e51a0(v6, v9) * 0x35c + 0x9b0e28) != 1)
										|| *v17b != 0) {
									goto label_4e5852;
								}
								{
									unsigned char v4;
									unsigned int* v18d;
									unsigned int* v16c;
									int v10b;
									int* v5;
									v4 = *(unsigned char*) &v6[2];
									v10b = 0xd7;
									v18d = (unsigned int*) (v9 * 0x35c + 0x9b0e20);
									v16c = (unsigned int*) v14;
									while (v10b != 0) {
										unsigned int* v1;
										unsigned int* v2;
										v1 = v16c + 1;
										v2 = v18d + 1;
										*v16c = *v18d;
										v10b -= 1;
										v18d = v2;
										v16c = v1;
									}
									v5 = *(int**) ((unsigned int) v4 * 0x14 + 0x9b0848);
									g_772f24 = v15;
									g_772f28 = v9;
									if (v5 != 0) {
										((void (__cdecl*) (void*, int)) v5)(v14, a1);
									}
									*(int*) (&v14[8]) = 1;
									*(int*) (&v14[4]) = 0;
									fcn_004c4df0(0x35c, (int*) v14);
									v8b = cm_RequestSendCutInfo(*(unsigned int*) (v15 + 4), *v6);
									v9 = fcn_004c4450(v8b);
									while (v9 == 0) {
										fcn_00535960();
										v9 = fcn_004c4450(v8b);
									}
									goto label_4e5922;
								}
							}
						}
label_4e5922:
						v9 = fcn_004e4fc0(v6);
					}
					fcn_004e5140(v6);
					fcn_005373e0(0, g_68bfb8 | 0x8000);
				}
			} else {
				if (v6[3] == *(int*) (v9 + 0x7f4ca4)) {
					v21 = 0;
					if (*(unsigned char*) &v6[0xc] != 0) {
						unsigned char* v18e;
						unsigned int* v20b;
						v18e = (unsigned char*) &v6[0xd];
						v20b = (unsigned int*) 0x9b0e20;
						do {
							int v8c;
							int v15c;
							v9 = gm_LookupEntityRecordById(*(int*) v18e);
							if (v9 != 0 && *(unsigned char*) (v9 + 2) != 6
									&& *(unsigned char*) (v9 + 2) != 7
									&& v20b[2] == 0) {
								unsigned int* v16d;
								unsigned int* v19c;
								int v10c;
								int* v5;
								v8c = *(unsigned char*) &v6[2];
								v15c = 0xd7;
								v16d = v20b;
								v19c = (unsigned int*) v13;
								while (v15c != 0) {
									unsigned int* v1;
									unsigned int* v2;
									v1 = v19c + 1;
									v2 = v16d + 1;
									*v19c = *v16d;
									v15c -= 1;
									v16d = v2;
									v19c = v1;
								}
								v5 = *(int**) ((unsigned int) v8c * 0x14 + 0x9b0848);
								g_772f24 = v9;
								if (v5 != 0) {
									((void (__cdecl*) (void*, int)) v5)(v13, a1);
								}
								*(int*) (&v13[8]) = 1;
								*(int*) (&v13[4]) = 0;
								fcn_004c4df0(0x35c, (int*) v13);
								v8c = cm_RequestSendCutInfo(*(unsigned int*) (v9 + 4), *v6);
								v9 = fcn_004c4450(v8c);
								while (v9 == 0) {
									fcn_00535960();
									v9 = fcn_004c4450(v8c);
								}
								fcn_004e5140(v6);
								fcn_005373e0(0, g_68bfb8 | 0x8000);
							}
							v21 += 1;
							v18e += 4;
							v20b = (unsigned int*) ((char*) v20b + 0x35c);
						} while (v21 < (int) (unsigned int) *(unsigned char*) &v6[0xc]);
					}
				}
				v9 = 0;
				g_772f24 = (unsigned int) g_774970 * 0x21c + 0x7f4ca0;
				if (*(unsigned char*) &v6[0xc] != 0) {
					int* v17c;
					v17c = (int*) &v6[0xd];
label_4e551b:
					if (*v17c != *(int*) ((unsigned int) g_774970 * 0x21c + 0x7f4ca4)) {
						goto label_4e551f;
					}
					{
						unsigned int* v18f;
						unsigned int* v16e;
						int v15d;
						g_772f34 = g_68bfbc + g_772f30;
						v15d = 0xd7;
						v18f = (unsigned int*) (v9 * 0x35c + 0x9b0e20);
						v16e = (unsigned int*) v13;
						while (v15d != 0) {
							unsigned int* v1;
							unsigned int* v2;
							v1 = v16e + 1;
							v2 = v18f + 1;
							*v16e = *v18f;
							v15d -= 1;
							v18f = v2;
							v16e = v1;
						}
					}
					g_772f38 = 0;
					((void (__cdecl*) (void*, int)) *(int*) ((unsigned int) *(unsigned char*) &v6[2] * 0x14 + 0x9b0844))(v13, a1);
					*(int*) (&v13[8]) = 1;
					*(int*) (&v13[4]) = 0;
					fcn_004c4df0(0x35c, (int*) v13);
					{
						int v8d;
						v8d = cm_RequestSendCutInfo(*(unsigned int*) (g_772f24 + 4), *v6);
						v9 = fcn_004c4450(v8d);
						while (v9 == 0) {
							fcn_00535960();
							v9 = fcn_004c4450(v8d);
						}
					}
					goto label_4e55e3;
				}
label_4e55e3:
				v9 = fcn_004e4fc0(v6);
				while (v9 == 0) {
					fcn_004e5140(v6);
					fcn_00533a40(g_14ac5ec);
					fcn_005373e0(0, g_68bfb8 | 0x8000);
					v9 = fcn_004e4fc0(v6);
				}
			}
		}
	}
	g_772f2c += 1;
	fcn_004e6c60(v7);
	return;
label_4e5852:
	v9 += 1;
	{
		int* v17d;
		int* v18g;
		v17d = (int*) 0x9b0e28;
		v18g = (int*) &v6[0xd];
		(void) v17d;
		(void) v18g;
	}
	goto label_4e5922;
label_4e551f:
	v9 += 1;
	if ((int) (unsigned int) *(unsigned char*) &v6[0xc] <= v9) {
		goto label_4e55e3;
	}
	goto label_4e551b;
}
