#include "client_types.h"

extern pos14_7f4c00 gm_GameTime;
char* __cdecl gm_LookupEntityRecordById(int);
int __cdecl he_HasNoActiveAction0x9a(int, char*);
void __cdecl gm_AddTime(void*, int, int, int);
int __cdecl fcn_004c5620(char, unsigned char*);

/* ADDRESS: GOLDTL 0x005776a0 */
int __cdecl fcn_005776a0(unsigned char* e)
{
	int r;

	*(pos14_7f4c00*) (e + 0x52) = gm_GameTime;
	if (he_HasNoActiveAction0x9a(*(int*) (e + 0xac), gm_LookupEntityRecordById(*(int*) (e + 0xb0))) != 0) {
		gm_AddTime(e + 0x52, 0x18, 0, 0);
		fcn_004c5620(0, e);
	}
	r = fcn_004c5620(-1, e);
	*(int*) (e + 0x84) = r;
	return r;
}
