typedef struct {
	unsigned char a;
	unsigned char b;
	unsigned char c0 : 1;
	unsigned char c1 : 1;
	unsigned char c2 : 6;
	unsigned char d;
} Col44f250;

void* __cdecl m_alloc(int size, char* tag);
void* __cdecl vfs_OpenFastChunk(unsigned int a0);
char* __cdecl fcn_0064d530(char* dest, char* src, int count);
void __cdecl fcn_004011f0(void* a0, void* a1);
void __cdecl vfs_ReadCString(void* a0, char* a1);
void __cdecl vfs_ReadByte(void* a0, void* a1);
void __cdecl fcn_004011d0(void* a0, void* a1);
void __cdecl vfs_ReadVec3(void* a0, void* a1);
void* __cdecl d3_LoadOrReuseTexture(void* a0, Col44f250 a1, unsigned int a2, unsigned int a3);
void __cdecl CloseVfsStream(void* a0);

extern char* g_104049c;

/* ADDRESS: GOLDTL 0x0044f250 */
int __cdecl d3_LoadFastChunk(unsigned int a0, unsigned int a1, int a2, int a3, int a4)
{
	unsigned char* chunk;
	void* inputStream;
	int v10;
	int v11;
	int v25;
	int v28;
	float v14[3];
	unsigned int v15;
	char v16[64];
	char v17[64];
	char v18[64];
	unsigned char v19;
	unsigned char v20;
	unsigned char v21;
	unsigned int v22;
	unsigned char v23;
	unsigned char v24[23];
	Col44f250 v27;
	unsigned char v31;
	unsigned char v32;
	unsigned char v33;
	unsigned char v3;
	char* v6;
	char* s;
	char* d;

	chunk = 0;
	v3 = 0;
	inputStream = vfs_OpenFastChunk(a0);
	if (inputStream != 0) {
		chunk = (unsigned char*)m_alloc(0x2a4, "d3_io_fl:LoadFastChunk(obj)");
		fcn_0064d530((char*)chunk, (char*)a1, 0x3f);
		fcn_004011f0(inputStream, chunk + 0x1e4);
		fcn_004011f0(inputStream, chunk + 0x44);
		fcn_004011f0(inputStream, chunk + 0x4c);
		v11 = *(int*)(chunk + 0x44);
		if (v11 > 0) {
			*(unsigned int*)(chunk + 0x40) = (unsigned int)m_alloc((v11 * 3 + 0x18) * 8, "d3_io_fl:LoadFastChunk(pol)");
			v28 = 0;
			if (v11 + 8 > 0) {
				do {
					vfs_ReadVec3(inputStream, (void*)(*(int*)(chunk + 0x40) + v28 * 0x18));
					vfs_ReadVec3(inputStream, (void*)(*(int*)(chunk + 0x40) + v28 * 0x18 + 0xc));
					v28 += 1;
				} while (v28 < *(int*)(chunk + 0x44) + 8);
			}
		}
		fcn_004011d0(inputStream, chunk + 0x1d4);
		v11 = *(int*)(chunk + 0x4c);
		*(unsigned int*)(chunk + 0x48) = (unsigned int)m_alloc(v11 * 0x38, "d3_io_fl:LoadFastChunk(poi)");
		v11 = 0;
		if (*(int*)(chunk + 0x4c) > 0) {
			do {
				v10 = v11 * 0x38;
				fcn_004011f0(inputStream, (void*)(v10 + 0x18 + *(int*)(chunk + 0x48)));
				fcn_004011f0(inputStream, (void*)(v10 + 0x1c + *(int*)(chunk + 0x48)));
				fcn_004011f0(inputStream, (void*)(v10 + 0x20 + *(int*)(chunk + 0x48)));
				vfs_ReadVec3(inputStream, v14);
				*(float*)(v10 + *(int*)(chunk + 0x48)) = v14[0];
				*(float*)(v10 + 8 + *(int*)(chunk + 0x48)) = v14[1];
				*(float*)(v10 + 0x10 + *(int*)(chunk + 0x48)) = v14[2];
				vfs_ReadVec3(inputStream, v14);
				*(float*)(v10 + 4 + *(int*)(chunk + 0x48)) = v14[0];
				*(float*)(v10 + 0xc + *(int*)(chunk + 0x48)) = v14[1];
				*(float*)(v10 + 0x14 + *(int*)(chunk + 0x48)) = v14[2];
				vfs_ReadVec3(inputStream, (void*)(v10 + 0x2c + *(int*)(chunk + 0x48)));
				*(unsigned int*)(v10 + 0x24 + *(int*)(chunk + 0x48)) = 0xffffffff;
				if (*(int*)(chunk + 0x1e4) > 0xfe) {
					fcn_004011f0(inputStream, (void*)(v10 + 0x28 + *(int*)(chunk + 0x48)));
				} else {
					vfs_ReadByte(inputStream, &v15);
					if ((v15 & 0xff) != 0xff) {
						*(unsigned int*)(v10 + 0x28 + *(int*)(chunk + 0x48)) = v15 & 0xff;
					} else {
						*(unsigned int*)(v10 + 0x28 + *(int*)(chunk + 0x48)) = 0xffffffff;
					}
				}
				v11 += 1;
			} while (v11 < *(int*)(chunk + 0x4c));
		}
		if ((a2 != 0) && (a3 > 0) && (a4 == *(int*)(chunk + 0x1e4))) {
			*(int*)(chunk + 0x1e8) = a3;
			*(int*)(chunk + 0x200) = a2;
			v3 = 1;
		} else {
			v10 = *(int*)(chunk + 0x1e4);
			*(unsigned int*)(chunk + 0x1e8) = 1;
			*(unsigned int*)(chunk + 0x200) = (unsigned int)m_alloc(v10 << 6, "d3_io_fl:LoadFastChunk(texset)");
		}
		v28 = 0;
		if (*(int*)(chunk + 0x1e4) > 0) {
			v6 = (char*)v15;
			do {
				v10 = v28 * 0x40;
				vfs_ReadCString(inputStream, v16);
				vfs_ReadCString(inputStream, v17);
				vfs_ReadCString(inputStream, v18);
				vfs_ReadByte(inputStream, &v19);
				vfs_ReadByte(inputStream, &v20);
				vfs_ReadByte(inputStream, &v21);
				vfs_ReadByte(inputStream, &v22);
				vfs_ReadByte(inputStream, &v23);
				vfs_ReadByte(inputStream, v24);
				*(unsigned int*) &v27 = 0; v27.a = 0xff;
				if (v19 != 0) {
					v27.a = v20;
					if (v19 == 2) {
						v27.c0 = 1;
					}
				}
				v27.c1 = v21 & 1;
				v31 = (unsigned char)(((unsigned int)v21 >> 6) & 1);
				v32 = (unsigned char)(((unsigned int)v21 >> 1) & 1);
				v33 = (unsigned char)(((unsigned int)v21 >> 2) & 0xf);
				if (v17[0] != 0) {
					if (!v3) {
						s = v17;
						d = (char*)(*(int*)(chunk + 0x200) + v10);
						do {
							*d = *s;
							s += 1;
							d += 1;
						} while (*(d - 1) != 0);
					}
					v6 = (char*)d3_LoadOrReuseTexture((void*)(*(int*)(chunk + 0x200) + v10), v27, (((((unsigned int)v31 << 4) | (unsigned int)v33) << 1) | (unsigned int)v32) << 1 | 1,
					    ((unsigned int)v23 << 4) | (unsigned int)v24[0]);
				} else if (v16[0] != 0) {
					if (!v3) {
						s = v16;
						d = (char*)(*(int*)(chunk + 0x200) + v10);
						do {
							*d = *s;
							s += 1;
							d += 1;
						} while (*(d - 1) != 0);
					}
					v6 = (char*)d3_LoadOrReuseTexture((void*)(*(int*)(chunk + 0x200) + v10), v27, (((((unsigned int)v31 << 4) | (unsigned int)v33) << 1) | (unsigned int)v32) << 1,
					    ((unsigned int)v23 << 4) | (unsigned int)v24[0]);
				} else if ((v18[0] != 0) && (!v3)) {
					s = v18;
					d = (char*)(*(int*)(chunk + 0x200) + v10);
					do {
						*d = *s;
						s += 1;
						d += 1;
					} while (*(d - 1) != 0);
				}
				if (v6 != 0) {
					v25 = (int)(v6 - g_104049c) / 0x70;
				} else {
					v25 = -1;
				}
				v10 = 0;
				if (*(int*)(chunk + 0x4c) > 0) {
					do {
						v11 = *(int*)(chunk + 0x48) + v10 * 0x38;
						if (*(int*)(v11 + 0x28) == v28) {
							*(int*)(v11 + 0x24) = v25;
						}
						v10 += 1;
					} while (v10 < *(int*)(chunk + 0x4c));
				}
				v28 += 1;
			} while (v28 < *(int*)(chunk + 0x1e4));
		}
		fcn_004011f0(inputStream, &v25);
		*(char*)(chunk + 0x2a0) = (char)(v25 & 0xff);
		v11 = 0;
		if (v25 > 0) {
			v10 = (int)(chunk + 0xb4);
			do {
				vfs_ReadCString(inputStream, (char*)(v10 - 0x40));
				vfs_ReadVec3(inputStream, (void*)v10);
				vfs_ReadVec3(inputStream, (void*)(v10 + 0xc));
				v11 += 1;
				v10 += 0x58;
			} while (v11 < v25);
		}
		CloseVfsStream(inputStream);
	}
	return (int)chunk;
}
