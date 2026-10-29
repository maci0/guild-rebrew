#include "Develop/DieGildeAddOn/game/spiel.h"



extern char g_6997e8[];


void* __cdecl fcn_00502cd0(int list, int a, int b, int c);
char* __cdecl gm_AllocObjekt(int a, int b, int c);
int __cdecl fcn_00502e30(char* list, int b);
int __cdecl sprintf(char* buf, const char* fmt, ...);

int __cdecl fcn_00503930(int a, int b, int c)
{
	char* list_head;
	void* sta;
	void* exi;
	char* r;
	void* dyn;

	if (!gm_ResolveEntityById((void**) &dyn, (void**) (&exi), (void**) (&sta), a)) {
		return 0;
	}
	if (dyn != 0) {
		list_head = (char*) dyn + 0x5d;
	} else if (exi != 0) {
		list_head = (char*) exi + 0x14;
	} else if (sta != 0) {
		list_head = (char*) sta + 0x178;
	} else {
		return 0;
	}
	r = fcn_00502cd0(*(int*) list_head, 1, 0, b);
	if (r == 0) {
		r = gm_AllocObjekt(a, b, 1);
		*(int*) (r + 0xe) = 0;
	}
	*(int*) (r + 0xe) -= c;
	if (*(int*) (r + 0xe) == 0) {
		fcn_00502e30(list_head, b);
	}
	return 1;
}
