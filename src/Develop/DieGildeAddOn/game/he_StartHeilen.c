


#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;

char* __cdecl gm_LookupEntityRecordById(int);
char* __cdecl gm_SearchTable67(int);
int __cdecl gm_FindRecordById(int);
void __cdecl he_AssignActionSlot(char*, int, int, char*);
void __cdecl gm_AddTime(pos14_7f4c00*, int, int, int);

/* ADDRESS: GOLDDE 0x00553b10 */
void __cdecl he_StartHeilen(char* u)
{
	char* h;
	char* t;
	int rec;

	rec = 0;
	h = gm_LookupEntityRecordById(*(int*) (u + 0xac));
	t = gm_SearchTable67(*(int*) (u + 0x10));
	if (*(int*) (u + 0xc4) != -1) {
		rec = gm_FindRecordById(*(int*) (u + 0xc4));
	}
	he_AssignActionSlot(t, rec, *(unsigned short*) h, u);
	*(int*) (u + 0xb0) = 200;
	*(pos14_7f4c00*) (u + 0xb4) = gm_GameTime;
	*(pos14_7f4c00*) (u + 0x44) = gm_GameTime;
	*(pos14_7f4c00*) (u + 0x52) = gm_GameTime;
	*(pos14_7f4c00*) (u + 0x60) = gm_GameTime;
	gm_AddTime((pos14_7f4c00*) (u + 0xb4), 0, 400, 0);
}
