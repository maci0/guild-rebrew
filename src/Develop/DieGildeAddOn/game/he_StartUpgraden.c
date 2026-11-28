char* __cdecl gm_LookupEntityRecordById(int);
char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
int __cdecl fcn_00502cd0(int, int, int, int, int);
int __cdecl he_AssignActionSlot(char*, int, int, char*);
int __cdecl gm_AddTime(char*, int, int, int);
int __cdecl he_FreeAction(char*);

#include "Develop/client_types.h"

extern pos14_7f4c00 gm_GameTime;

/* ADDRESS: GOLDTL 0x0057a260 */
int __cdecl he_StartUpgraden(char* p)
{
	int v;
	char* s;
	char* e;

	v = 0;
	s = (char*) gm_LookupEntityRecordById(*(int*)(p + 0xac));
	if (s != 0
	    && (*(char**)(s + 0x17c) == 0 || *(unsigned char*)*(char**)(s + 0x17c) != 0x8f)
	    && (e = (char*) gm_StartFilteredEntitySearch(1, 1, *(int*)(p + 0x10))) != 0) {
		if (*(int*)(p + 0xb4) != -1)
			v = fcn_00502cd0(*(int*)(e + 0x5d), 2, 6, 1, *(int*)(p + 0xb4));
		*(pos14_7f4c00*) (p + 0x52) = gm_GameTime;
		*(pos14_7f4c00*) (p + 0x44) = gm_GameTime;
		if (v)
			he_AssignActionSlot(e, v, *(unsigned short*)s, p);
		else
			he_AssignActionSlot(e, 0, *(unsigned short*)s, p);
		*(pos14_7f4c00*) (p + 0x60) = gm_GameTime;
		gm_AddTime(p + 0x52, 0, 0x1e, 0);
		*(pos14_7f4c00*) (p + 0xb8) = *(pos14_7f4c00*) (p + 0x52);
		return gm_AddTime(p + 0xb8, 3, 0, 0);
	}
	return he_FreeAction(p);
}
