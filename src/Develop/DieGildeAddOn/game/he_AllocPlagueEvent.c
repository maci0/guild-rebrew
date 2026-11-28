int __cdecl cm_SendSetHE(int, char*);

#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;




char* __cdecl he_StartHandlungSearch(int, int, int, ...);
char* __cdecl he_fn_Handlung(void);

/* ADDRESS: GOLDDE 0x005385d0 */
void __cdecl he_AllocPlagueEvent(char* o)
{
	char* p;

	if (o[0x78] & 4) {
		return;
	}
	for (p = he_StartHandlungSearch(1, 0, 0x59); p != 0; p = he_fn_Handlung()) {
		if (p != o) {
			*(pos14_7f4c00*) (o + 0x52) = gm_GameTime;
			*(int*) (o + 0x84) = cm_SendSetHE(-1, o);
			return;
		}
	}
	*(int*) (o + 0x70) = 5;
	*(pos14_7f4c00*) (o + 0x52) = *(pos14_7f4c00*) (o + 0x44);
	*(int*) (o + 0x84) = -1;
	cm_SendSetHE(5, o);
}
