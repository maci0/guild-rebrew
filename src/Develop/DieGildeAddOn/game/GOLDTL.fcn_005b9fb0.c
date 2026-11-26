


// SIZE 0xe
typedef struct {
	char b[14];
} Stamp;

#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;

char* __cdecl he_StartHandlungSearch(int, int, int);
char* __cdecl he_fn_Handlung(void);
void __cdecl cm_SendSetHE(int, char*);

void __cdecl cm_CompleteAction0x0f(char* e)
{
	char* p;

	for (p = he_StartHandlungSearch(1, 0, 0xf); p != 0; p = he_fn_Handlung()) {
		if (*(int*) (p + 0xac) == *(int*) (e + 2)) {
			*(Stamp*) (p + 0x52) = (*(Stamp*)&gm_GameTime);
			cm_SendSetHE(-1, p);
			return;
		}
	}
}
