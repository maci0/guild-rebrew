typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
#include <string.h>
/* ADDRESS: GOLDTL 0x0047a990 */
unsigned int __cdecl d2_BlitRgb24ShapeToSurface(int x, int y, char* shape, char* surface)
{
	u32* v1;
	u16 v10;
	u16* v11;
	int v12;
	int* v13;
	u16 words[0x480];
	u32* v15;
	int loopIndex;

	u16* v18;

	int v20;
	int v21;


	u8 v5;
	u8 v6;
	u8 v7;
	int v8;
	u8* v9;

	if (*(int*) (shape + 0x26) != -1) {
		v8 = 0;
		v13 = (int*) (shape + 0x32);
		v15 = (u32*) (shape + 0x36);
		if (*(u16*) (shape + 10) > 0) {
			do {
				v21 = 0;
				v11 = (u16*) (*(int*) (surface + 0x1c) + ((v8 + y) * *(int*) (surface + 0x10) + x) * 2);
				if (*v13 > 0) {
					do {
						for (loopIndex = 0; loopIndex < (int) (*v15 / 3); loopIndex++) {
							*v11 = 0;
						}
						loopIndex = 0;
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
								words[loopIndex] = v10;
								if (!v10) {
									words[loopIndex] = 0x421;
								}
								words[loopIndex] |= 0x8000;
								loopIndex += 1;
								v9 = v9 + 3;
							} while (loopIndex < (int) v15[1]);
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
			} while (v8 < (int) *(u16*) (shape + 10));
			return 1;
		}
		return 1;
	}
	v20 = *(u16*) (shape + 10);
	v8 = *(u16*) (shape + 6);
	v18 = (u16*) (*(int*) (surface + 0x1c) + (*(int*) (surface + 0x10) * y + x) * 2);
	v9 = (u8*) (shape + 0x32);
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
			v18 = v18 + *(int*) (surface + 0x10) - v8;
			v20 -= 1;
		} while (v20);
		return 1;
	}
	return 1;
}
