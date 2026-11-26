


#include <string.h>

// SIZE 0x21c
#include "Develop/DieGildeAddOn/game/entity_record.h"








extern unsigned char g_773d75;

char* __cdecl gm_LookupEntityRecordById(int);
int __cdecl fcn_0050f950(int, int);
char* __cdecl fcn_00502cd0();
char* __cdecl gm_FindBuildingPrimarySlot(char*);
char* __cdecl gm_NextEntityQueryMatch(void);
unsigned short __cdecl gm_RandomMod(int);
float __cdecl fcn_0050bb50(int, unsigned char);
int __cdecl cm_SendSellObjekt(int, int, int, int, unsigned char, int);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl he_MessageBoxQuickjump(int, int, char*, int, int, int, int, int, char*);
void __cdecl he_FreeAction(char*);
int __cdecl fcn_0051e070(void);

void __cdecl he_RunFriedhofStealAction(char* e)
{
	char* q;
	char* o;
	char* list[32];
	char buf[0x400];
	char* p;
	char* r;
	char* c;
	char* sel;
	int n;

	switch (*(int*) (e + 0x70)) {
	case -2:
	case -1:
		he_FreeAction(e);
		return;
	case 0:
		break;
	default:
		return;
	}
	o = gm_LookupEntityRecordById(*(int*) (e + 0xac));
	if (o == 0 || (p = *(char**) (o + 0x16c)) == 0
	    || fcn_0050f950(*(unsigned short*) (p + 0x27), *(unsigned short*) o) > -26) {
		he_FreeAction(e);
		return;
	}
	r = fcn_00502cd0(*(int*) (p + 0x5d), 2, 6, 0, 0x2a);
	if (r == 0) {
		r = fcn_00502cd0(*(int*) (p + 0x5d), 2, 6, r, 0x116);
	}
	q = gm_FindBuildingPrimarySlot(p);
	if (r != 0) {
		n = 0;
		memset(list, 0, sizeof(list));
		for (c = fcn_00502cd0(*(int*) (r + 0x14), 1, 5); c != 0; c = gm_NextEntityQueryMatch()) {
			list[n++] = c;
		}
		if (n != 0) {
			sel = list[gm_RandomMod(n)];
			if (sel != 0) {
				fcn_0050bb50(*(unsigned short*) sel, g_773d75);
				cm_SendSellObjekt(-1, *(int*) (r + 2), *(unsigned short*) sel, 1, g_773d75, 0);
				switch (fcn_0051e070()) {
				case 0:
				case 2:
					io_FormatTextBuffer(buf, 0x414b, 0x229, *(int*) (o + 0x16c), *(unsigned short*) sel * 2 + 0x9a8);
					break;
				case 1:
					io_FormatTextBuffer(buf, 0x414b, 0x229, *(unsigned short*) sel * 2 + 0x9a8, *(int*) (o + 0x16c));
					break;
				}
				he_MessageBoxQuickjump(((ENTITY_RECORD_VIEW*)g_7f4ca0)[*(unsigned short*) (e + 8)].entity_id, -1, buf, 0, 0x5f2, *(int*) (p + 1),
				    *(int*) (q + 2), 0, "_NACHRICHTEN_FRIEDHOF_06");
			}
		}
	}
	he_FreeAction(e);
}
