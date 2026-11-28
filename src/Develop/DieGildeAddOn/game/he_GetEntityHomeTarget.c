extern unsigned char* lpGebaeudePROT;
#include "Develop/DieGildeAddOn/game/building_prototype.h"
int __cdecl gm_CheckEntityType(char*);
char* __cdecl gm_FindFallbackPublicBuilding(char*, int*, int*);
char* __cdecl gm_FindRecordById(int);
int __cdecl init_AllocateGebaeudeSceneSlot(char*);
int __cdecl init_EnsureObjektSceneContext(char*);
char* __cdecl gm_QueryEntities(int, int, int, int);
char* __cdecl sim_StartEntityQueryByType(char*);

/* ADDRESS: GOLDTL 0x00567170 */
int __cdecl he_GetEntityHomeTarget(char* h, int* out1, int* out2, int* out3)
{
	char* q;
	char* t;
	char* e;
	char* r;
	int id;
	unsigned char k;
	unsigned char* ty;

	q = 0;
	t = 0;
	id = -1;
	if (h[2] == 0xd || h[2] == 0xe) {
		return 0;
	}
	if (*(unsigned char**) (h + 0x16c) != 0) {
		ty = ((unsigned char*)&((BUILDING_PROTOTYPE*)lpGebaeudePROT)[**(unsigned char**) (h + 0x16c)]);
		if (*ty == 4 || *ty == 0x10 || *ty == 0x13 || *ty == 0x1d || *ty == 0x1e) {
			return 0;
		}
		k = h[0x180];
		if (k == 0x3f || k == 0x40 || k == 0x48 || k == 0x3c || k == 0x49 || k == 0x44 || k == 0x62 || k == 0x61
		    || k == 0x65 || k == 0x64 || k == 0x14 || k == 0x75 || k == 0x1a || k == 0x18 || k == 0xa1) {
			return 0;
		}
		if (h[0x1b1] != 0) {
			return 0;
		}
	}
	if (*(char**) (h + 0x170) == 0) {
		e = gm_FindFallbackPublicBuilding(h, out1, out2);
		if (e == 0) {
			return 0;
		}
		if (out3 != 0) {
			r = gm_FindRecordById(*out2);
			if (gm_CheckEntityType(e) != 0) {
				*out3 = init_AllocateGebaeudeSceneSlot(e);
				return 1;
			}
			if (r != 0) {
				*out3 = init_EnsureObjektSceneContext(r);
				return 1;
			}
			*out3 = 0;
			return 1;
		}
	} else {
		if (*(char**) (h + 0x16c) != 0 && gm_CheckEntityType(*(char**) (h + 0x16c)) != 0) {
			q = gm_QueryEntities(*(int*) (*(char**) (h + 0x16c) + 0x5d), 1, 0, 0x2c);
			if (q == 0) {
				q = gm_QueryEntities(*(int*) (*(char**) (h + 0x16c) + 0x5d), 1, 0, 0x109);
				if (q == 0) {
					return 0;
				}
			}
			t = *(char**) (h + 0x16c);
		}
		if (q == 0 && *(char**) (h + 0x170) != 0
		    && (*(char**) (h + 0x16c) == 0 || gm_CheckEntityType(*(char**) (h + 0x16c)) == 0)) {
			q = sim_StartEntityQueryByType(*(char**) (h + 0x170));
			t = *(char**) (h + 0x170);
		}
		if (t == 0) {
			return 0;
		}
		if (q != 0) {
			id = *(int*) (q + 2);
		}
		if (out3 != 0) {
			if (gm_CheckEntityType(t) != 0) {
				*out3 = init_AllocateGebaeudeSceneSlot(t);
			} else if (q != 0) {
				*out3 = init_EnsureObjektSceneContext(q);
			} else {
				*out3 = -1;
			}
		}
		*out1 = *(int*) (t + 1);
		*out2 = id;
	}
	return 1;
}
