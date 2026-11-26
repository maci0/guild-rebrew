extern char* lpGebaeudePROT;
typedef struct { unsigned char kind; unsigned char unknown01[0x246]; unsigned char level; unsigned char unknown248[5]; } BUILDING_ROW;
extern char* lpGebaeudeINST;
extern char g_773d75;
extern int g_666028;
extern int g_66602c;
extern float g_664178;
extern float g_664158;
extern float g_6628bc;
#include "Develop/DieGildeAddOn/game/building_prototype.h"
char* __cdecl he_StartHandlungSearch(int, ...);
char* __cdecl he_fn_Handlung(void);
char* __cdecl gm_StartFilteredEntitySearch(int, ...);
char* __cdecl gm_FindNextFilteredEntity(void);
int __cdecl fcn_004fa5b0(int, int, int);
int __cdecl ai_StartKreditNehmen(int, char*, int, char*, int);
int __cdecl gm_CalculateGebaeudeValue(char*, int);
int __cdecl fcn_0050d320(char*, char);
int __cdecl gm_BuyBuilding(int, int, int, char*, int);

/* ADDRESS: GOLDTL 0x00497990 */
int __cdecl fcn_00497990(int a1, char* entityRec, int phaseFlag, char* decisionMsg, int a5)
{
	unsigned char* e;
	unsigned char* t;
	int i;
	int n;
	int bits_lo;
	int bits_hi;
	int q[4];
	int A;
	int B;
	int r;
	int id;
	char buf[0x220];

	if (*(char*) (entityRec + 2) == 3) {
		return 0;
	}
	for (i = 0; i < 0x88; i++) {
		((int*) buf)[i] = 0;
	}
	*(int*) buf = 1;
	if (phaseFlag == 0) {
		if (*(char*) decisionMsg != 0) {
			return 0;
		}
	} else if (phaseFlag == 1) {
		unsigned char b = *(char*) decisionMsg;
		if (b != 5 && b != 4) {
			return 0;
		}
	}
	if (he_StartHandlungSearch(2, 0, 0xd, 2, *(unsigned short*) entityRec) != 0) {
		return 0;
	}
	e = (unsigned char*) lpGebaeudeINST;
	for (i = 0; i < 0x100; i++) {
		if (*e != 0) {
			unsigned char b = ((BUILDING_PROTOTYPE *)lpGebaeudePROT)[*e].category;
			bits_lo = 0;
			bits_hi = 0;
			if (b > 0x1f) {
				bits_hi = (int) (1U << ((b - 0x20) & 31));
			} else {
				bits_lo = (int) (1U << b);
			}
			if (*(unsigned short*) entityRec == *(unsigned short*) (e + 0x27)) {
				if ((g_666028 & bits_lo) != 0 || (g_66602c & bits_hi) != 0) {
					goto found;
				}
			}
		}
		e += 0xa9;
	}
	return 0;
found:
	A = (int) (fcn_0050d320(entityRec, g_773d75) * g_664178);
	r = fcn_004fa5b0(1, (int) entityRec, (int) buf);
	q[0] = (r == 2 || r == 4);
	r = fcn_004fa5b0(5, (int) entityRec, (int) buf);
	q[1] = (r == 2 || r == 4);
	r = fcn_004fa5b0(9, (int) entityRec, (int) buf);
	q[2] = (r == 2 || r == 4);
	r = fcn_004fa5b0(0xc, (int) entityRec, (int) buf);
	q[3] = (r == 2 || r == 4);
	t = (unsigned char*) *(int*) (entityRec + 0x170);
	if (t != 0) {
		n = ((BUILDING_PROTOTYPE *)lpGebaeudePROT)[*t].level - 1;
		if (n >= 0) {
			/* uncertain: native clears b dwords from &q[0], past q[3] when b > 4 */
			for (i = 0; i <= n; i++) {
				q[i] = 0;
			}
		}
	}
	if (*(char*) decisionMsg == 0) {
		e = (unsigned char*) gm_StartFilteredEntitySearch(1, 6);
		if (*(char*) decisionMsg != 0) {
			goto ret16;
		}
		while (e != 0) {
			unsigned char b = *(unsigned char*) e;
			if (((BUILDING_PROTOTYPE *)lpGebaeudePROT)[b].category == 2 && (*(unsigned char*) (e + 0x5a) & 2) != 0) {
				if ((b == 4 && q[0] != 0) || (b == 5 && q[1] != 0) || (b == 6 && q[2] != 0) || (b == 7 && q[3] != 0)) {
					t = (unsigned char*) he_StartHandlungSearch(1, 0, 0x1b);
					if (t != 0) {
						while (*(int*) (t + 0xac) != *(int*) (e + 1)) {
							t = (unsigned char*) he_fn_Handlung();
							if (t == 0) {
								goto next_ent;
							}
						}
						B = *(int*) (t + 0xb0);
						if (A < B) {
							goto fraction;
						}
						*(char*) decisionMsg = 4;
						*(int*) (decisionMsg + 4) = *(int*) (e + 1);
						*(int*) (decisionMsg + 8) = 1;
					}
				}
			}
		next_ent:
			e = (unsigned char*) gm_FindNextFilteredEntity();
			if (*(char*) decisionMsg != 0) {
				return 0x10;
			}
		}
		if (*(char*) decisionMsg == 0) {
			return 0;
		}
	} else {
		if (*(unsigned char*) decisionMsg != 5) {
			return 0;
		}
		id = *(int*) (decisionMsg + 4);
		if (id == 4 && q[0] == 0) {
			return 0;
		}
		if (id == 5 && q[1] == 0) {
			return 0;
		}
		if (id == 6 && q[2] == 0) {
			return 0;
		}
		if (id == 7 && q[3] == 0) {
			return 0;
		}
		e = (unsigned char*) gm_StartFilteredEntitySearch(1, 6);
		if (*(unsigned char*) decisionMsg != 5) {
			goto ret16;
		}
		while (e != 0) {
			if (((BUILDING_PROTOTYPE *)lpGebaeudePROT)[*e].category == *(int*) (decisionMsg + 4)) {
				t = (unsigned char*) he_StartHandlungSearch(1, 0, 0x1b);
				if (t != 0) {
					while (*(int*) (t + 0xac) != *(int*) (e + 1)) {
						t = (unsigned char*) he_fn_Handlung();
						if (t == 0) {
							goto next_ent2;
						}
					}
					B = *(int*) (t + 0xb0);
					if (A < B) {
						goto fraction;
					}
					*(char*) decisionMsg = 4;
					*(int*) (decisionMsg + 4) = *(int*) (e + 1);
					*(int*) (decisionMsg + 8) = 1;
				}
			}
		next_ent2:
			e = (unsigned char*) gm_FindNextFilteredEntity();
			if (*(unsigned char*) decisionMsg != 5) {
				return 0x10;
			}
		}
		if (*(unsigned char*) decisionMsg == 5) {
			return 0;
		}
	}
ret16:
	return 0x10;
fraction:
	r = gm_CalculateGebaeudeValue((char*) e, (int) *(signed char*) (e + 0x5c));
	if ((double) (B - A) / (double) B < (double) (B - r) / (double) r * g_664158 + 0.25f) {
		*(int*) (decisionMsg + 8) = B - A;
		*(char*) decisionMsg = 0x12;
		return ai_StartKreditNehmen(0x10, entityRec, phaseFlag, decisionMsg, a5);
	}
	return 0;
}

/* ADDRESS: GOLDTL 0x00497e60 */
int __cdecl fcn_00497e60(int a1, char* a2)
{
	unsigned char* t;
	int id;

	if (*(unsigned char*) a2 != 4) {
		return 0;
	}
	t = (unsigned char*) he_StartHandlungSearch(1, 0, 0x1b);
	if (t == 0) {
		goto exhausted;
	}
	do {
		if (*(int*) (t + 0xac) == *(int*) (a2 + 4)) {
			goto found;
		}
		t = (unsigned char*) he_fn_Handlung();
	} while (t != 0);
exhausted:
	return (int) t;
found:
	gm_BuyBuilding(*(int*) (a2 + 4), *(int*) (a1 + 4), *(int*) (t + 0xb0), (char*) t, 1);
	return 0x10;
}
