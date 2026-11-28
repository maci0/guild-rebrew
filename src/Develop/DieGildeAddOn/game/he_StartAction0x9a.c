#include "Develop/client_types.h"

extern pos14_7f4c00 gm_GameTime;
char* __cdecl gm_LookupEntityRecordById(int);
int __cdecl he_HasNoActiveAction0x9a(int, char*);
void __cdecl gm_AddTime(void*, int, int, int);
int __cdecl cm_SendSetHE(char, unsigned char*);

/* ADDRESS: GOLDTL 0x005776a0 */
/* ADDRESS: GOLDDE 0x0055d5d0 */
int __cdecl he_StartAction0x9a(unsigned char* e)
{
	int r;

	*(pos14_7f4c00*) (e + 0x52) = gm_GameTime;
	if (he_HasNoActiveAction0x9a(*(int*) (e + 0xac), gm_LookupEntityRecordById(*(int*) (e + 0xb0))) != 0) {
		gm_AddTime(e + 0x52, 0x18, 0, 0);
		cm_SendSetHE(0, e);
	}
	r = cm_SendSetHE(-1, e);
	*(int*) (e + 0x84) = r;
	return r;
}
