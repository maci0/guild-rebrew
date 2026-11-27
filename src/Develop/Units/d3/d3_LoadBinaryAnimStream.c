#include <string.h>

extern void* g_6b7fdc; extern float g_662c6c; extern float g_6628a4;

void* __cdecl vfs_Tfopen(const char*, const char*, void*);
int __cdecl vfs_ReadData(char*, int, int, void*);
int __cdecl vfs_ReadStreamToken(void*);
int __cdecl fcn_004011f0(void*, void*);
int __cdecl vfs_ReadByte(void*, void*);
void __cdecl vfs_ReadCString(void*, char*);
void __cdecl vfs_ReadVec3(void*, void*);
void* __cdecl m_alloc(unsigned int, const char*);
void __cdecl m_FreeTracked(void*);
void __cdecl ReportClientMessage(const char*);
void __cdecl CloseVfsStream(void*);


/* Chunked binary animation-stream loader.  The returned record is 0x16c
 * bytes; its frame table is v12 entries of 0xc0 bytes. */
/* ADDRESS: GOLDTL 0x0044e1e0 */
char* __cdecl d3_LoadBinaryAnimStream(char* path, char* name, char a2)
{
	int v11;
	int v22;
	int frameCount;
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
	char* stream;
	char* animation;

	v19 = -1;
	v20 = -1;
	v17 = -1;
	v18 = -1;
	frameCount = 0;
	v16 = 1;
	v15 = 0;
	v14 = 0;
	v13 = 1;
	animation = 0;
	stream = (char*) vfs_Tfopen(path, (char*) 0x6750e8, g_6b7fdc);
	v31 = (int) stream;
	if (stream != 0) {
		vfs_ReadData(v10, 4, 1, stream);
		if (vfs_ReadStreamToken(stream) == 0x30) {
			fcn_004011f0(stream, &v11);
			if (vfs_ReadStreamToken(stream) == 1) {
				fcn_004011f0(stream, &v11);
				if ((unsigned int) v11 > 0xabcd0001) {
					CloseVfsStream(stream);
					return 0;
				}
			}
			v3 = vfs_ReadStreamToken(stream);
			if (v3 == 0x23) {
				fcn_004011f0(stream, &frameCount);
				if (frameCount > 0) {
					animation = (char*) m_alloc(0x16c, (char*) 0x67ba68);
					strncpy(animation, name, 0x3f);
					*(int*) (animation + 0x148) = frameCount;
					*(int*) (animation + 0x150) = 0;
					*(char*) (animation + 0x168) = 0;
					*(int*) (animation + 0x154) = frameCount - 1;
					*(char*) (animation + 0x169) = a2;
					*(int*) (animation + 0x15c) = (int) m_alloc(frameCount * 0xc0,
						(char*) 0x67ba2c);
				}
				v3 = vfs_ReadStreamToken(stream);
			}
			if (v3 == 0x33) {
				vfs_ReadByte(stream, &v13);
				v3 = vfs_ReadStreamToken(stream);
			}
			if (v3 == 0x24) {
				vfs_ReadByte(stream, &v14);
				v3 = vfs_ReadStreamToken(stream);
			}
			if (v3 == 0x37) {
				fcn_004011f0(stream, &v15);
				if (animation != 0) {
					*(int*) (animation + 0x144) = v15;
				}
				v3 = vfs_ReadStreamToken(stream);
			}
			if (v3 == 0x36) {
				fcn_004011f0(stream, &v16);
				v3 = vfs_ReadStreamToken(stream);
			}
			if (v3 == 0x34) {
				fcn_004011f0(stream, &v17);
				v3 = vfs_ReadStreamToken(stream);
			}
			if (v3 == 0x35) {
				fcn_004011f0(stream, &v18);
				v3 = vfs_ReadStreamToken(stream);
			}
			if (v3 == 0x29) {
				fcn_004011f0(stream, &v19);
				if (animation != 0) {
					*(int*) (animation + 0x150) = v19;
				}
				v3 = vfs_ReadStreamToken(stream);
			}
			if (v3 == 0x2a) {
				fcn_004011f0(stream, &v20);
				if (animation != 0) {
					*(int*) (animation + 0x154) = v20;
				}
				v3 = vfs_ReadStreamToken(stream);
			}
			if (animation != 0 && *(int*) (animation + 0x150) > *(int*) (animation + 0x154)) {
				v9 = *(int*) (animation + 0x154);
				*(int*) (animation + 0x154) = *(int*) (animation + 0x150);
				*(int*) (animation + 0x150) = v9;
			}
			for (v11 = 0; v11 < frameCount; v11++) {
				v21 = -1;
				v29 = 0;
				for (v30 = 0; v30 < v16; v30++) {
					if (v3 == 0x18) {
						fcn_004011f0(stream, &v21);
						if (animation != 0) {
							*(int*) (v11 * 0xc0
								+ *(int*) (animation + 0x15c)) = v21;
						}
						v3 = vfs_ReadStreamToken(stream);
					}
					v22 = 0;
					if (v13 != 0 && v3 == 0x19) {
						fcn_004011f0(stream, &v22);
						if (animation != 0) {
							if (*(int*) (animation + 0x140) != 0) {
								if (v17 == -1
									&& *(int*) (animation + 0x140) != v22) {
									ReportClientMessage((char*) 0x67b9ec);
								}
							}
							else if (v17 >= 0) {
								*(int*) (animation + 0x140) = v17;
							}
							else {
								*(int*) (animation + 0x140) = v22;
							}
						}
						v3 = vfs_ReadStreamToken(stream);
					}
					if (v3 == 0x21) {
						if (animation != 0 && v29 == 0) {
							if (v17 > 0) {
								v4 = (int) m_alloc(v17 * 0xc,
									(char*) 0x67b9a8);
								*(int*) (v11 * 0xc0 + 0xbc
									+ *(int*) (animation + 0x15c)) = v4;
							}
							else {
								v4 = (int) m_alloc(v22 * 0xc,
									(char*) 0x67b9a8);
								*(int*) (v11 * 0xc0 + 0xbc
									+ *(int*) (animation + 0x15c)) = v4;
							}
						}
						v3 = 0;
						if (v22 > 0) {
							v27 = v29 * 0xc;
							do {
								vfs_ReadVec3(stream, v23);
								if (animation != 0) {
									if (v11 != 0) {
										*(float*) (v27 + *(int*) (v11 * 0xc0
											+ 0xbc + *(int*) (animation + 0x15c)))
											= v23[0] - *(float*) (*(int*) (*(int*) (animation + 0x15c) + 0xbc) + v27);
										*(float*) (*(int*) (v11 * 0xc0
											+ 0xbc + *(int*) (animation + 0x15c)) + 4 + v27)
											= v23[1] - *(float*) (*(int*) (*(int*) (animation + 0x15c) + 0xbc) + 4 + v27);
										*(float*) (*(int*) (v11 * 0xc0
											+ 0xbc + *(int*) (animation + 0x15c)) + 8 + v27)
											= v23[2] - *(float*) (*(int*) (*(int*) (animation + 0x15c) + 0xbc) + 8 + v27);
									}
									else {
										*(float*) (v27 + *(int*) (*(int*) (animation + 0x15c) + 0xbc)) = v23[0];
										*(float*) (*(int*) (*(int*) (animation + 0x15c) + 0xbc) + 4 + v27) = v23[1];
										*(float*) (*(int*) (*(int*) (animation + 0x15c) + 0xbc) + 8 + v27) = v23[2];
									}
								}
								v3++;
								v27 += 0xc;
							} while (v3 < v22);
						}
						v29 += v22;
						v3 = vfs_ReadStreamToken(stream);
						if (v3 != 0x28) {
							ReportClientMessage((char*) 0x67b968);
						}
						else {
							v3 = vfs_ReadStreamToken(stream);
						}
					}
					if (v14 != 0 && v3 == 0x1a) {
						fcn_004011f0(stream, &v24);
						v3 = vfs_ReadStreamToken(stream);
						if (v3 == 0x22) {
							v3 = 0;
							if (v24 > 0) {
								do {
									vfs_ReadVec3(stream, v23);
									vfs_ReadVec3(stream, v25);
									v3++;
								} while (v3 < v24);
							}
							v3 = vfs_ReadStreamToken(stream);
						}
						if (v3 != 0x28) {
							ReportClientMessage((char*) 0x67b92c);
						}
						else {
							v3 = vfs_ReadStreamToken(stream);
						}
					}
				}
				if (v3 == 0x31) {
					vfs_ReadVec3(stream, v23);
					vfs_ReadVec3(stream, v25);
					if (animation != 0) {
						*(float*) (v11 * 0xc0 + 0x20 + *(int*) (animation + 0x15c)) = v23[0];
						*(float*) (v11 * 0xc0 + 0x24 + *(int*) (animation + 0x15c)) = v23[1];
						*(float*) (v11 * 0xc0 + 0x28 + *(int*) (animation + 0x15c)) = v23[2];
						*(float*) (v11 * 0xc0 + 0x2c + *(int*) (animation + 0x15c)) = v25[0];
						*(float*) (v11 * 0xc0 + 0x30 + *(int*) (animation + 0x15c)) = v25[1];
						*(float*) (v11 * 0xc0 + 0x34 + *(int*) (animation + 0x15c)) = v25[2];
					}
					v3 = vfs_ReadStreamToken(stream);
				}
				v9 = 0;
				if (v15 > 0) {
					v29 = (int) (animation + 0x40);
					do {
						if (v3 == 0x38) {
							vfs_ReadCString(stream, (char*) v29);
							v3 = vfs_ReadStreamToken(stream);
						}
						if (v3 == 0x39) {
							vfs_ReadVec3(stream, (void*) (*(int*) (animation + 0x15c)
								+ 0x54 + (v9 + v11 * 8) * 0x18));
							v3 = vfs_ReadStreamToken(stream);
						}
						if (v3 == 0x3a) {
							vfs_ReadVec3(stream, (void*) (*(int*) (animation + 0x15c)
								+ (v9 + 4 + v11 * 8) * 0x18));
							v3 = vfs_ReadStreamToken(stream);
						}
						v9++;
						v29 += 0x40;
					} while (v9 < v15);
				}
			}
			if (v3 == 0x32) {
				vfs_ReadVec3(stream, v23);
				vfs_ReadVec3(stream, v25);
				v3 = vfs_ReadStreamToken(stream);
			}
			if (v3 != 0x2f) {
				ReportClientMessage((char*) 0x67b8e8);
			}
			if (animation != 0) {
				if (v17 >= 0) {
					v22 = v17;
				}
				if (v18 >= 0) {
					v24 = v18;
				}
				if (*(int*) (animation + 0x150) < 0) {
					*(int*) (animation + 0x150) = 0;
				}
				v3 = *(int*) (animation + 0x148);
				if (*(int*) (animation + 0x150) >= v3) {
					*(int*) (animation + 0x150) = v3 - 1;
				}
				if (*(int*) (animation + 0x154) < 0) {
					*(int*) (animation + 0x154) = 0;
				}
				if (*(int*) (animation + 0x154) >= v3) {
					*(int*) (animation + 0x154) = v3 - 1;
				}
				for (v11 = 0; v11 < frameCount - 1; v11++) {
					v4 = v11 * 0xc0 + *(int*) (animation + 0x15c);
					*(int*) (v4 + 4) = *(int*) ((v11 * 3 + 3) * 0x40
						+ *(int*) (animation + 0x15c)) - *(int*) v4;
				}
				v3 = frameCount * 0xc0 + *(int*) (animation + 0x15c);
				*(int*) (v3 - 0xbc) = *(int*) (v3 - 0x17c);
				for (v11 = 1; v11 < frameCount; v11++) {
					v4 = *(int*) (animation + 0x15c);
					*(float*) (v11 * 0xc0 + 0x20 + v4)
						= *(float*) (v11 * 0xc0 + 0x20 + v4)
						- *(float*) (v4 + 0x20);
					v4 = *(int*) (animation + 0x15c);
					*(float*) (v11 * 0xc0 + 0x24 + v4)
						= *(float*) (v11 * 0xc0 + 0x24 + v4)
						- *(float*) (v4 + 0x24);
					v4 = *(int*) (animation + 0x15c);
					*(float*) (v11 * 0xc0 + 0x28 + v4)
						= *(float*) (v11 * 0xc0 + 0x28 + v4)
						- *(float*) (v4 + 0x28);
					v4 = *(int*) (animation + 0x15c);
					*(float*) (v11 * 0xc0 + 0x2c + v4)
						= *(float*) (v11 * 0xc0 + 0x2c + v4)
						- *(float*) (v4 + 0x2c);
					v4 = *(int*) (animation + 0x15c);
					*(float*) (v11 * 0xc0 + 0x30 + v4)
						= *(float*) (v11 * 0xc0 + 0x30 + v4)
						- *(float*) (v4 + 0x30);
					v4 = *(int*) (animation + 0x15c);
					*(float*) (v11 * 0xc0 + 0x34 + v4)
						= *(float*) (v11 * 0xc0 + 0x34 + v4)
						- *(float*) (v4 + 0x34);
				}
				v4 = *(int*) (animation + 0x15c);
				*(int*) (v4 + 0x20) = 0;
				*(int*) (v4 + 0x24) = 0;
				*(int*) (v4 + 0x28) = 0;
				*(int*) (v4 + 0x2c) = 0;
				*(int*) (v4 + 0x30) = 0;
				*(int*) (v4 + 0x34) = 0;
				for (v11 = 0; v11 < *(int*) (animation + 0x140); v11++) {
					*(int*) (*(int*) (*(int*) (animation + 0x15c) + 0xbc)
						+ v11 * 0xc) = 0;
					*(int*) (*(int*) (*(int*) (animation + 0x15c) + 0xbc)
						+ 4 + v11 * 0xc) = 0;
					*(int*) (*(int*) (*(int*) (animation + 0x15c) + 0xbc)
						+ 8 + v11 * 0xc) = 0;
				}
				for (v11 = 0; v11 < frameCount; v11++) {
					if (*(char*) (animation + 0x169) != 0) {
						for (v9 = 0; v9 < *(int*) (animation + 0x140); v9++) {
							v27 = *(int*) (*(int*) (animation + 0x15c) + v11 * 0xc0 + 0xbc);
							*(float*) (v27 + v9 * 0xc)
								= *(float*) (v27 + v9 * 0xc)
								- *(float*) (v11 * 0xc0 + 0x20
								+ *(int*) (animation + 0x15c));
							v27 = *(int*) (*(int*) (animation + 0x15c) + v11 * 0xc0 + 0xbc);
							*(float*) (v27 + 4 + v9 * 0xc)
								= *(float*) (v27 + 4 + v9 * 0xc)
								- *(float*) (v11 * 0xc0 + 0x24
								+ *(int*) (animation + 0x15c));
							v27 = *(int*) (*(int*) (animation + 0x15c) + v11 * 0xc0 + 0xbc);
							*(float*) (v27 + 8 + v9 * 0xc)
								= *(float*) (v27 + 8 + v9 * 0xc)
								- *(float*) (v11 * 0xc0 + 0x28
								+ *(int*) (animation + 0x15c));
						}
						for (v9 = 0; v9 < v15; v9++) {
							v27 = *(int*) (animation + 0x15c);
							*(float*) (v27 + 0x54 + v9 * 0x18)
								= *(float*) (v27 + 0x54 + v9 * 0x18)
								- *(float*) (v11 * 0xc0 + 0x20 + v27);
							v27 = *(int*) (animation + 0x15c);
							*(float*) (v27 + 0x58 + v9 * 0x18)
								= *(float*) (v27 + 0x58 + v9 * 0x18)
								- *(float*) (v11 * 0xc0 + 0x24 + v27);
							v27 = *(int*) (animation + 0x15c);
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
					v28 = g_662c6c;
					if (v22 > 0) {
						v4 = *(int*) (v11 * 0xc0 + 0xbc + *(int*) (animation + 0x15c));
						if (v22 > 0) {
							v9 = v22;
							do {
								if (!(*(float*) v4 > v34)) {
									v34 = *(float*) v4;
								}
								if (!(*(float*) (v4 + 4) > v35)) {
									v35 = *(float*) (v4 + 4);
								}
								if (!(*(float*) (v4 + 8) > v36)) {
									v36 = *(float*) (v4 + 8);
								}
								if (!(*(float*) v4 < v39)) {
									v39 = *(float*) v4;
								}
								if (!(*(float*) (v4 + 4) < v40)) {
									v40 = *(float*) (v4 + 4);
								}
								if (!(v28 > *(float*) (v4 + 8))) {
									v28 = *(float*) (v4 + 8);
								}
								v4 += 0xc;
								v9--;
							} while (v9 != 0);
						}
					}
					*(float*) (v11 * 0xc0 + 8 + *(int*) (animation + 0x15c)) = v34;
					*(float*) (v11 * 0xc0 + 0xc + *(int*) (animation + 0x15c)) = v35;
					*(float*) (v11 * 0xc0 + 0x10 + *(int*) (animation + 0x15c)) = v36;
					v23[0] = v39 - v34;
					v23[1] = v40 - v35;
					v23[2] = v28 - v36;
					*(float*) (v11 * 0xc0 + 0x14 + *(int*) (animation + 0x15c))
						= v23[0] * 0.00392156886f;
					*(float*) (v11 * 0xc0 + 0x18 + *(int*) (animation + 0x15c))
						= v23[1] * 0.00392156886f;
					*(float*) (v11 * 0xc0 + 0x1c + *(int*) (animation + 0x15c))
						= v23[2] * 0.00392156886f;
					v4 = v11 * 0xc0 + 4 + *(int*) (animation + 0x15c);
					*(int*) v4 = *(int*) v4 * 3;
					v4 = (int) m_alloc(v22 * 3, (char*) 0x67b8a0);
					v30 = 0;
					*(int*) (v11 * 0xc0 + 0xb4 + *(int*) (animation + 0x15c)) = v4;
					if (v22 > 0) {
						stream = 0;
						v29 = 0;
						do {
							v27 = v11 * 0xc0;
							v25[0] = *(float*) (*(int*) (*(int*) (animation + 0x15c) + 0xbc + v27) + (int) stream) - v34;
							v25[1] = *(float*) (*(int*) (*(int*) (animation + 0x15c) + 0xbc + v27) + 4 + (int) stream) - v35;
							v25[2] = *(float*) (*(int*) (*(int*) (animation + 0x15c) + 0xbc + v27) + 8 + (int) stream) - v36;
							*(char*) (v29 + *(int*) (*(int*) (animation + 0x15c) + 0xb4 + v27))
								= (char) (int) (v25[0] * g_6628a4 / v23[0]);
							*(char*) (*(int*) (v11 * 0xc0 + 0xb4 + *(int*) (animation + 0x15c)) + 1 + v29)
								= (char) (int) (v25[1] * g_6628a4 / v23[1]);
							stream = (char*) ((int) stream + 0xc);
							v29 += 3;
							*(char*) (*(int*) (v11 * 0xc0 + 0xb4 + *(int*) (animation + 0x15c)) + -1 + v29)
								= (char) (int) (v25[2] * g_6628a4 / v23[2]);
							v30++;
						} while (v30 < v22);
						stream = (char*) v31;
					}
					m_FreeTracked((void*) *(int*) (v11 * 0xc0 + 0xbc
						+ *(int*) (animation + 0x15c)));
					*(int*) (v11 * 0xc0 + 0xbc + *(int*) (animation + 0x15c)) = 0;
				}
			}
		}
		CloseVfsStream(stream);
	}
	return animation;
}
