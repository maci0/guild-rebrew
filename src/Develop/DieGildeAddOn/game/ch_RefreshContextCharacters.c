


#include <string.h>

typedef struct
{
	char pad[0x184];
	char* ref;
	char tail[0x94];
} Ent21c;
// SIZE 0x21c

extern int d3_ActiveScene;
#include "Develop/DieGildeAddOn/game/entity_record.h"
extern char* ch_ContextCharacters[32];

void __cdecl ch_RefreshContextCharacters(void)
{
	int self;
	int n;
	int i;

	self = d3_ActiveScene;
	memset(((Ent21c**)ch_ContextCharacters), 0, sizeof(Ent21c*[32]));
	n = 0;
	for (i = 0; i < 768; i++) {
		if (n >= 31) {
			break;
		}
		if ((*(char**)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[i].ptr_184) != 0 && *(int*) ((*(char**)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[i].ptr_184) + 0x88) == self) {
			((Ent21c**)ch_ContextCharacters)[n] = ((Ent21c*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[i]);
			n++;
		}
	}
}
