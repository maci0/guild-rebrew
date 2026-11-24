extern unsigned char* lpGebaeudePROT;
extern char* lpObjektePROT;
extern char g_7f4ca0[];
#include "Develop/DieGildeAddOn/game/object_prototype.h"
#include "Develop/DieGildeAddOn/game/game_data.h"
int __cdecl fcn_00507910(unsigned char typ);
int __cdecl gm_CheckStatLevel(int a0, int typ);
int __cdecl fcn_005903d0(void* geb, void* a1, void* a2);
int __cdecl gm_MapEntityStatRange(int typ);
void* __cdecl gm_StartFilteredEntitySearch(int, int, int, int, int);
#include "Develop/DieGildeAddOn/game/entity_record.h"
/* ADDRESS: GOLDTL 0x00506380 */
int __cdecl fcn_00506380(int playerIndex, unsigned char* a1, unsigned short* a2, int a3)
{
	unsigned char* rec;
	unsigned char* geb;
	int result;
	int found;
	int i;
	unsigned char ch;
	unsigned short id;
#include "Develop/DieGildeAddOn/game/building_prototype.h"
	result = 0;
	rec = 0;
	if (a1 != 0) {
		rec = (unsigned char*) (((unsigned char*)&((BUILDING_PROTOTYPE*)lpGebaeudePROT)[
(unsigned int) *a1]));
		found = gm_CheckStatLevel(playerIndex, fcn_00507910(*rec));
		if (*rec == 0x1d)
			return fcn_005903d0((void*) (((char*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[playerIndex])), a1, a2);
		switch (*rec) {
		case 33:
				if (*(unsigned short*) (a1 + 0x25) == playerIndex)
					result = 0x3c;
				if (*(unsigned short*) (a1 + 0x27) == playerIndex)
					result |= 0x620;
				break;
			case 2:
			case 30:
				if (*(unsigned short*) (a1 + 0x25) == playerIndex)
					result = 0x3c;
				if (*(unsigned short*) (a1 + 0x27) == playerIndex)
					result |= 0x5661;
				break;
			case 9:
				result = 1;
				if (*(unsigned short*) (a1 + 0x25) == playerIndex)
					result = 0x403d;
				if (*(unsigned short*) (a1 + 0x27) != playerIndex)
					break;
				result |= 0x54e1;
				for (i = 0; i < 6; i++) {
					if (rec[0x223 + i] == 0)
						break;
					if (rec[0x223 + i] == found) {
						result |= 0x2200;
						break;
					}
				}
				break;
			case 4:
				if (*(unsigned short*) (a1 + 0x25) == playerIndex)
					result = 0x50bd;
				if (*(unsigned short*) (a1 + 0x27) != playerIndex)
					break;
				result |= 0x44e1;
				for (i = 0; i < 6; i++) {
					if (rec[0x223 + i] == 0)
						break;
					if (rec[0x223 + i] == found) {
						result |= 0x2200;
						break;
					}
				}
				break;
			case 5:
			case 8:
			case 14:
			case 18:
			case 20:
			case 21:
			case 22:
			case 32:
				result = 0x81;
				if (*(unsigned short*) (a1 + 0x25) == playerIndex)
					result = 0x10bd;
				if (*(unsigned short*) (a1 + 0x27) != playerIndex)
					break;
				result |= 0x460;
				for (i = 0; i < 6; i++) {
					if (rec[0x223 + i] == 0)
						break;
					if (rec[0x223 + i] == found) {
						result |= 0x2200;
						break;
					}
				}
				result |= 0x4000;
				break;
			case 23:
			case 24:
			case 25:
			case 26:
				result = 0x5081;
				if ((*rec == 0x17 && *((unsigned char*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[playerIndex] + 0x169) == 0x1e) ||
				    (*rec == 0x18 && *((unsigned char*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[playerIndex] + 0x169) == 0x1f) ||
				    (*rec == 0x19 && *((unsigned char*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[playerIndex] + 0x169) == 0x20) ||
				    (*rec == 0x1a && *((unsigned char*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[playerIndex] + 0x169) == 0x21))
					result = 0x52f1;
				break;
			case 11:
			case 12:
			case 13:
			case 17:
			case 31:
				if (a2 == 0 || *(unsigned short*) (a1 + 0x27) == playerIndex)
					result = 0x81;
				if (*(unsigned short*) (a1 + 0x25) == playerIndex)
					result |= 0x403c;
				if (*(unsigned short*) (a1 + 0x27) == playerIndex)
					result |= 0x5670;
				if (a2 == 0)
					goto finish;
				if (*a2 == 0xfd)
					result |= 0x4001;
				break;
			case 16:
				if (*(unsigned short*) (a1 + 0x27) == playerIndex) {
					result = 0x54e1;
					for (i = 0; i < 6; i++) {
						if (rec[0x223 + i] == 0)
							break;
						if (rec[0x223 + i] == found) {
							result = 0x76e1;
							break;
						}
					}
				}
				if (*(unsigned short*) (a1 + 0x25) == playerIndex)
					result |= 0x3c;
				break;
			case 1:
			case 3:
			case 15:
				if (*rec != 3)
					result = 0x5081;
				ch = *((unsigned char*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[playerIndex] + 0x166);
				if (ch == 0xf || ch == 0xe || ch == 0xd)
					result |= 0x502;
				if (ch == 0xf || ch == 0xe || ch == 0xd)
					result |= 0x200;
				if (*rec == 3) {
					if (ch == 0xa)
						result |= 0x30;
				} else if (ch == 0xf) {
					result |= 0x30;
				}
				if (a2 != 0 && *a2 == 0x114 && ch == 0)
					result &= 0xffffbffe;
				break;
			case 19:
				if (*(unsigned short*) (a1 + 0x25) == playerIndex)
					result = 0x50bd;
				if (*(unsigned short*) (a1 + 0x27) != playerIndex)
					break;
				result |= 0x44e1;
				for (i = 0; i < 6; i++) {
					if (rec[0x223 + i] == 0)
						break;
					if (rec[0x223 + i] == found) {
						result |= 0x2200;
						break;
					}
				}
				break;
			case 6:
				geb = (unsigned char*) (((char*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[playerIndex]));
				result = 0x5001;
				if (*(unsigned short*) (a1 + 0x25) == playerIndex)
					result = 0x503d;
				if (*(unsigned short*) (a1 + 0x27) == playerIndex)
					result |= 0x5660;
				if (*(unsigned char*) (geb + 0x166) == 0xf)
					result |= 0x30;
				break;
			case 28:
				geb = (unsigned char*) (((char*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[playerIndex]));
				if (gm_MapEntityStatRange(*(unsigned char*) (geb + 0x164)) == 8)
					result = 1;
				else if (gm_StartFilteredEntitySearch(
				             2, 5, 9, 4,
				             *(unsigned short*) geb) != 0)
					result = 1;
				break;
			case 10:
				result = 1;
				break;
			case 7:
				result = 1;
				if (a2 != 0 && (*a2 == 0xe6 || *a2 == 0xe5))
					result = 0x1001;
				if (*(unsigned short*) (a1 + 0x25) == playerIndex)
					result |= 0x103c;
				if (*(unsigned short*) (a1 + 0x27) == playerIndex) {
					result |= 0x4460;
					for (i = 0; i < 6; i++) {
						if (rec[0x223 + i] == 0)
							break;
						if (rec[0x223 + i] == found) {
							result |= 0x2200;
							break;
						}
					}
				} else {
					if (a2 == 0)
						goto finish;
					if (*a2 != 0xf3)
						result |= 0x5000;
				}
			break;
		}
		goto common;
	} else if (a3 != 0) {
		if (*(int*) (a3 + 0x16c) != 0 &&
		    *(unsigned short*) (*(int*) (a3 + 0x16c) + 0x27) == playerIndex)
			result = 0x800;
	} else {
		if (a2 == 0)
			goto finish;
		id = *a2;
		if (*(char*) (((char *)&((OBJECT_PROTOTYPE *)lpObjektePROT)[(unsigned int) id])) == 6) {
			if (id >= 0x91 && id <= 0x97)
				result = 1;
			else
				result = 0xffffffff;
			result |= 0x4000;
		} else {
			if (id >= 0x91 && id <= 0x97)
				result = 1;
			else
				result = id == 0xfd ? 0x4001 : 0xffffffff;
		}
	}
common:
	if (a2 != 0) {
		id = *a2;
		if (id == 0x27f || id == 0x21b || id == 0x28a || id == 0x120)
			result |= 0x5000;
		if (id == 0x12e)
			result |= 0x4000;
	}
finish:
	if (g_774800 != 0) {
		result = 0xffffffff;
		if (a1 != 0 && (*rec == 3 || *rec == 0x21))
			result = 0xfffffffe;
	}
	if (a1 != 0 && *(unsigned short*) (a1 + 0x27) == 0xffff)
		result = 0;
	return result;
}
