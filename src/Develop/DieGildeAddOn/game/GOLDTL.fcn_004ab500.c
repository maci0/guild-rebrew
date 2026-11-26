/* Select a placement candidate for an entity and fill the caller's packet
 * with the chosen node's keys. */
#include "Develop/DieGildeAddOn/game/building_prototype.h"
extern unsigned char* lpGebaeudePROT;
extern unsigned char* lpGebaeudeINST;
#include "Develop/DieGildeAddOn/game/entity_record.h"
int __cdecl gm_CheckStatLevel(int, int);
int __cdecl fcn_00502cd0(int, int, int, int, int);
int __cdecl gm_CountBuildingExtensions(char*);
int __cdecl gm_RandomMod(unsigned short);
int __cdecl fcn_004a5340(int*, int, int*, int, float, unsigned short*);
int __cdecl fcn_004a5c40(int*, int, int, float, float, int, unsigned short*);
int __cdecl amt_GetRoleLevel(unsigned char);

/* ADDRESS: GOLDTL 0x004ab500 */
unsigned int __cdecl ai_StartBlutrache(unsigned int a0, unsigned short* entity, int a2,
                                  char* packet, int a4)
{
	unsigned int v8;
	unsigned short v9[4];
	int v10[4];
	unsigned short* v12;
	unsigned char* v11;
	int v5;
	int v6;
	int v7;
	int v1;
	unsigned int* v4;

	v5 = gm_CheckStatLevel((int) *entity, 0xe);
	v9[0] = 0xffff;
	v9[1] = 0xffff;
	v9[2] = 0xffff;
	v9[3] = 0xffff;
	v12 = 0;
	v6 = 0;
	v4 = 0;
	v10[0] = 0;
	v10[1] = 0;
	v10[2] = 0;
	v10[3] = 0;
	if ((*(unsigned char*) ((char*) entity + 0x1cc) & 8) == 0 &&
	    *(int*) ((char*) entity + 0x194) >= 5 && (a0 == 0x44 || a0 == 0) &&
	    a2 == 0 && v5 != 0 && *(char*) ((char*) entity + 2) != 3) {
		a0 = 0x100;
		v11 = lpGebaeudeINST;
		do {
			if (*v11 != 0 && *(unsigned short*) (v11 + 0x27) == *entity &&
			    *(unsigned char*) ((unsigned char*)&((BUILDING_PROTOTYPE*)lpGebaeudePROT)
			                       [(unsigned int) *v11]) == 0x1f &&
			    fcn_00502cd0(*(int*) (v11 + 0x5d), 2, 6, 0, 0x27c) != 0) {
				if (v12 == 0) {
					v12 = (unsigned short*) v11;
					v6 = gm_CountBuildingExtensions((char*) v11);
				} else {
					v5 = gm_CountBuildingExtensions((char*) v11);
					if (v5 > v6) {
						v6 = v5;
						v12 = (unsigned short*) v11;
					}
				}
			}
			v11 += 0xa9;
		} while (--a0);
		if (v12 != 0 && v6 != 0) {
			v4 = (unsigned int*) 0xf00500;

			if (fcn_004a5340((int*) entity, 1, (int*) &v4, 0,
			                 (float) (gm_RandomMod(0x20) & 0xffff) + 25.0f,
			                 (unsigned short*) &v8) != 0) {
				a2 = (int) (((char*)&((ENTITY_RECORD*)g_7f4ca0)[v8 & 0xffff]));
				v5 = amt_GetRoleLevel(*(unsigned char*) (a2 + 0x166)) / 3 + 2;
				if (v5 + 2 <= *(int*) ((char*) entity + 0x194) &&
				    (a0 = fcn_004a5c40((int*) entity, 4, (int) v4, 25.0f,
				                       75.0f, v6, v9)) != 0) {
					v7 = 0;
					v6 = 0;
					if ((int) a0 > 0) {
						do {
							v1 = *(unsigned char*) (
							    ((char*)&((ENTITY_RECORD*)g_7f4ca0)[(unsigned int)v9[v7]]) + 0x166);
							v1 = amt_GetRoleLevel((unsigned char) v1) / 3 +
							     2 + v5;
							if (v1 >= *(int*) ((char*) entity + 0x194)) {
								v5 = v1;
								v10[v6] = (int) ((char*)&((ENTITY_RECORD*)g_7f4ca0)
								                 [(unsigned int)v9[v7]]);
								v6 += 1;
							}
							v7 += 1;
						} while (v7 < (int) a0);
						if (v6 != 0) {
							*(unsigned int*) (packet + 4) =
							    *(unsigned int*) (a2 + 4);
							*(unsigned int*) (packet + 0xc) =
							    *(unsigned int*) (v10[0] + 4);
							if (v6 > 1)
								*(unsigned int*) (packet + 8) =
								    *(unsigned int*) (v10[1] + 4);
							if (v6 > 2)
								*(unsigned int*) (a4 + 0xc) =
								    *(unsigned int*) (v10[2] + 4);
							if (v6 > 3)
								*(unsigned int*) (a4 + 8) =
								    *(unsigned int*) (v10[3] + 4);
							*(int*) (packet + 0x10) = v5;
							*packet = 7;
							return 0x44;
						}
					}
				}
			}
		}
	}
	return 0;
}
