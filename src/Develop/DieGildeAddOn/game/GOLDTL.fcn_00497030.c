extern char* lpObjektePROT;
extern unsigned char* lpGebaeudePROT;
extern unsigned char g_773d75;
#include "Develop/DieGildeAddOn/game/object_prototype.h"
#include "Develop/DieGildeAddOn/game/building_prototype.h"
unsigned short* __cdecl fcn_00502cd0(int, int, ...);
char* __cdecl gm_FindRecordById(unsigned int);
char* __cdecl gm_SearchTable67(unsigned int);
char* __cdecl gm_LookupEntityRecordById(int);
short* __cdecl fcn_0050d430(short*);
int __cdecl fcn_0050d320(char*, char);
float __cdecl fcn_0050bb50(int, unsigned char);

/* ADDRESS: GOLDTL 0x00497030 */
int __cdecl fcn_00497030(int a0, int a1, int a2, char* a3, char* a4)
{
	char* rec;
	unsigned char* ent;
	unsigned char* tbl;
	unsigned int id;
	unsigned char kind;
	int i;
	int cnt;
	int owner;

	if (a2 != 1) {
		goto fail;
	}
	if (*a3 != 2) {
		goto fail;
	}
	id = *(unsigned int*) (a3 + 4);
	if ((*(char *)&((OBJECT_PROTOTYPE *)lpObjektePROT)[id].value_040) != 0) {
		goto fail;
	}
	if ((*(char *)&((OBJECT_PROTOTYPE *)lpObjektePROT)[id].kind) == 2) {
		goto fail;
	}
	ent = 0;
	rec = 0;
	owner = 0;
	if (*a4 == 1) {
		rec = (char*) gm_FindRecordById(*(unsigned int*) (a4 + 4));
		if (rec == 0) {
			goto fail;
		}
		kind = (*(char *)&((OBJECT_PROTOTYPE *)lpObjektePROT)[(unsigned int) *(unsigned short*)rec].kind);
		if (kind != 2 && kind != 6) {
			goto done;
		}
		if (fcn_00502cd0(*(int*) (rec + 0x14), 1, 0, *(unsigned int*) (a3 + 4)) != 0) {
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
		while (i < cnt && (*(unsigned short*) (tbl + 0x23 + i * 2) & 0x7fff) != *(unsigned int*) (a3 + 4)) {
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
	} else if (*a4 == 4) {
		ent = (unsigned char*) gm_SearchTable67(*(unsigned int*) (a4 + 4));
		if (ent == 0) {
			goto fail;
		}
		if (fcn_00502cd0(*(int*) (ent + 0x5d), 1, 0, *(unsigned int*) (a3 + 4)) != 0) {
			goto fail;
		}
		tbl = (unsigned char*)&((BUILDING_PROTOTYPE*)lpGebaeudePROT)[(unsigned int) *ent];
		cnt = ((BUILDING_PROTOTYPE*)tbl)->component_count;
		i = 0;
		while (i < cnt && (*(unsigned short*) (tbl + 0x23 + i * 2) & 0x7fff) != *(unsigned int*) (a3 + 4)) {
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
	} else if (*a4 == 7) {
		owner = (int) gm_LookupEntityRecordById(*(unsigned int*) (a4 + 4));
		if (owner == 0) {
			return 0;
		}
	} else {
		goto fail;
	}
done:
	if (a0 == 0x39) {
		i = *(int*) (a4 + 0x10);
		*(int*) (a3 + 0x10) = 0x39;
	} else {
		if (rec != 0) {
			owner = (int) fcn_0050d430((short*) rec);
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
		i = fcn_0050d320((char*) owner, g_773d75);
		*(int*) (a3 + 0x10) = 0;
	}
	if (*(float*) (a3 + 0x14) > 0.0f && *(float*) (a3 + 0x14) < 1.0f) {
		i = (int) ((float) i * *(float*) (a3 + 0x14));
	}
	return ((i < (int) fcn_0050bb50(*(int*) (a3 + 4), g_773d75)) - 1U) & 0xb;

fail:
	return 0;
}
