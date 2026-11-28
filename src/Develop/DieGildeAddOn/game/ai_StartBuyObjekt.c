extern char* lpObjektePROT;
extern unsigned char* lpGebaeudePROT;
extern unsigned char gm_ActiveTownIndex;
#include "Develop/DieGildeAddOn/game/object_prototype.h"
#include "Develop/DieGildeAddOn/game/building_prototype.h"
unsigned short* __cdecl fcn_00502cd0(int, int, ...);
char* __cdecl gm_FindRecordById(unsigned int);
char* __cdecl gm_SearchTable67(unsigned int);
char* __cdecl gm_LookupEntityRecordById(int);
short* __cdecl gm_ResolveEntityOwnerBuilding(short*);
int __cdecl gm_GetSeasonTreasury(char*, char);
float __cdecl gm_GetSeasonPrice(int, unsigned char);

/* ADDRESS: GOLDTL 0x00497030 */
int __cdecl ai_StartBuyObjekt(int actionKind, int unused, int argCount, char* itemCmd, char* targetCmd)
{
	char* rec;
	unsigned char* ent;
	unsigned char* tbl;
	unsigned int id;
	unsigned char kind;
	int i;
	int cnt;
	int owner;

	if (argCount != 1) {
		goto fail;
	}
	if (*itemCmd != 2) {
		goto fail;
	}
	id = *(unsigned int*) (itemCmd + 4);
	if ((*(char *)&((OBJECT_PROTOTYPE *)lpObjektePROT)[id].value_040) != 0) {
		goto fail;
	}
	if ((*(char *)&((OBJECT_PROTOTYPE *)lpObjektePROT)[id].kind) == 2) {
		goto fail;
	}
	ent = 0;
	rec = 0;
	owner = 0;
	if (*targetCmd == 1) {
		rec = (char*) gm_FindRecordById(*(unsigned int*) (targetCmd + 4));
		if (rec == 0) {
			goto fail;
		}
		kind = (*(char *)&((OBJECT_PROTOTYPE *)lpObjektePROT)[(unsigned int) *(unsigned short*)rec].kind);
		if (kind != 2 && kind != 6) {
			goto done;
		}
		if (fcn_00502cd0(*(int*) (rec + 0x14), 1, 0, *(unsigned int*) (itemCmd + 4)) != 0) {
			goto fail;
		}
		ent = (unsigned char*) gm_SearchTable67(*(unsigned int*) (rec + 6));
		if (ent == 0) {
			goto fail;
		}
		tbl = (unsigned char*)&((BUILDING_PROTOTYPE*)lpGebaeudePROT)[(unsigned int) *ent];
		cnt = ((BUILDING_PROTOTYPE*)tbl)->component_count;
		i = 0;
		while (i < cnt && (*(unsigned short*) (tbl + 0x23 + i * 2) & 0x7fff) != *(unsigned short*) rec) {
			i++;
		}
		if (i >= cnt) {
			goto fail;
		}
		i++;
		if (i >= cnt) {
			goto fail;
		}
		while (i < cnt && (*(unsigned short*) (tbl + 0x23 + i * 2) & 0x7fff) != *(unsigned int*) (itemCmd + 4)) {
			i++;
		}
		if (i >= cnt) {
			goto fail;
		}
		if (*(unsigned short*) (tbl + i * 4 + 0xa3) != 0) {
			if (fcn_00502cd0(*(int*) (rec + 0x14), 1, 0, (unsigned int) *(unsigned short*) (tbl + i * 4 + 0xa3)) == 0) {
				goto fail;
			}
		}
		if (*(unsigned short*) (tbl + i * 4 + 0xa5) != 0) {
			if (fcn_00502cd0(*(int*) (rec + 0x14), 1, 0, (unsigned int) *(unsigned short*) (tbl + i * 4 + 0xa5)) == 0) {
				goto fail;
			}
		}
	} else if (*targetCmd == 4) {
		ent = (unsigned char*) gm_SearchTable67(*(unsigned int*) (targetCmd + 4));
		if (ent == 0) {
			goto fail;
		}
		if (fcn_00502cd0(*(int*) (ent + 0x5d), 1, 0, *(unsigned int*) (itemCmd + 4)) != 0) {
			goto fail;
		}
		tbl = (unsigned char*)&((BUILDING_PROTOTYPE*)lpGebaeudePROT)[(unsigned int) *ent];
		cnt = ((BUILDING_PROTOTYPE*)tbl)->component_count;
		i = 0;
		while (i < cnt && (*(unsigned short*) (tbl + 0x23 + i * 2) & 0x7fff) != *(unsigned int*) (itemCmd + 4)) {
			i++;
		}
		if (i >= cnt) {
			goto fail;
		}
		if (*(unsigned short*) (tbl + i * 4 + 0xa3) != 0) {
			if (fcn_00502cd0(*(int*) (ent + 0x5d), 1, 0, (unsigned int) *(unsigned short*) (tbl + i * 4 + 0xa3)) == 0) {
				goto fail;
			}
		}
		if (*(unsigned short*) (tbl + i * 4 + 0xa5) != 0) {
			if (fcn_00502cd0(*(int*) (ent + 0x5d), 1, 0, (unsigned int) *(unsigned short*) (tbl + i * 4 + 0xa5)) == 0) {
				goto fail;
			}
		}
	} else if (*targetCmd == 7) {
		owner = (int) gm_LookupEntityRecordById(*(unsigned int*) (targetCmd + 4));
		if (owner == 0) {
			return 0;
		}
	} else {
		goto fail;
	}
done:
	if (actionKind == 0x39) {
		i = *(int*) (targetCmd + 0x10);
		*(int*) (itemCmd + 0x10) = 0x39;
	} else {
		if (rec != 0) {
			owner = (int) gm_ResolveEntityOwnerBuilding((short*) rec);
		} else if (ent != 0) {
			if (*(unsigned short*) (ent + 0x27) == 0xffff) {
				goto fail;
			}
			owner = (unsigned int) *(unsigned short*) (ent + 0x27) * 0x21c + 0x7f4ca0;
		} else if (owner == 0) {
			goto fail;
		}
		if (owner == 0) {
			goto fail;
		}
		i = gm_GetSeasonTreasury((char*) owner, gm_ActiveTownIndex);
		*(int*) (itemCmd + 0x10) = 0;
	}
	if (*(float*) (itemCmd + 0x14) > 0.0f && *(float*) (itemCmd + 0x14) < 1.0f) {
		i = (int) ((float) i * *(float*) (itemCmd + 0x14));
	}
	return ((i < (int) gm_GetSeasonPrice(*(int*) (itemCmd + 4), gm_ActiveTownIndex)) - 1U) & 0xb;

fail:
	return 0;
}
