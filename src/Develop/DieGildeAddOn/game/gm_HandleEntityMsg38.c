#include <string.h>
#include "Develop/DieGildeAddOn/game/object_prototype.h"
#pragma pack(push, 1)
typedef struct Rec {
	char type;
	char pad1[0x40];
} Rec;
// SIZE 0x41
#pragma pack(pop)

extern char* lpObjektePROT;
extern unsigned char gm_ActiveTownIndex;

unsigned short __cdecl gm_RandomMod(int);
unsigned char* __cdecl gm_LookupEntityRecordById(int);
int __cdecl gm_HasActiveSpecialObject(void*, int);
unsigned short* __cdecl gm_QueryEntities(int, int, int);
unsigned short* __cdecl gm_NextEntityQueryMatch(void);
int __cdecl cm_SendSellObjekt(int, int, int, int, unsigned char, int);
void __cdecl io_FormatTextBuffer(char*, int, int);
void __cdecl he_PostEntityMessage(int, int, char*, int, int, int);


/* ADDRESS: GOLDTL 0x004bb0b0 */
/* ADDRESS: GOLDDE 0x004a9120 */
int __cdecl gm_HandleEntityMsg38(int* request)
{
	unsigned short* found[6];
	char buf[0x100];
	unsigned char* p;
	unsigned short* e;
	int n;

	n = 0;
	p = gm_LookupEntityRecordById(*request);
	if (p == 0) {
		return 1;
	}
	if (gm_RandomMod(0x100) < p[0x82]) {
		return 0x400;
	}
	if (gm_HasActiveSpecialObject(p, 0x290) != 0) {
		return 0x400;
	}
	e = gm_QueryEntities(*(int*) (p + 0x178), 1, 5);
	while (e != 0 && n < 6) {
		if ((*(char *)&((OBJECT_PROTOTYPE*)lpObjektePROT)[*e].kind) != 9) {
			found[n] = e;
			n++;
		}
		e = gm_NextEntityQueryMatch();
	}
	if (n == 0) {
		return 0x400;
	}
	e = found[gm_RandomMod(n)];
	cm_SendSellObjekt(-1, *(int*) (p + 4), *e, 1, gm_ActiveTownIndex, 0);
	io_FormatTextBuffer(buf, *(unsigned short*) ((char*) request + 4) + 0x12e7, *e * 2 + 0x9a8);
	he_PostEntityMessage(*(int*) (p + 4), *(int*) (p + 4), buf, 0x100 < strlen(buf), 0x603, 0);
	return 0;
}
