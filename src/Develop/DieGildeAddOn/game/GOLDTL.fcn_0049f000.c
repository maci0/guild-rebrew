#include <string.h>

extern unsigned char* lpGebaeudeINST;
#include "GOLDTL.fcn_0049f000_gconf.h"
extern char g_773d75;

int __cdecl gm_GetEntityTableEntry(int);
int __cdecl fcn_0050d320(int, signed char);
int __cdecl fcn_005463a0(int, int, int);
int __cdecl he_fn_Handlung(void);
int __cdecl gm_GetOppositeStatIndex(int);
int __cdecl fcn_00507910(int);
int __cdecl gm_RandomMod(int);
int __cdecl fcn_00507400(int, int);
int __cdecl fcn_005072c0(int);
int __cdecl fcn_004a4bb0(int, int, int, int*, int*, int);
int __cdecl fcn_0050d170(int);

/* ADDRESS: GOLDTL 0x0049f000 */
unsigned int __cdecl fcn_0049f000(int a0, char* a1, int a2, int* a3, int* a4)
{
	int v8;
	int v15[6];
	int v14[6];
	int v12[17];
	int v13[17];
	int v7;
	int v9;
	int v10;
	int i;
	int limit;
	unsigned char* p;

	v7 = gm_GetEntityTableEntry((int) a1);
	if (a1[2] != 5) {
		return 0;
	}
	if (*(int*) (a1 + 0x194) < 4) {
		return 0;
	}
	if (v7 == 0) {
		return 0;
	}
	v8 = fcn_0050d320((int) a1, g_773d75);
	if (v8 / 0x20 < 5000) {
		return 0;
	}
	v9 = fcn_005463a0(1, 0, 0x24);
	while (v9 != 0) {
		if (*(int*) (v9 + 0xac) == *(int*) (a1 + 4)) {
			return 0;
		}
		v9 = he_fn_Handlung();
	}
	gm_GetOppositeStatIndex(*(unsigned char*) (a1 + 0x164));
	memset(&v12[1], 0, 0x3c);
	p = (unsigned char*) (v7 + 0x75);
	i = 0;
	do {
		*(int*) ((char*) v13 + i + 4) = gm_GetOppositeStatIndex(*p);
		i += 4;
		p++;
	} while (i < 0x3c);
	i = 0;
	do {
		if (lpGebaeudeINST[i] != 0) {
			v12[fcn_00507910(g_entity_type_table[lpGebaeudeINST[i] * 0x24d])]++;
		}
		i += 0xa9;
	} while (i < 0xa900);
	limit = (int) (unsigned short) gm_RandomMod(4) + 1;
	v10 = gm_RandomMod(0x10) & 0xffff;
	v7 = 0x10;
	do {
		if (v10 != 0 && v13[v10] == 0 && v12[v10] < limit) {
			if (v10 == -1) {
				return 0;
			}
			v7 = fcn_00507400(v10, 1);
			v15[1] = fcn_005072c0(v7);
			if (v15[1] == 0) {
				return 0;
			}
			v15[0] = 5;
			v15[2] = 1;
			v14[0] = 0;
			v14[1] = 0;
			v14[2] = 0;
			v9 = fcn_004a4bb0(a0, (int) a1, a2, v15, v14, 1);
			if (v9 == 0) {
				return 0;
			}
			if (v8 < fcn_0050d170(v15[1])) {
				return 0;
			}
			memcpy(a3, v15, 0x18);
			a3[4] = v7;
			memcpy(a4, v14, 0x18);
			return 0x34;
		}
		v10 = (v10 + 1) % 0x10;
		v7--;
	} while (v7 != 0);
	return 0;
}
