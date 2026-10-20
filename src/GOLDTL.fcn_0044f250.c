void* __cdecl m_alloc(int size, char* tag);
void* __cdecl fcn_0044f190(unsigned int a0);
char* __cdecl fcn_0064d530(char* dest, char* src, int count);
void __cdecl fcn_004011f0(void* a0, void* a1);
void __cdecl fcn_004011a0(void* a0, char* a1);
void __cdecl fcn_00401180(void* a0, void* a1);
void __cdecl fcn_004011d0(void* a0, void* a1);
void __cdecl fcn_00401280(void* a0, void* a1);
void* __cdecl fcn_0045c5b0(void* a0, unsigned int a1, unsigned int a2, unsigned int a3);
void __cdecl fcn_00430580(void* a0);

extern char* g_104049c;

/* ADDRESS: GOLDTL 0x0044f250 */
int __cdecl fcn_0044f250(unsigned int a0, unsigned int a1, int a2, int a3, int a4)
{
	unsigned char* v26;
	void* v4;
	int v10;
	int v11;
	int v25;
	int v28;
	unsigned int v14[3];
	unsigned int v15;
	char v16[64];
	char v17[64];
	char v18[64];
	unsigned char v19;
	unsigned char v20;
	unsigned char v21;
	unsigned int v22;
	unsigned char v23;
	char v24[23];
	unsigned int v27;
	unsigned char v31;
	unsigned char v32;
	unsigned char v33;
	unsigned char v3;
	char* v6;
	char* s;
	char* d;

	v26 = 0;
	v3 = 0;
	v4 = fcn_0044f190(a0);
	if (v4 != 0) {
		v26 = (unsigned char*)m_alloc(0x2a4, "d3_io_fl:LoadFastChunk(obj)");
		fcn_0064d530((char*)v26, (char*)a1, 0x3f);
		fcn_004011f0(v4, v26 + 0x1e4);
		fcn_004011f0(v4, v26 + 0x44);
		fcn_004011f0(v4, v26 + 0x4c);
		v11 = *(int*)(v26 + 0x44);
		if (v11 >= 1) {
			*(unsigned int*)(v26 + 0x40) = (unsigned int)m_alloc((v11 * 3 + 0x18) * 8, "d3_io_fl:LoadFastChunk(pol)");
			v28 = 0;
			if (v11 + 8 > 0) {
				do {
					fcn_00401280(v4, (void*)(*(int*)(v26 + 0x40) + v28 * 0x18));
					fcn_00401280(v4, (void*)(*(int*)(v26 + 0x40) + v28 * 0x18 + 0xc));
					v28 += 1;
				} while (v28 < *(int*)(v26 + 0x44) + 8);
			}
		}
		fcn_004011d0(v4, v26 + 0x1d4);
		v11 = *(int*)(v26 + 0x4c);
		*(unsigned int*)(v26 + 0x48) = (unsigned int)m_alloc(v11 * 0x38, "d3_io_fl:LoadFastChunk(poi)");
		v11 = 0;
		if (*(int*)(v26 + 0x4c) >= 1) {
			do {
				v10 = v11 * 0x38;
				fcn_004011f0(v4, (void*)(v10 + 0x18 + *(int*)(v26 + 0x48)));
				fcn_004011f0(v4, (void*)(v10 + 0x1c + *(int*)(v26 + 0x48)));
				fcn_004011f0(v4, (void*)(v10 + 0x20 + *(int*)(v26 + 0x48)));
				fcn_00401280(v4, v14);
				*(unsigned int*)(v10 + *(int*)(v26 + 0x48)) = v14[0];
				*(unsigned int*)(v10 + 8 + *(int*)(v26 + 0x48)) = v14[1];
				*(unsigned int*)(v10 + 0x10 + *(int*)(v26 + 0x48)) = v14[2];
				fcn_00401280(v4, v14);
				*(unsigned int*)(v10 + 4 + *(int*)(v26 + 0x48)) = v14[0];
				*(unsigned int*)(v10 + 0xc + *(int*)(v26 + 0x48)) = v14[1];
				*(unsigned int*)(v10 + 0x14 + *(int*)(v26 + 0x48)) = v14[2];
				fcn_00401280(v4, (void*)(v10 + 0x2c + *(int*)(v26 + 0x48)));
				*(unsigned int*)(v10 + 0x24 + *(int*)(v26 + 0x48)) = 0xffffffff;
				if (*(int*)(v26 + 0x1e4) >= 0xff) {
					fcn_004011f0(v4, (void*)(v10 + 0x28 + *(int*)(v26 + 0x48)));
				} else {
					fcn_00401180(v4, &v15);
					if ((v15 & 0xff) != 0xff) {
						*(unsigned int*)(v10 + 0x28 + *(int*)(v26 + 0x48)) = v15 & 0xff;
					} else {
						*(unsigned int*)(v10 + 0x28 + *(int*)(v26 + 0x48)) = 0xffffffff;
					}
				}
				v11 += 1;
			} while (v11 < *(int*)(v26 + 0x4c));
		}
		if ((a2 != 0) && (a3 >= 1) && (a4 == *(int*)(v26 + 0x1e4))) {
			*(int*)(v26 + 0x1e8) = a3;
			*(int*)(v26 + 0x200) = a2;
			v3 = 1;
		} else {
			v10 = *(int*)(v26 + 0x1e4);
			*(unsigned int*)(v26 + 0x1e8) = 1;
			*(unsigned int*)(v26 + 0x200) = (unsigned int)m_alloc(v10 << 6, "d3_io_fl:LoadFastChunk(texset)");
		}
		v28 = 0;
		if (*(int*)(v26 + 0x1e4) >= 1) {
			v6 = (char*)v15;
			do {
				v10 = v28 * 0x40;
				fcn_004011a0(v4, v16);
				fcn_004011a0(v4, v17);
				fcn_004011a0(v4, v18);
				fcn_00401180(v4, &v19);
				fcn_00401180(v4, &v20);
				fcn_00401180(v4, &v21);
				fcn_00401180(v4, &v22);
				fcn_00401180(v4, &v23);
				fcn_00401180(v4, v24);
				v27 = 0xff;
				if (v19 != 0) {
					v27 = (v27 & 0xffffff00u) | ((unsigned int)v20 & 0xff);
					if (v19 == 2) {
						v27 |= 0x00010000u;
					}
				}
				v27 = (v27 & 0xfffdffffu) | (((unsigned int)v21 & 1u) << 17);
				v31 = (unsigned char)(((unsigned int)v21 >> 6) & 1);
				v32 = (unsigned char)(((unsigned int)v21 >> 1) & 1);
				v33 = (unsigned char)(((unsigned int)v21 >> 2) & 0xf);
				if (v17[0] != 0) {
					if (!v3) {
						s = v17;
						d = (char*)(*(int*)(v26 + 0x200) + v10);
						do {
							*d = *s;
							s += 1;
							d += 1;
						} while (*(d - 1) != 0);
					}
					v6 = (char*)fcn_0045c5b0((void*)(*(int*)(v26 + 0x200) + v10), v27, (((((unsigned int)v31 << 4) | (unsigned int)v33) << 1) | (unsigned int)v32) << 1 | 1, ((unsigned int)v23 << 4) | (unsigned int)v24[0]);
				} else if (v16[0] != 0) {
					if (!v3) {
						s = v16;
						d = (char*)(*(int*)(v26 + 0x200) + v10);
						do {
							*d = *s;
							s += 1;
							d += 1;
						} while (*(d - 1) != 0);
					}
					v6 = (char*)fcn_0045c5b0((void*)(*(int*)(v26 + 0x200) + v10), v27, (((((unsigned int)v31 << 4) | (unsigned int)v33) << 1) | (unsigned int)v32) << 1, ((unsigned int)v23 << 4) | (unsigned int)v24[0]);
				} else if ((v18[0] != 0) && (!v3)) {
					s = v18;
					d = (char*)(*(int*)(v26 + 0x200) + v10);
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
				if (*(int*)(v26 + 0x4c) >= 1) {
					do {
						v11 = *(int*)(v26 + 0x48) + v10 * 0x38;
						if (*(int*)(v11 + 0x28) == v28) {
							*(int*)(v11 + 0x24) = v25;
						}
						v10 += 1;
					} while (v10 < *(int*)(v26 + 0x4c));
				}
				v28 += 1;
			} while (v28 < *(int*)(v26 + 0x1e4));
		}
		fcn_004011f0(v4, &v25);
		*(char*)(v26 + 0x2a0) = (char)(v25 & 0xff);
		v11 = 0;
		if (v25 >= 1) {
			v10 = (int)(v26 + 0xb4);
			do {
				fcn_004011a0(v4, (char*)(v10 - 0x40));
				fcn_00401280(v4, (void*)v10);
				fcn_00401280(v4, (void*)(v10 + 0xc));
				v11 += 1;
				v10 += 0x58;
			} while (v11 < v25);
		}
		fcn_00430580(v4);
	}
	return (int)v26;
}
