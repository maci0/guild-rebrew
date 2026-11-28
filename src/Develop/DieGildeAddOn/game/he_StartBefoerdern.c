void __cdecl he_FreeAction(char*);

#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;




char* __cdecl he_StartHandlungSearch(int, int, int, ...);
char* __cdecl he_fn_Handlung(void);
char* __cdecl gm_LookupEntityRecordById(int);
void __cdecl gm_AddTime(pos14_7f4c00*, int, int, int);
void __cdecl cm_RequestChangeBits(int, int, int, int, int);

void __cdecl he_StartBefoerdern(char* o)
{
	char* p;
	char* e;

	for (p = he_StartHandlungSearch(1, 0, 0x32); p != 0; p = he_fn_Handlung()) {
		if (p != o && *(int*) (o + 0xac) == *(int*) (p + 0xac)) {
			he_FreeAction(o);
			return;
		}
	}
	*(int*) (o + 0xb0) = -1;
	*(pos14_7f4c00*) (o + 0x52) = gm_GameTime;
	gm_AddTime((pos14_7f4c00*) (o + 0x52), 0, 0, 1);
	e = gm_LookupEntityRecordById(*(int*) (o + 0xac));
	if (e == 0) {
		he_FreeAction(o);
		return;
	}
	if (o[0x78] & 2) {
		cm_RequestChangeBits(*(int*) (e + 4), 0x1cc, 4, 0x1000000, 0);
	}
}
