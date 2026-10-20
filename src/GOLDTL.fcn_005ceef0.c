#include <string.h>

extern int g_775348;
extern int g_772514;
extern char g_773d75;
extern int g_100f1dc;
extern int g_774654;
extern int g_67d370;
extern int g_14ce8d0;
extern int g_14ce8d8;
extern int g_14ce8e0;
extern char* g_1015ea0;
extern int g_aed32c;
extern float g_662910;
extern int g_14a90a0;
extern int g_14b5874;

int* __cdecl fcn_005b1b10(int a);
int* __cdecl fcn_005b1b30(int a);
void __cdecl fcn_005b1e20(int a);
void __cdecl fcn_005b1ce0(int a, unsigned int b, unsigned int c);
void __cdecl fcn_005b1ed0(int a, float v);
int __cdecl fcn_00470820(int a, int b, char* name);
void __cdecl fcn_004727a0(int a, int b);
void __cdecl fcn_005340f0(int a);
void __cdecl fcn_00471b60(int a);
void __cdecl fcn_00473a90(int a, int b);
int __cdecl fcn_0050b710(int a, unsigned char k);
int __cdecl fcn_0050b750(int a, unsigned char k);
void __cdecl fcn_005ced80(int dlg, int* list, int* bars, int* icons);
void __cdecl fcn_005ce800(int id, int* out, int* value, int* slots,
	unsigned char* type, int text, unsigned int flags, int pad7, int pad8,
	int pad9, int* handle, int source);
void __cdecl fcn_00533a60(int a, int b, int* c, int d, int e, int f);
int __cdecl fcn_00471f80(int a);
void __cdecl fcn_00472380(int a, int b, int c, unsigned char d);
void __cdecl fcn_00472640(int a, int b);
void __cdecl fcn_004c4510(void* p, unsigned int value);
void __cdecl fcn_004c4570(int a, int b, int off, unsigned int* value);
void __cdecl fcn_004c4670(int a, int b, int off, void* value);
void __cdecl fcn_004c5360(void);
int __cdecl fcn_005373e0(void* fn, int msg);
void __cdecl fcn_00471e30(int a);

