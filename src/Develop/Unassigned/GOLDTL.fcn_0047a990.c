typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
#include <string.h>
/* ADDRESS: GOLDTL 0x0047a990 */
unsigned int __cdecl fcn_0047a990(int a0, int a1, char* a2, char* a3)
{
	u32* v1;
	u16 v10;
	u16* v11;
	int v12;
	int* v13;
	u16 words[0x480];
	u32* v15;
	int v16;

	u16* v18;

	int v20;
	int v21;


	u8 v5;
	u8 v6;
	u8 v7;
	int v8;
	u8* v9;

	if (*(int*) (a2 + 0x26) != -1) {
		v8 = 0;
		v13 = (int*) (a2 + 0x32);
		v15 = (u32*) (a2 + 0x36);
		if (*(u16*) (a2 + 10) > 0) {
			do {
				v21 = 0;
				v11 = (u16*) (*(int*) (a3 + 0x1c) + ((v8 + a1) * *(int*) (a3 + 0x10) + a0) * 2);
				if (*v13 > 0) {
					do {
						for (v16 = 0; v16 < (int) (*v15 / 3); v16++) {
							*v11 = 0;
						}
						v16 = 0;
						v1 = (u32*) ((int) v11 + ((*v15 / 3) * 2));
						if ((int) v15[1] > 0) {
							v9 = (u8*) ((int) v15 + 10);
							do {
								v5 = v9[-2];
								v6 = v9[-1];
								v9[-2] = v5 >> 3;
								v7 = *v9;
								v9[-1] = v6 >> 3;
								*v9 = v7 >> 3;
								v10 = (u16) (((u16) (v5 >> 3) << 5 | (u16) (v6 >> 3)) << 5 | (u16) (v7 >> 3));
								words[v16] = v10;
								if (!v10) {
									words[v16] = 0x421;
								}
								words[v16] |= 0x8000;
								v16 += 1;
								v9 = v9 + 3;
							} while (v16 < (int) v15[1]);
						}
						memcpy(v1, words, v15[1] * 2);
						v11 = (u16*) ((int) v1 + v15[1] * 2);
						v15 = (u32*) ((int) v15 + v15[1] * 3 + 8);
						v21 += 1;
					} while (v21 < *v13);
				}
				v13 = (int*) v15;
				v15 = (u32*) (v13 + 1);
				v8 += 1;
			} while (v8 < (int) *(u16*) (a2 + 10));
			return 1;
		}
		return 1;
	}
	v20 = *(u16*) (a2 + 10);
	v8 = *(u16*) (a2 + 6);
	v18 = (u16*) (*(int*) (a3 + 0x1c) + (*(int*) (a3 + 0x10) * a1 + a0) * 2);
	v9 = (u8*) (a2 + 0x32);
	if (v20 > 0) {
		do {
			if (v8 > 0) {
				v12 = v8;
				do {
					if ((*v9) || (v9[1])) {
						v5 = v9[1];
						v6 = v9[2];
						v7 = *v9 >> 3;
						*v9 = v7;
						v9[1] = v5 >> 3;
						v9[2] = v6 >> 3;
						v10 = (u16) (((u16) v7 << 5 | (u16) (v5 >> 3)) << 5 | (u16) (v6 >> 3));
						*v18 = v10;
						if (!v10) {
							*v18 = 0x421;
						}
						*(u8*) ((int) v18 + 1) = *(u8*) ((int) v18 + 1) | 0x80;
					}
					v18 = v18 + 1;
					v9 = v9 + 3;
					v12 -= 1;
				} while (v12);
			}
			v18 = v18 + *(int*) (a3 + 0x10) - v8;
			v20 -= 1;
		} while (v20);
		return 1;
	}
	return 1;
}
