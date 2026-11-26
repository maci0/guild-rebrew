


// SIZE 0xe
typedef struct {
	char b[14];
} Stamp;

#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;
#include "Develop/DieGildeAddOn/game/entity_record.h"

char* __cdecl he_StartHandlungSearch(int, int, int);
char* __cdecl he_fn_Handlung(void);
void __cdecl he_NotifyAction0x35Blocked(char*, char*);
void __cdecl cm_SendSetHE(int, char*);

int __cdecl gm_ObjTriggerAction0x35(char* e)
{
	char* p;

	for (p = he_StartHandlungSearch(1, 0, 0x35); p != 0; p = he_fn_Handlung()) {
		if (*(int*) (e + 4) == *(int*) (p + 0xbc)) {
			he_NotifyAction0x35Blocked(e, ((char*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[*(unsigned short*) (p + 8)]));
			*(Stamp*) (p + 0x52) = (*(Stamp*)&gm_GameTime);
			cm_SendSetHE(-1, p);
		}
	}
	return 1;
}
