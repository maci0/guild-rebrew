






// SIZE 0xe

#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;

unsigned char* __cdecl he_StartHandlungSearch(int, int, int);
unsigned char* __cdecl he_fn_Handlung(void);
void __cdecl cm_SendSetHE(int, unsigned char*);

void __cdecl he_CancelErforschenActions(char* object)
{
	unsigned char* p;

	for (p = he_StartHandlungSearch(1, 3, *(int*) (object + 1)); p != 0; p = he_fn_Handlung()) {
		if (*p >= 0x95 && *p <= 0x97) {
			*(pos14_7f4c00*) (p + 0x52) = (*(pos14_7f4c00*)&gm_GameTime);
			cm_SendSetHE(-2, p);
		}
	}
}
