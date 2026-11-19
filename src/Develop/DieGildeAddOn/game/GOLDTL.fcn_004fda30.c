#include "Develop/DieGildeAddOn/game/head_set.h"





extern HEAD_SET g_6918e8[];


int __cdecl gm_RandomMod(unsigned short n);
void __cdecl fcn_004fdd70(HEAD_SET* hs);

/* ADDRESS: GOLDTL 0x004fda30 */
HEAD_SET* __cdecl fcn_004fda30(unsigned int entityIndex)
{
	char* v4;
	HEAD_SET* headSet;
	int* headEntry;
	int v3;
	int v5;
	int v8;
	unsigned char v1;
	char v2;

	headSet = 0;
	v5 = 0;
	v3 = entityIndex * 0x21c;
	v1 = *(unsigned char*) (v3 + 0x7f4e04);
	if (!v1 && *(unsigned short*) (v3 + 0x7f4caa) < *(float*) (v3 + 0x7f4cc0)) {
		if (*(char*) (v3 + 0x7f4ca9)) {
			return (HEAD_SET*) 0x690600;
		}
		return (HEAD_SET*) 0x6905b8;
	}
	v4 = (char*) (v3 + 0x7f4e94);
	v8 = *(int*) (v3 + 0x7f4e2c);
	if (*(char*) (v3 + 0x7f4e94) && v8 != -1) {
		*(int*) 0x773d60 = (*(int*) 0x773d60 + 1) & 0x80000007;
		if (*(int*) 0x773d60 <= -1) {
			*(int*) 0x773d60 = (*(int*) 0x773d60 - 1 | 0xfffffff8) + 1;
		}
		v3 = *(int*) 0x773d60 * 0x44;
		v5 = v3 - (int) v4;
		do {
			v2 = *v4;
			v4[v5 + 0x99ed64] = v2;
			v4 = v4 + 1;
		} while (v2);
		v8 -= 0x639;
		*(int*) (v3 + 0x99ed94) = v8;
		*(int*) (v3 + 0x99ed98) = v8;
		*(int*) (v3 + 0x99ed9c) = v8;
		*(int*) (v3 + 0x99eda0) = v8;
		return (HEAD_SET*) (v3 + 0x99ed60);
	}
	if (*(char*) (v3 + 0x7f4ca2) == 0x11) {
		return (HEAD_SET*) ((unsigned short) gm_RandomMod(3) * 0x44 + 0x6960a8);
	}
	if (v1) {
		if (*(char*) (v3 + 0x7f4ca9)) {
			if (*(char*) (v3 + 0x7f4ca9) == 1) {
				headSet = (HEAD_SET*) 0x693228;
			}
		} else {
			headSet = (HEAD_SET*) 0x6918e8;
		}
		headEntry = (int*) headSet;
		do {
			if (*headEntry == 0) {
				break;
			}
			if (*headEntry == v1) {
				fcn_004fdd70(&headSet[v5]);
				return &headSet[v5];
			}
			v5++;
			headEntry = &headEntry[0x11];
		} while (v5 < 0x5f);
		return &headSet[v5];
	}
	if (*(unsigned char*) (v3 + 0x7f4e05)) {
		if (*(char*) (v3 + 0x7f4ca9)) {
			if (*(char*) (v3 + 0x7f4ca9) == 1) {
				headSet = (HEAD_SET*) 0x690f98;
			}
		} else {
			headSet = (HEAD_SET*) 0x690648;
		}
		headEntry = (int*) headSet;
		do {
			if (*headEntry == 0) {
				if (v5 <= 0x22) {
					return &headSet[v5];
				}
				break;
			}
			if (*headEntry == *(unsigned char*) (v3 + 0x7f4e05)) {
				fcn_004fdd70(&headSet[v5]);
				return &headSet[v5];
			}
			v5++;
			headEntry = &headEntry[0x11];
		} while (v5 < 0x23);
	}
	if (!*(char*) (v3 + 0x7f4ca9)) {
		return (HEAD_SET*) 0x690648;
	}
	if (*(char*) (v3 + 0x7f4ca9) != 1) {
		return headSet;
	}
	return (HEAD_SET*) 0x690f98;
}
