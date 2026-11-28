typedef struct Kind {
	unsigned char type;
	char pad1[0x24c];
} Kind;
// SIZE 0x24d
#include "Develop/DieGildeAddOn/game/building_prototype.h"
extern unsigned char* lpGebaeudePROT;
extern unsigned char* lpGebaeudeINST;
extern char gm_EntitySlotTable[];

int __cdecl gm_CheckStatLevel(int, int);
char* __cdecl gm_QueryEntities(int, int, int, int, int);
unsigned short __cdecl gm_RandomMod(unsigned short);
int __cdecl ai_SelectRankedCandidates(unsigned short* e, int n, int* lim, float a4, float r, unsigned short* ids);


/* ADDRESS: GOLDTL 0x004abe20 */
int __cdecl ai_StartEhrerbietung(int a1, unsigned short* entity, int a3, char* result)
{
	int lim;
	unsigned short id;
	int lvl;
	int n;
	int i;
	unsigned char* e;
	char* p;

	lvl = gm_CheckStatLevel(*entity, 0xe);
	lim = 0;
	if ((*((unsigned char*) entity + 0x1cc) & 0x20) != 0)
		return 0;
	if (*(int*) ((char*) entity + 0x194) < 2)
		return 0;
	if (a1 != 0x47 && a1 != 0)
		return 0;
	if (a3 != 0 || lvl == 0 || *((unsigned char*) entity + 2) == 3)
		return 0;
	e = lpGebaeudeINST;
	for (i = 0; i < 0x100; i++, e += 0xa9) {
		if (e[0] != 0 && *(unsigned short*) (e + 0x27) == *entity
		    && ((BUILDING_PROTOTYPE*)lpGebaeudePROT)[e[0]].category == 0x1f
		    && gm_QueryEntities(*(int*) (e + 0x5d), 2, 6, 0, 0x276) != 0) {
			lim = 0xf00500;
			if (ai_SelectRankedCandidates(entity, 1, &lim, 0.0f, gm_RandomMod(0x20) + 25.0f, &id) == 0)
				return 0;
			p = gm_EntitySlotTable + id * 540;
			n = *(int*) ((char*) entity + 0x194);
			if (n >= 8)
				n = 8;
			n = gm_RandomMod(n);
			if (n <= 2)
				n = 2;
			*(int*) (result + 4) = *(int*) (p + 4);
			*(int*) (result + 0x10) = n;
			*(int*) (result + 0xc) = 0;
			result[0] = 7;
			return 0x45;
		}
	}
	return 0;
}
