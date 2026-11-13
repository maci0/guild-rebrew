#include <string.h>
#include "game_data.h"
void* __cdecl gm_StartFilteredEntitySearch(int a1, int a2, int a3);
int __cdecl fcn_004fa6f0(char* a1, int* a2, int* a3);
void __cdecl fcn_004f4830(unsigned char a1, char* a2);

/* ADDRESS: GOLDTL 0x004fad10 */
void __cdecl fcn_004fad10(void)
{
	int* v4;
	int* v12;
	int* v22;




	unsigned char record[0x2d];
	int v14;
	int v15;
	int v8;
	int v19;
	int v9;
	int v10;
	int v11;





	int stats[9];
	unsigned char v3;
	unsigned int* v5;
	float v20;
	float v21;
	float* v6;
	float* v7;

	v4 = (int*) 0x99ef8c;
	do {
		v8 = 8;
		do {
			v4[1] = 0;
			*v4 = 0;
			v4[2] = 0;
			v4 = (int*) ((char*) v4 + 0x18);
			v8 -= 1;
		} while (v8);
	} while ((int) v4 < 0x99f58c);
	v12 = (int*) 0x9a3800;
	v22 = (int*) 0x9a3800;
	do {
		if (*(int*) ((char*) v12 + 0x25) != 0 && *v12 != -1) {
			memcpy(record, v12, 0x2d);
			v5 = (unsigned int*) gm_StartFilteredEntitySearch(1, 1, *(int*) (record + 0x21));
			if (v5 != 0 && *(unsigned char*) v5 != 0) {
				v8 = *(int*) ((char*) v5 + 0x61);
				if (v8 != 0) {
					v3 = *(unsigned char*) (lpGebaeudePROT + *(unsigned char*) v5 * 0x24d);
					if ((v3 < 0xb || v3 >= 0xe) && v3 != 0x10) {
						if (fcn_004fa6f0((char*) v8 + 0x4c, &v15, &v14) != 0) {
							fcn_004f4830(record[0x1c], (char*) stats);
							v8 = v14 + v15 * 8;
							v20 = (float) *(short*) (record + 0x1a) / (float) stats[4] * (float) stats[3];
							v21 = v20 * *(float*) 0x6628cc;
							*(float*) (v8 * 0x18 + 0x99ef8c) = v21 + *(float*) (v8 * 0x18 + 0x99ef8c);
							v8 = v15 + 1 <= 8 ? v15 + 1 : 8;
							v19 = v14 + 1 >= 9 ? 8 : v14 + 1;
							v9 = (unsigned int) (v15 - 1 < 0) - 1 & (unsigned int) (v15 - 1);
							if ((int) v9 <= v8) {
								do {
									v11 = (unsigned int) (v14 - 1 < 0) - 1 & (unsigned int) (v14 - 1);
									if ((int) v11 <= v19) {
										v10 = (v19 - v11) + 1;
										v6 = (float*) ((v11 + v9 * 8) * 0x18 + 0x99ef8c);
										do {
											v7 = v6 + 6;
											v10 -= 1;
											v6[1] = v20 + v6[1];
											*v6 = v21 + *v6;
											v6 = v7;
										} while (v10);
									}
									v9 += 1;
								} while ((int) v9 <= v8);
							}
							v12 = v22;
						}
					}
				}
			}
		}
		v12 = (int*) ((char*) v12 + 0x2d);
		v22 = v12;
	} while ((int) v12 < 0x9a9200);
}
