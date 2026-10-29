#include <string.h>

extern void* g_6b7fdc;

void* __cdecl vfs_Tfopen(const char*, const char*, void*);
int __cdecl vfs_ReadData(char*, int, int, void*);
int __cdecl fcn_0044d770(void*);
int __cdecl fcn_004011f0(void*, void*);
int __cdecl fcn_00401180(void*, void*);
void __cdecl fcn_004011a0(void*, char*);
void __cdecl fcn_00401280(void*, void*);
void* __cdecl m_alloc(unsigned int, const char*);
void __cdecl m_FreeTracked(void*);
void __cdecl fcn_0041d9e0(const char*);
void __cdecl CloseVfsStream(void*);
long __cdecl _ftol(float);

/* Chunked binary animation-stream loader.  The returned record is 0x16c
 * bytes; its frame table is v12 entries of 0xc0 bytes. */
/* ADDRESS: GOLDTL 0x0044e1e0 */
char* __cdecl d3_LoadBinaryAnimStream(char* path, char* name, char a2)
{
	int v11;
	int v22;
	int v12;
	int v15;
	int v17;
	int v29;
	int v16;
	int v24;
	int v19;
	int v20;
	int v21;
	int v30;
	int v18;
	int v31;
	int v27;
	char v10[4];
	float v23[4];
	float v34;
	float v35;
	float v36;
	float vpad2;
	float v25[4];
	float v39;
	float v40;
	float v28;
	char v13;
	char v14;
	int v3;
	int v4;
	int v9;
	char* v2;
	char* v26;

	v19 = -1;
	v20 = -1;
	v17 = -1;
	v18 = -1;
	v12 = 0;
	v16 = 1;
	v15 = 0;
	v14 = 0;
	v13 = 1;
	v26 = 0;
	v2 = (char*) vfs_Tfopen(path, (char*) 0x6750e8, g_6b7fdc);
	v31 = (int) v2;
	if (v2 != 0) {
		vfs_ReadData(v10, 4, 1, v2);
		if (fcn_0044d770(v2) == 0x30) {
			fcn_004011f0(v2, &v11);
			if (fcn_0044d770(v2) == 1 && (unsigned int) v11 > 0xabcd0001) {
				CloseVfsStream(v2);
				return 0;
			}
			v3 = fcn_0044d770(v2);
			if (v3 == 0x23) {
				fcn_004011f0(v2, &v12);
				if (v12 > 0) {
					v26 = (char*) m_alloc(0x16c, (char*) 0x67ba68);
					strncpy(v26, name, 0x3f);
					*(int*) (v26 + 0x148) = v12;
					*(int*) (v26 + 0x150) = 0;
					*(char*) (v26 + 0x168) = 0;
					*(int*) (v26 + 0x154) = v12 - 1;
					*(char*) (v26 + 0x169) = a2;
					*(int*) (v26 + 0x15c) = (int) m_alloc(v12 * 0xc0,
						(char*) 0x67ba2c);
				}
				v3 = fcn_0044d770(v2);
			}
			if (v3 == 0x33) {
				fcn_00401180(v2, &v13);
				v3 = fcn_0044d770(v2);
			}
			if (v3 == 0x24) {
				fcn_00401180(v2, &v14);
				v3 = fcn_0044d770(v2);
			}
			if (v3 == 0x37) {
				fcn_004011f0(v2, &v15);
				if (v26 != 0) {
					*(int*) (v26 + 0x144) = v15;
				}
				v3 = fcn_0044d770(v2);
			}
			if (v3 == 0x36) {
				fcn_004011f0(v2, &v16);
				v3 = fcn_0044d770(v2);
			}
			if (v3 == 0x34) {
				fcn_004011f0(v2, &v17);
				v3 = fcn_0044d770(v2);
			}
			if (v3 == 0x35) {
				fcn_004011f0(v2, &v18);
				v3 = fcn_0044d770(v2);
			}
			if (v3 == 0x29) {
				fcn_004011f0(v2, &v19);
				if (v26 != 0) {
					*(int*) (v26 + 0x150) = v19;
				}
				v3 = fcn_0044d770(v2);
			}
			if (v3 == 0x2a) {
				fcn_004011f0(v2, &v20);
				if (v26 != 0) {
					*(int*) (v26 + 0x154) = v20;
				}
				v3 = fcn_0044d770(v2);
			}
			if (v26 != 0 && *(int*) (v26 + 0x150) > *(int*) (v26 + 0x154)) {
				v9 = *(int*) (v26 + 0x154);
				*(int*) (v26 + 0x154) = *(int*) (v26 + 0x150);
				*(int*) (v26 + 0x150) = v9;
			}
			for (v11 = 0; v11 < v12; v11++) {
				v21 = -1;
				v29 = 0;
				for (v30 = 0; v30 < v16; v30++) {
					if (v3 == 0x18) {
						fcn_004011f0(v2, &v21);
						if (v26 != 0) {
							*(int*) (v11 * 0xc0
								+ *(int*) (v26 + 0x15c)) = v21;
						}
						v3 = fcn_0044d770(v2);
					}
					v22 = 0;
					if (v13 != 0 && v3 == 0x19) {
						fcn_004011f0(v2, &v22);
						if (v26 != 0) {
							if (*(int*) (v26 + 0x140) != 0) {
								if (v17 == -1
									&& *(int*) (v26 + 0x140) != v22) {
									fcn_0041d9e0((char*) 0x67b9ec);
								}
							}
							else if (v17 >= 0) {
								*(int*) (v26 + 0x140) = v17;
							}
							else {
								*(int*) (v26 + 0x140) = v22;
							}
						}
						v3 = fcn_0044d770(v2);
					}
					if (v3 == 0x21) {
						if (v26 != 0 && v29 == 0) {
							if (v17 > 0) {
								v4 = (int) m_alloc(v17 * 0xc,
									(char*) 0x67b9a8);
							}
							else {
								v4 = (int) m_alloc(v22 * 0xc,
									(char*) 0x67b9a8);
							}
							*(int*) (v11 * 0xc0 + 0xbc
								+ *(int*) (v26 + 0x15c)) = v4;
						}
						v3 = 0;
						if (v22 > 0) {
							v27 = v29 * 0xc;
							do {
								fcn_00401280(v2, v23);
								if (v26 != 0) {
									if (v11 != 0) {
										*(float*) (v27 + *(int*) (v11 * 0xc0
											+ 0xbc + *(int*) (v26 + 0x15c)))
											= v23[0] - *(float*) (*(int*) (*(int*) (v26 + 0x15c) + 0xbc) + v27);
										*(float*) (*(int*) (v11 * 0xc0
											+ 0xbc + *(int*) (v26 + 0x15c)) + 4 + v27)
											= v23[1] - *(float*) (*(int*) (*(int*) (v26 + 0x15c) + 0xbc) + 4 + v27);
										*(float*) (*(int*) (v11 * 0xc0
											+ 0xbc + *(int*) (v26 + 0x15c)) + 8 + v27)
											= v23[2] - *(float*) (*(int*) (*(int*) (v26 + 0x15c) + 0xbc) + 8 + v27);
									}
									else {
										*(float*) (v27 + *(int*) (*(int*) (v26 + 0x15c) + 0xbc)) = v23[0];
										*(float*) (*(int*) (*(int*) (v26 + 0x15c) + 0xbc) + 4 + v27) = v23[1];
										*(float*) (*(int*) (*(int*) (v26 + 0x15c) + 0xbc) + 8 + v27) = v23[2];
									}
								}
								v3++;
								v27 += 0xc;
							} while (v3 < v22);
						}
						v29 += v22;
						v3 = fcn_0044d770(v2);
						if (v3 != 0x28) {
							fcn_0041d9e0((char*) 0x67b968);
						}
						else {
							v3 = fcn_0044d770(v2);
						}
					}
					if (v14 != 0 && v3 == 0x1a) {
						fcn_004011f0(v2, &v24);
						v3 = fcn_0044d770(v2);
						if (v3 == 0x22) {
							v3 = 0;
							if (v24 > 0) {
								do {
									fcn_00401280(v2, v23);
									fcn_00401280(v2, v25);
									v3++;
								} while (v3 < v24);
							}
							v3 = fcn_0044d770(v2);
						}
						if (v3 != 0x28) {
							fcn_0041d9e0((char*) 0x67b92c);
						}
						else {
							v3 = fcn_0044d770(v2);
						}
					}
				}
				if (v3 == 0x31) {
					fcn_00401280(v2, v23);
					fcn_00401280(v2, v25);
					if (v26 != 0) {
						*(float*) (v11 * 0xc0 + 0x20 + *(int*) (v26 + 0x15c)) = v23[0];
						*(float*) (v11 * 0xc0 + 0x24 + *(int*) (v26 + 0x15c)) = v23[1];
						*(float*) (v11 * 0xc0 + 0x28 + *(int*) (v26 + 0x15c)) = v23[2];
						*(float*) (v11 * 0xc0 + 0x2c + *(int*) (v26 + 0x15c)) = v25[0];
						*(float*) (v11 * 0xc0 + 0x30 + *(int*) (v26 + 0x15c)) = v25[1];
						*(float*) (v11 * 0xc0 + 0x34 + *(int*) (v26 + 0x15c)) = v25[2];
					}
					v3 = fcn_0044d770(v2);
				}
				v9 = 0;
				if (v15 > 0) {
					v29 = (int) (v26 + 0x40);
					do {
						if (v3 == 0x38) {
							fcn_004011a0(v2, (char*) v29);
							v3 = fcn_0044d770(v2);
						}
						if (v3 == 0x39) {
							fcn_00401280(v2, (void*) (*(int*) (v26 + 0x15c)
								+ 0x54 + (v9 + v11 * 8) * 0x18));
							v3 = fcn_0044d770(v2);
						}
						if (v3 == 0x3a) {
							fcn_00401280(v2, (void*) (*(int*) (v26 + 0x15c)
								+ (v9 + 4 + v11 * 8) * 0x18));
							v3 = fcn_0044d770(v2);
						}
						v9++;
						v29 += 0x40;
					} while (v9 < v15);
				}
			}
			if (v3 == 0x32) {
				fcn_00401280(v2, v23);
				fcn_00401280(v2, v25);
				v3 = fcn_0044d770(v2);
			}
			if (v3 != 0x2f) {
				fcn_0041d9e0((char*) 0x67b8e8);
			}
			if (v26 != 0) {
				if (v17 >= 0) {
					v22 = v17;
				}
				if (v18 >= 0) {
					v24 = v18;
				}
				if (*(int*) (v26 + 0x150) < 0) {
					*(int*) (v26 + 0x150) = 0;
				}
				v3 = *(int*) (v26 + 0x148);
				if (*(int*) (v26 + 0x150) >= v3) {
					*(int*) (v26 + 0x150) = v3 - 1;
				}
				if (*(int*) (v26 + 0x154) < 0) {
					*(int*) (v26 + 0x154) = 0;
				}
				if (*(int*) (v26 + 0x154) >= v3) {
					*(int*) (v26 + 0x154) = v3 - 1;
				}
				for (v11 = 0; v11 < v12 - 1; v11++) {
					v4 = v11 * 0xc0 + *(int*) (v26 + 0x15c);
					*(int*) (v4 + 4) = *(int*) ((v11 * 3 + 3) * 0x40
						+ *(int*) (v26 + 0x15c)) - *(int*) v4;
				}
				v3 = v12 * 0xc0 + *(int*) (v26 + 0x15c);
				*(int*) (v3 - 0xbc) = *(int*) (v3 - 0x17c);
				for (v11 = 1; v11 < v12; v11++) {
					v4 = *(int*) (v26 + 0x15c);
					*(float*) (v11 * 0xc0 + 0x20 + v4)
						= *(float*) (v11 * 0xc0 + 0x20 + v4)
						- *(float*) (v4 + 0x20);
					v4 = *(int*) (v26 + 0x15c);
					*(float*) (v11 * 0xc0 + 0x24 + v4)
						= *(float*) (v11 * 0xc0 + 0x24 + v4)
						- *(float*) (v4 + 0x24);
					v4 = *(int*) (v26 + 0x15c);
					*(float*) (v11 * 0xc0 + 0x28 + v4)
						= *(float*) (v11 * 0xc0 + 0x28 + v4)
						- *(float*) (v4 + 0x28);
					v4 = *(int*) (v26 + 0x15c);
					*(float*) (v11 * 0xc0 + 0x2c + v4)
						= *(float*) (v11 * 0xc0 + 0x2c + v4)
						- *(float*) (v4 + 0x2c);
					v4 = *(int*) (v26 + 0x15c);
					*(float*) (v11 * 0xc0 + 0x30 + v4)
						= *(float*) (v11 * 0xc0 + 0x30 + v4)
						- *(float*) (v4 + 0x30);
					v4 = *(int*) (v26 + 0x15c);
					*(float*) (v11 * 0xc0 + 0x34 + v4)
						= *(float*) (v11 * 0xc0 + 0x34 + v4)
						- *(float*) (v4 + 0x34);
				}
				v4 = *(int*) (v26 + 0x15c);
				*(int*) (v4 + 0x20) = 0;
				*(int*) (v4 + 0x24) = 0;
				*(int*) (v4 + 0x28) = 0;
				*(int*) (v4 + 0x2c) = 0;
				*(int*) (v4 + 0x30) = 0;
				*(int*) (v4 + 0x34) = 0;
				for (v11 = 0; v11 < *(int*) (v26 + 0x140); v11++) {
					*(int*) (*(int*) (*(int*) (v26 + 0x15c) + 0xbc)
						+ v11 * 0xc) = 0;
					*(int*) (*(int*) (*(int*) (v26 + 0x15c) + 0xbc)
						+ 4 + v11 * 0xc) = 0;
					*(int*) (*(int*) (*(int*) (v26 + 0x15c) + 0xbc)
						+ 8 + v11 * 0xc) = 0;
				}
				for (v11 = 0; v11 < v12; v11++) {
					if (*(char*) (v26 + 0x169) != 0) {
						for (v9 = 0; v9 < *(int*) (v26 + 0x140); v9++) {
							v27 = *(int*) (*(int*) (v26 + 0x15c) + v11 * 0xc0 + 0xbc);
							*(float*) (v27 + v9 * 0xc)
								= *(float*) (v27 + v9 * 0xc)
								- *(float*) (v11 * 0xc0 + 0x20
								+ *(int*) (v26 + 0x15c));
							v27 = *(int*) (*(int*) (v26 + 0x15c) + v11 * 0xc0 + 0xbc);
							*(float*) (v27 + 4 + v9 * 0xc)
								= *(float*) (v27 + 4 + v9 * 0xc)
								- *(float*) (v11 * 0xc0 + 0x24
								+ *(int*) (v26 + 0x15c));
							v27 = *(int*) (*(int*) (v26 + 0x15c) + v11 * 0xc0 + 0xbc);
							*(float*) (v27 + 8 + v9 * 0xc)
								= *(float*) (v27 + 8 + v9 * 0xc)
								- *(float*) (v11 * 0xc0 + 0x28
								+ *(int*) (v26 + 0x15c));
						}
						for (v9 = 0; v9 < v15; v9++) {
							v27 = *(int*) (v26 + 0x15c);
							*(float*) (v27 + 0x54 + v9 * 0x18)
								= *(float*) (v27 + 0x54 + v9 * 0x18)
								- *(float*) (v11 * 0xc0 + 0x20 + v27);
							v27 = *(int*) (v26 + 0x15c);
							*(float*) (v27 + 0x58 + v9 * 0x18)
								= *(float*) (v27 + 0x58 + v9 * 0x18)
								- *(float*) (v11 * 0xc0 + 0x24 + v27);
							v27 = *(int*) (v26 + 0x15c);
							*(float*) (v27 + 0x5c + v9 * 0x18)
								= *(float*) (v27 + 0x5c + v9 * 0x18)
								- *(float*) (v11 * 0xc0 + 0x28 + v27);
						}
					}
					v34 = 1e+10f;
					v35 = 1e+10f;
					v36 = 1e+10f;
					v39 = -1e+10f;
					v40 = -1e+10f;
					v28 = *(float*) 0x662c6c;
					if (v22 > 0) {
						v4 = *(int*) (v11 * 0xc0 + 0xbc + *(int*) (v26 + 0x15c));
						if (v22 > 0) {
							v9 = v22;
							do {
								if (*(float*) v4 <= v34) {
									v34 = *(float*) v4;
								}
								if (*(float*) (v4 + 4) <= v35) {
									v35 = *(float*) (v4 + 4);
								}
								if (*(float*) (v4 + 8) <= v36) {
									v36 = *(float*) (v4 + 8);
								}
								if (v39 <= *(float*) v4) {
									v39 = *(float*) v4;
								}
								if (v40 <= *(float*) (v4 + 4)) {
									v40 = *(float*) (v4 + 4);
								}
								if (v28 <= *(float*) (v4 + 8)) {
									v28 = *(float*) (v4 + 8);
								}
								v4 += 0xc;
								v9--;
							} while (v9 != 0);
						}
					}
					*(float*) (v11 * 0xc0 + 8 + *(int*) (v26 + 0x15c)) = v34;
					*(float*) (v11 * 0xc0 + 0xc + *(int*) (v26 + 0x15c)) = v35;
					*(float*) (v11 * 0xc0 + 0x10 + *(int*) (v26 + 0x15c)) = v36;
					v23[0] = v39 - v34;
					v23[1] = v40 - v35;
					v23[2] = v28 - v36;
					*(float*) (v11 * 0xc0 + 0x14 + *(int*) (v26 + 0x15c))
						= v23[0] * *(float*) 0x662c30;
					*(float*) (v11 * 0xc0 + 0x18 + *(int*) (v26 + 0x15c))
						= v23[1] * *(float*) 0x662c30;
					*(float*) (v11 * 0xc0 + 0x1c + *(int*) (v26 + 0x15c))
						= v23[2] * *(float*) 0x662c30;
					v4 = v11 * 0xc0 + 4 + *(int*) (v26 + 0x15c);
					*(int*) v4 = *(int*) v4 * 3;
					v4 = (int) m_alloc(v22 * 3, (char*) 0x67b8a0);
					v30 = 0;
					*(int*) (v11 * 0xc0 + 0xb4 + *(int*) (v26 + 0x15c)) = v4;
					if (v22 > 0) {
						v2 = 0;
						v29 = 0;
						do {
							v27 = v11 * 0xc0;
							v25[0] = *(float*) (*(int*) (*(int*) (v26 + 0x15c) + 0xbc + v27) + (int) v2) - v34;
							v25[1] = *(float*) (*(int*) (*(int*) (v26 + 0x15c) + 0xbc + v27) + 4 + (int) v2) - v35;
							v25[2] = *(float*) (*(int*) (*(int*) (v26 + 0x15c) + 0xbc + v27) + 8 + (int) v2) - v36;
							*(char*) (v29 + *(int*) (*(int*) (v26 + 0x15c) + 0xb4 + v27))
								= (char) _ftol(v25[0] * *(float*) 0x6628a4 / v23[0]);
							*(char*) (*(int*) (v11 * 0xc0 + 0xb4 + *(int*) (v26 + 0x15c)) + 1 + v29)
								= (char) _ftol(v25[1] * *(float*) 0x6628a4 / v23[1]);
							v2 = (char*) ((int) v2 + 0xc);
							v29 += 3;
							*(char*) (*(int*) (v11 * 0xc0 + 0xb4 + *(int*) (v26 + 0x15c)) + -1 + v29)
								= (char) _ftol(v25[2] * *(float*) 0x6628a4 / v23[2]);
							v30++;
						} while (v30 < v22);
						v2 = (char*) v31;
					}
					m_FreeTracked((void*) *(int*) (v11 * 0xc0 + 0xbc
						+ *(int*) (v26 + 0x15c)));
					*(int*) (v11 * 0xc0 + 0xbc + *(int*) (v26 + 0x15c)) = 0;
				}
			}
		}
		CloseVfsStream(v2);
	}
	return v26;
}
/* Layout scaffolding: shifts the next source object to its reference
 * VA. 0x90 filler, not reconstruction. Generated by the text lead pass. */
#pragma data_seg(".text")

/* Layout scaffolding: shifts the next source object to its reference
 * VA. 0x90 filler, not reconstruction. Generated by the text lead pass. */
#pragma data_seg(".text")


/* Layout scaffolding: aligned this TU with its neighbours. */
#pragma data_seg(".text")
unsigned char _tlead_GOLDTL_d3_LoadBinaryAnimStream[0x70] = {
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90
};
