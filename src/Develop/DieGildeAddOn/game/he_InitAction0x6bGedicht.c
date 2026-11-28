





// SIZE 0xe

#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;

short __cdecl gm_GetGedichtCount(void);
int __cdecl cm_SendSetHE(int, char*);

/* ADDRESS: GOLDDE 0x0053c080 */
void __cdecl he_InitAction0x6bGedicht(char* e)
{
	if ((e[0x78] & 4) == 0) {
		*(short*) (e + 0xac) = gm_GetGedichtCount();
		*(int*) (e + 0xb4) = -1;
		*(pos14_7f4c00*) (e + 0x52) = (*(pos14_7f4c00*)&gm_GameTime);
		*(int*) (e + 0x84) = cm_SendSetHE(0, e);
	}
}
