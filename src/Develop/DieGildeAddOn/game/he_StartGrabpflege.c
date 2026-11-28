void __cdecl he_FreeAction(char*);

#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;




unsigned short* __cdecl gm_LookupEntityRecordById(int);
char* __cdecl gm_SearchTable67(int);
char* __cdecl gm_QueryEntities(int, int, int, int);
void __cdecl he_AssignActionSlot(char*, char*, int, char*);
void __cdecl gm_AddTime(pos14_7f4c00*, int, int, int);

void __cdecl he_StartGrabpflege(char* o)
{
	unsigned short* x;
	char* r;
	char* q;

	x = gm_LookupEntityRecordById(*(int*) (o + 0x8c));
	if (x != 0) {
		r = gm_SearchTable67(*(int*) (o + 0x10));
		if (r != 0) {
			q = gm_QueryEntities(*(int*) (r + 0x5d), 1, 0, 0xfd);
			he_AssignActionSlot(r, q, *x, o);
			*(int*) (o + 0xac) = 0;
			*(int*) (o + 0xb8) = 0x1fe;
			*(pos14_7f4c00*) (o + 0xbc) = gm_GameTime;
			*(pos14_7f4c00*) (o + 0x52) = gm_GameTime;
			*(int*) (o + 0x70) = 0;
			gm_AddTime((pos14_7f4c00*) (o + 0x52), 0, 5, 0);
			return;
		}
	}
	he_FreeAction(o);
}
