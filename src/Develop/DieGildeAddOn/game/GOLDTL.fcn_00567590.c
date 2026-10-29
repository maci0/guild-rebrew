#include <math.h>

#include "client_types.h"

extern pos14_7f4c00 g_7f4c00;
extern int g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;
extern float g_696540[];
extern float g_696550[];
extern float g_6628a0;
extern float g_662918;
extern float g_665ec4;
extern char* lpGebaeudePROT;
extern char g_6b5c60[];
extern unsigned char g_7747b0;

int __cdecl fcn_00500e20(int*);
void __cdecl fcn_00546190(void*);
void __cdecl fcn_00500bb0(void*, int, int, int);
void __cdecl sim_SetSyncParams(int*, int, int, int);
int __cdecl fcn_00567030(char*, int*, int*);
int __cdecl gm_CheckEntityType(char*);
char* __cdecl gm_SearchTable67(int);
void __cdecl fcn_00455350(char*, char*, float*);
int __cdecl gm_AccumulateTyped2(char*);
int __cdecl fcn_00402ba0(int, int);
void __cdecl fcn_004c6650(int);
void __cdecl cm_RequestChrMoveToUniverse(int, int, int, char*);
void __cdecl fcn_004c5ba0(int, int, int, char*);
void __cdecl fcn_004c5da0(int, int, int, int, int, char*);
void __cdecl fcn_004c5420(int, int, int, int, int);
int __cdecl gm_RandomMod(int);
unsigned char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
unsigned char* __cdecl gm_FindNextFilteredEntity(void);
int __cdecl fcn_00567170(char*, int*, int*, int*);
int __cdecl fcn_00567410(char*, int, char**, int*, int*);