/* ADDRESS: GOLDTL 0x005ceef0 */
void __cdecl fcn_005ceef0(int a0, unsigned short* a1)
{
	unsigned int v10;
	unsigned int v11;
	int v12[7];
	int v13;
	int v14[4];
	int v15;
	unsigned int v16;
	int v17[7];
	int v18;
	unsigned int v19;
	char v2;
	char v20;
	char* v21;
	int v22;
	int v23;
	unsigned int v24;
	char* v26;
	int* v27;
	unsigned int v28;
	int v29;
	int v3;
	int v30;
	int v31;
	unsigned int v32;
	unsigned int v33;
	unsigned int v34;
	unsigned short* v4;
	unsigned int v5;
	int v6;
	int v7;
	int v8;
	unsigned int v9;

	v3 = a0;
	v20 = 1;
	v29 = -1;
	v30 = -1;
	v13 = -1;
	v27 = fcn_005b1b10(*(unsigned int*) ((char*) a0 + 1));
	memset(v12, -1, sizeof(v12));
	if (v27) {
		fcn_005b1e20(v3);
	}
	else {
		v27 = fcn_005b1b30(v3);
		if (v27) {
			fcn_005b1e20(v3);
		}
		else {
			v20 = 0;
			g_775348 = 0;
		}
	}
	v5 = fcn_00470820(0, 0, (char*) 0x6aca84);
	v28 = v5;
	fcn_004727a0(v5, 0);
	fcn_005340f0(g_772514);
	fcn_00471b60(v5);
	fcn_00473a90(0, 0);
	v15 = fcn_0050b710(*(unsigned int*) ((char*) v3 + 0x39), g_773d75);
	v8 = (int) v27;
	v4 = a1;
	v19 = *(unsigned int*) &a1[0xda];
	v32 = *(unsigned int*) &a1[0xdc];
	v33 = *(unsigned int*) &a1[0xde];
	v34 = *(unsigned int*) &a1[0xe0];
	if (g_775348) {
		fcn_005ced80(v5, v27, v12, v17);
		v8 = (int) v27;
	}
	else {
		fcn_005ce800(v28, &v16, &v15, v14, (unsigned char*) v3, *a1,
			*(unsigned int*) &a1[0xda], *(unsigned int*) &a1[0xdc],
			*(unsigned int*) &a1[0xde], *(unsigned int*) &a1[0xe0],
			&v13, (int) v27);
	}
	if (v20) {
		fcn_004727a0(v28, 3);
		fcn_00533a60(g_772514, 0, &v18, 2, g_14a90a0, g_14b5874);
		v29 = v18;
		v30 = v31;
	}
	g_100f1dc = -1;
	for (;;) {
		if (g_14ce8e0) {
			g_774654 = 1;
		}
		else if (g_14ce8d0) {
			if (g_775348 != 1) {
				if (!g_775348 && v13 != -1 && g_67d370 == v13) {
					v18 = fcn_00471f80(v13);
					fcn_005b1ed0(v3, (float) v18 * g_662910);
				}
			}
			else {
				v23 = 0;
				do {
					if (g_67d370 == v12[v23]) {
						if (v23 <= 6 && v12[v23] != -1) {
							g_100f1dc = -1;
							v5 = fcn_00471f80(v12[v23]);
							fcn_005b1ce0(v3,
								*(unsigned int*) (v8 + v23 * 8),
								v5);
							v23 = 0;
							v26 = (char*) (v8 + 4);
							do {
								if (v12[v23] != -1) {
									fcn_00472380(v12[v23], 0, 100,
										*v26);
								}
								v23 += 1;
								v26 = &v26[8];
							} while (v23 < 7);
							v8 = (int) v27;
						}
						break;
					}
					v23 += 1;
				} while (v23 < 7);
			}
		}
		v23 = g_67d370;
		if (g_14ce8d8 && g_67d370 != -1) {
			v21 = (char*) (v8 + 5);
			v8 = 0;
			do {
				v23 = *(int*) ((char*) v17 + v8);
				if (g_67d370 == v23) {
					v2 = *v21;
					*v21 = (v2 == 0);
					*(unsigned int*) (g_1015ea0 + 0x38
						+ v23 * 0x2f4) = (v2 != 0);
					fcn_00472640(*(unsigned int*) ((char*) v12 + v8),
						*v21 == 0);
				}
				v8 += 4;
				v21 = &v21[8];
			} while (v8 < 0x1c);
			v23 = g_67d370;
			v8 = (int) v27;
		}
		if (g_100f1dc != -1) {
			if (g_775348 != 1) {
				if (!g_775348) {
					v15 = fcn_00471f80(v16);
					if (g_67d370 != v30) {
						v24 = 0;
						v23 = g_67d370;
						do {
							if (v23 == -1) {
								break;
							}
							v22 = v14[v24];
							if (v23 == v22) {
								v19 = *(unsigned int*) &v4[0xda];
								v32 = *(unsigned int*) &v4[0xdc];
								v33 = *(unsigned int*) &v4[0xde];
								v34 = *(unsigned int*) &v4[0xe0];
								if (fcn_00471f80(v22)) {
									switch (v24) {
									case 0:
										v19 |= 1;
										break;
									case 1:
										v19 |= 2;
										break;
									case 2:
										v19 |= 4;
										break;
									case 3:
										v19 |= 8;
										break;
									}
								}
								else {
									switch (v24) {
									case 0:
										v19 &= ~1;
										break;
									case 1:
										v19 &= ~2;
										break;
									case 2:
										v19 &= ~4;
										break;
									case 3:
										v19 &= ~8;
										break;
									}
								}
								fcn_004c4510(v4,
									*(unsigned int*) ((char*) v4 + 4));
								fcn_004c4570(4, 1,
									(int) ((char*) v4 + 0x1b4
										- g_aed32c), &v19);
								fcn_004c5360();
								fcn_004c4510(v3,
									*(unsigned int*) ((char*) v3 + 1));
								fcn_004c4570(4, 1,
									(int) ((char*) v3 + 0x99
										- g_aed32c), &v19);
								fcn_004c5360();
								fcn_005ce800(v28, &v16, &v15, v14,
									(unsigned char*) v3, *v4, v19, v32,
									v33, v34, &v13, (int) v27);
								v23 = -1;
								g_67d370 = -1;
							}
							v24 += 1;
						} while ((int) v24 < 4);
					}
					else {
						fcn_005ced80(v28, v27, v12, v17);
						g_775348 = 1;
						g_67d370 = -1;
					}
				}
			}
			else if (v23 != v29) {
				v22 = 0;
				do {
					if (v23 == v12[v22]) {
						if (v22 <= 6) {
							v5 = fcn_00471f80(v12[v22]);
							fcn_005b1ce0(v3,
								*(unsigned int*) (v8 + v22 * 8), v5);
							v23 = 0;
							v26 = (char*) (v8 + 4);
							do {
								if (v12[v23] != -1) {
									fcn_00472380(v12[v23], 0, 100,
										*v26);
								}
								v23 += 1;
								v26 = &v26[8];
							} while (v23 < 7);
							v8 = (int) v27;
						}
						break;
					}
					v22 += 1;
				} while (v22 < 7);
			}
			else {
				fcn_005ce800(v28, &v16, &v15, v14,
					(unsigned char*) v3, *v4, v19, v32, v33, v34,
					&v13, (int) v27);
				g_775348 = 0;
				g_67d370 = -1;
			}
		}
		v6 = fcn_005373e0((void*) fcn_005ceef0, 0x677c7);
		if (!v6) {
			v5 = v10;
			if (!g_775348) {
				fcn_00471f80(v16);
				v5 = v11;
				v15 = v7;
			}
			v15 = fcn_0050b750(v15, g_773d75);
			fcn_004c4510(v3, *(unsigned int*) ((char*) v3 + 1));
			fcn_004c4570(4, 1,
				(int) ((char*) v3 + 0x39 - g_aed32c), &v15);
			fcn_004c5360();
			v18 = v15 - *(int*) ((char*) v3 + 0x39);
			fcn_004c4510(v4, *(unsigned int*) ((char*) v4 + 4));
			fcn_004c4670(4, 1,
				(int) ((char*) v4 + 0x1b8 - g_aed32c), &v18);
			fcn_004c5360();
			fcn_00471e30(v28);
			return;
		}
	}
}
