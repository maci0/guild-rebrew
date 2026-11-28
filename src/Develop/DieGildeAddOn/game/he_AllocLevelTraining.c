#include "Develop/client_types.h"

extern pos14_7f4c00 gm_GameTime;

int __cdecl he_fn_Handlung(void);
int __cdecl cm_SendSetHE(char a1, unsigned char* e);
struct unit* __cdecl he_StartHandlungSearch(int n, ...);

/* ADDRESS: GOLDTL 0x00551650 */
void __cdecl he_AllocLevelTraining(char* e)
{
	int entry;

	entry = (int) he_StartHandlungSearch(2, 0, 0x5e, 2, (unsigned int) *(unsigned short*) (e + 8));
	while (entry != 0) {
		if (entry != (int) e) {
			*(pos14_7f4c00*) (e + 0x52) = gm_GameTime;
			*(int*) (e + 0x84) = cm_SendSetHE(-1, (unsigned char*) e);
			return;
		}
		entry = (int) he_fn_Handlung();
	}
	*(int*) (e + 0x70) = 0;
	*(char*) (e + 0xb8) = 0;
	*(int*) (e + 0x84) = cm_SendSetHE(0, (unsigned char*) e);
}