/* ADDRESS: GOLDTL 0x00567590 */
void __cdecl fcn_00567590(char* a0)
{
	char* p;
	char* q;
	char* ent;
	char* other;
	int hour;
	int found;
	int moved;
	int v18;
	int out1;
	int out2;
	int idx;
	int count;
	int kind;
	int c2;
	int id;
	float dist;
	char* list[0x20];
	float v10[3];
	float v11[3];

	v18 = 0;
	found = 0;
	hour = fcn_00500e20((int*) &g_7f4c00);
	switch (*(int*) (a0 + 0x70)) {
	case 0:
		idx = 0;
		p = (char*) 0x7f4e0c;
		while ((int) p < 0x85a20c) {
			if (1 <= found) {
				break;
			}
			if ((p[-7] != 0 || p[-8] != 0) && *(int*) p != 0 && *(int*) (p + 0x18) != 0
			    && (*(unsigned int*) (p + 0x5c) & 0x1000) == 0
			    && fcn_00567030(p - 0x16c, &out1, &out2) != 0) {
				if (out1 != *(int*) (*(int*) (p + 0x18) + 0x2c)) {
					v18 = *(int*) p;
					if (gm_CheckEntityType((char*) v18) != 0 || *(int*) (*(int*) p + 0x61) == 0) {
						fcn_004c6650(*(int*) (p - 0x168));
						cm_RequestChrMoveToUniverse(*(int*) (p - 0x168), out1, out2, "dummy_EINGANG");
						fcn_004c5ba0(*(int*) (p - 0x168), out1, out2, g_6b5c60);
						*(unsigned int*) (p + 0x5c) |= 0x1000;
					}
					else {
						kind = *(unsigned char*) (0x7f4ca2
						       + *(unsigned short*) (*(int*) p + 0x27) * 0x21c);
						if (kind != 6 && kind != 7 && (int) fcn_00402ba0(0, 0) <= 0x1f) {
							other = gm_SearchTable67(*(int*) (*(int*) (p + 0x18) + 0x2c));
							if (other != 0 && *(int*) (other + 0x61) != 0) {
								char* src;
								char* dst;

								src = *(char**) (*(int*) p + 0x61);
								dst = *(char**) (other + 0x61);
								fcn_00455350(src, src + 0x4c, v10);
								fcn_00455350(dst, dst + 0x4c, v11);
								dist = (float) sqrt(
								    (v10[0] - v11[0]) * (v10[0] - v11[0])
								    + (v10[1] - v11[1]) * (v10[1] - v11[1])
								    + (v10[2] - v11[2]) * (v10[2] - v11[2]));
								if (g_665ec4 <= dist) {
									*(int*) (a0 + 0xac) = idx;
									goto next0;
								}
							}
							if ((float) (g_7f4c04 & 0xffff) < g_696540[hour] - g_6628a0) {
								fcn_004c6650(*(int*) (p - 0x168));
								fcn_004c5da0(*(int*) (p - 0x168), out1, out2, 0, 0, "Go to work");
								found += 1;
								*(unsigned int*) (p + 0x5c) |= 0x1000;
							}
						}
					}
					*(int*) (a0 + 0xac) = idx;
				}
			}
next0:
			p += 0x21c;
			idx += 1;
		}
		if (found != 0) {
			*(int*) (a0 + 0x52) = *(int*) &g_7f4c00;
			*(int*) (a0 + 0x56) = g_7f4c04;
			*(int*) (a0 + 0x5a) = g_7f4c08;
			*(unsigned short*) (a0 + 0x5e) = g_7f4c0c;
			fcn_00500bb0(a0 + 0x52, 0, 5, 0);
		}
		if ((float) (g_7f4c04 & 0xffff) < g_696540[hour]) {
			return;
		}
		p = (char*) 0x7f4e04;
		while ((int) p < 0x85a204) {
			if ((p[1] != 0 || p[0] != 0) && *(int*) (p + 8) != 0 && *(int*) (p + 0x20) != 0
			    && (*(unsigned int*) (p + 0x64) & 0x1000) == 0
			    && fcn_00567030(p - 0x164, &out2, &out1) != 0) {
				if (out2 != *(int*) (*(int*) (p + 0x20) + 0x2c)) {
					fcn_004c6650(*(int*) (p - 0x160));
					cm_RequestChrMoveToUniverse(*(int*) (p - 0x160), out2, out1, "dummy_EINGANG");
					fcn_004c5ba0(*(int*) (p - 0x160), out2, out1, g_6b5c60);
					*(unsigned int*) (p + 0x64) |= 0x1000;
				}
			}
			p += 0x21c;
		}
		*(int*) (a0 + 0x52) = *(int*) &g_7f4c00;
		*(int*) (a0 + 0x56) = g_7f4c04;
		*(int*) (a0 + 0x5a) = g_7f4c08;
		*(unsigned short*) (a0 + 0x5e) = g_7f4c0c;
		sim_SetSyncParams((int*) (a0 + 0x52), (int) g_696550[hour], 0, 0);
		*(int*) (a0 + 0x70) = 1;
		*(int*) (a0 + 0xac) = 0;
		return;
	case 1:
		if ((signed char) g_7747b0 < 0) {
			fcn_00546190(a0);
			return;
		}
		if (*(int*) &g_7f4c00 != *(int*) (a0 + 0x44)) {
			fcn_00546190(a0);
			return;
		}
		q = (char*) gm_StartFilteredEntitySearch(1, 5, 0x16);
		count = 0;
		if (q != 0) {
			do {
				if (count >= 0x20) {
					break;
				}
				if (*(unsigned short*) (q + 0x27) != 0xffff && *(int*) (q + 0x61) != 0) {
					list[count] = q;
					count += 1;
				}
				q = (char*) gm_FindNextFilteredEntity();
			} while (q != 0);
		}
		found = 0;
		idx = 0;
		p = (char*) 0x7f4e24;
		while ((int) p < 0x85a224) {
			if ((p[-0x1f] != 0 || p[-0x20] != 0) && *(int*) (p - 0x18) != 0 && *(int*) p != 0
			    && (kind = *(unsigned char*) (lpGebaeudePROT
			                + (unsigned char) ** (char**) (p - 0x18) * 0x24d)) != 4
			    && kind != 0x10 && kind != 0x13
			    && fcn_00567170(p - 0x184, &out1, &out2, 0) != 0
			    && (out1 != *(int*) (*(int*) p + 0x2c) || out2 != *(int*) (*(int*) p + 0x30))) {
				if ((*(unsigned int*) (p + 0x44) & 0x800) == 0) {
					c2 = *(unsigned char*) (0x7f4ca2
					     + *(unsigned short*) (*(int*) (p - 0x18) + 0x27) * 0x21c);
					if (c2 == 6 || c2 == 7) {
						fcn_004c6650(*(int*) (p - 0x180));
						if (count != 0 && gm_AccumulateTyped2(p - 0x184) >= 0xc81
						    && gm_RandomMod(2) != 0) {
							if (fcn_00567410(p - 0x184, count, list, &out1, &out2) != 0) {
								fcn_004c5da0(*(int*) (p - 0x180), out1, out2, 0, 0, "Go to wirtshaus");
							}
						}
						else {
							if (out2 != -1) {
								if (found >= 0x40) {
									goto after1;
								}
								fcn_004c5da0(*(int*) (p - 0x180), out1, out2, 0, 0, "Go home");
							}
							else {
								fcn_004c5da0(*(int*) (p - 0x180), out1, out2, 0, 1, "Go home");
							}
						}
after1:
						*(unsigned int*) (p + 0x44) |= 0x800;
						fcn_004c5420(*(int*) (p - 0x180), 0x1c8, 4, 0x800, 0x1000);
						*(int*) (a0 + 0xac) = idx;
						found += 1;
					}
				}
			}
			p += 0x21c;
			idx += 1;
		}
		moved = found;
		idx = 0;
		p = (char*) 0x7f4e0c;
		while ((int) p < 0x85a20c) {
			if (1 <= moved) {
				break;
			}
			if ((p[-7] != 0 || p[-8] != 0) && *(int*) p != 0 && *(int*) (p + 0x18) != 0
			    && (kind = *(unsigned char*) (lpGebaeudePROT
			                + (unsigned char) ** (char**) p * 0x24d)) != 4
			    && kind != 0x10 && kind != 0x13
			    && fcn_00567170(p - 0x16c, &out1, &out2, 0) != 0
			    && (out1 != *(int*) (*(int*) (p + 0x18) + 0x2c)
			        || out2 != *(int*) (*(int*) (p + 0x18) + 0x30))
			    && (*(unsigned int*) (p + 0x5c) & 0x800) == 0) {
				fcn_004c6650(*(int*) (p - 0x168));
				if (count != 0 && gm_AccumulateTyped2(p - 0x16c) >= 0xc81 && gm_RandomMod(2) != 0) {
					if (fcn_00567410(p - 0x16c, count, list, &out1, &out2) != 0) {
						fcn_004c5da0(*(int*) (p - 0x168), out1, out2, 0, 0, "Go to wirtshaus");
					}
				}
				else {
					if (out2 != -1) {
						fcn_004c5da0(*(int*) (p - 0x168), out1, out2, 0, 0, "Go home");
					}
					else {
						fcn_004c5da0(*(int*) (p - 0x168), out1, out2, 0, 1, "Go home");
					}
				}
				*(unsigned int*) (p + 0x5c) |= 0x800;
				fcn_004c5420(*(int*) (p - 0x168), 0x1c8, 4, 0x800, 0x1000);
				moved += 1;
				*(int*) (a0 + 0xac) = idx;
			}
			p += 0x21c;
			idx += 1;
		}
		if (moved != 0) {
			*(int*) (a0 + 0x52) = *(int*) &g_7f4c00;
			*(int*) (a0 + 0x56) = g_7f4c04;
			*(int*) (a0 + 0x5a) = g_7f4c08;
			*(unsigned short*) (a0 + 0x5e) = g_7f4c0c;
			fcn_00500bb0(a0 + 0x52, 0, 5, 0);
		}
		if ((float) (g_7f4c04 & 0xffff) <= g_696550[hour] + g_662918) {
			return;
		}
		p = (char*) 0x7f4e04;
		while ((int) p < 0x85a204) {
			if ((p[1] != 0 || p[0] != 0) && *(int*) (p + 8) != 0
			    && *(int*) (p + 0xc) != 0 && *(int*) (p + 0x20) != 0
			    && (kind = *(unsigned char*) (lpGebaeudePROT
			                + (unsigned char) ** (char**) (p + 8) * 0x24d)) != 4
			    && kind != 0x10 && kind != 0x13
			    && fcn_00567170(p - 0x164, &out2, &out1, 0) != 0
			    && (out2 != *(int*) (*(int*) (p + 0x20) + 0x2c)
			        || out1 != *(int*) (*(int*) (p + 0x20) + 0x30))
			    && (*(unsigned int*) (p + 0x64) & 0x800) == 0) {
				fcn_004c6650(*(int*) (p - 0x160));
				if (count != 0 && gm_AccumulateTyped2(p - 0x164) >= 0xc81 && gm_RandomMod(2) != 0) {
					if (fcn_00567410(p - 0x164, count, list, &out2, &out1) != 0) {
						cm_RequestChrMoveToUniverse(*(int*) (p - 0x160), out2, out1, "dummy_EINGANG");
						fcn_004c5ba0(*(int*) (p - 0x160), out2, out1, g_6b5c60);
					}
				}
				else {
					if (out1 != -1) {
						cm_RequestChrMoveToUniverse(*(int*) (p - 0x160), out2, out1, "dummy_EINGANG");
						fcn_004c5ba0(*(int*) (p - 0x160), out2, out1, g_6b5c60);
					}
					else {
						cm_RequestChrMoveToUniverse(*(int*) (p - 0x160), out2, -1, "dummy_TUER");
					}
				}
				*(unsigned int*) (p + 0x64) |= 0x800;
				fcn_004c5420(*(int*) (p - 0x160), 0x1c8, 4, 0x800, 0x1000);
			}
			p += 0x21c;
		}
		fcn_00546190(a0);
		return;
	case -2:
	case -1:
		fcn_00546190(a0);
		return;
	default:
		return;
	}
}
