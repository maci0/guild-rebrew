#include "Develop/DieGildeAddOn/game/head_set.h"





extern HEAD_SET g_6918e8[];


int __cdecl gm_RandomMod(unsigned short n);
void __cdecl fcn_004fdd70(HEAD_SET* hs);

/* ADDRESS: GOLDTL 0x004fda30 */
HEAD_SET* __cdecl gm_SelectEntityHeadSet(unsigned int entityIndex)
{
	char* srcName;
	HEAD_SET* headSet;
	int* headEntry;
	int entOff;
	int idx;
	int portraitId;
	unsigned char roleId;
	char ch;

	headSet = 0;
	idx = 0;
	entOff = entityIndex * 0x21c;
	roleId = *(unsigned char*) (entOff + 0x7f4e04);
	if (!roleId && *(unsigned short*) (entOff + 0x7f4caa) < *(float*) (entOff + 0x7f4cc0)) {
		if (*(char*) (entOff + 0x7f4ca9)) {
			return (HEAD_SET*) 0x690600;
		}
		return (HEAD_SET*) 0x6905b8;
	}
	srcName = (char*) (entOff + 0x7f4e94);
	if (*(char*) (entOff + 0x7f4e94) && (portraitId = *(int*) (entOff + 0x7f4e2c)) != -1) {
		*(int*) 0x773d60 = (*(int*) 0x773d60 + 1) & 0x80000007;
		if (*(int*) 0x773d60 <= -1) {
			*(int*) 0x773d60 = (*(int*) 0x773d60 - 1 | 0xfffffff8) + 1;
		}
		entOff = *(int*) 0x773d60 * 0x44;
		idx = entOff - (int) srcName;
		do {
			ch = *srcName;
			srcName[idx + 0x99ed64] = ch;
			srcName = srcName + 1;
		} while (ch);
		portraitId -= 0x639;
		*(int*) (entOff + 0x99ed94) = portraitId;
		*(int*) (entOff + 0x99ed98) = portraitId;
		*(int*) (entOff + 0x99ed9c) = portraitId;
		*(int*) (entOff + 0x99eda0) = portraitId;
		return (HEAD_SET*) (entOff + 0x99ed60);
	}
	if (*(char*) (entOff + 0x7f4ca2) == 0x11) {
		return (HEAD_SET*) ((unsigned short) gm_RandomMod(3) * 0x44 + 0x6960a8);
	}
	if (roleId) {
		if (*(char*) (entOff + 0x7f4ca9)) {
			if (*(char*) (entOff + 0x7f4ca9) == 1) {
				headSet = (HEAD_SET*) 0x693228;
			}
		} else {
			headSet = g_6918e8;
		}
		headEntry = (int*) headSet;
		do {
			if (*headEntry == 0) {
				break;
			}
			if (*headEntry == roleId) {
				fcn_004fdd70(&headSet[idx]);
				return &headSet[idx];
			}
			idx++;
			headEntry = &headEntry[0x11];
		} while (idx < 0x5f);
		return &headSet[idx];
	}
	if (*(unsigned char*) (entOff + 0x7f4e05)) {
		if (*(char*) (entOff + 0x7f4ca9)) {
			if (*(char*) (entOff + 0x7f4ca9) == 1) {
				headSet = (HEAD_SET*) 0x690f98;
			}
		} else {
			headSet = (HEAD_SET*) 0x690648;
		}
		headEntry = (int*) headSet;
		do {
			if (*headEntry == 0) {
				if (idx <= 0x22) {
					return &headSet[idx];
				}
				break;
			}
			if (*headEntry == *(unsigned char*) (entOff + 0x7f4e05)) {
				fcn_004fdd70(&headSet[idx]);
				return &headSet[idx];
			}
			idx++;
			headEntry = &headEntry[0x11];
		} while (idx < 0x23);
	}
	if (!*(char*) (entOff + 0x7f4ca9)) {
		return (HEAD_SET*) 0x690648;
	}
	if (*(char*) (entOff + 0x7f4ca9) != 1) {
		return headSet;
	}
	return (HEAD_SET*) 0x690f98;
}
