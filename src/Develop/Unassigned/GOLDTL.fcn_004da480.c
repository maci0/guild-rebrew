


#include <string.h>

typedef struct
{
	char pad[0x184];
	char* ref;
	char tail[0x94];
} Ent21c;
// SIZE 0x21c

extern int g_67a370;
#include "Develop/DieGildeAddOn/game/entity_record.h"
extern char* ch_ContextCharacters[32];

void __cdecl ch_RefreshContextCharacters(void)
{
	int self;
	int n;
	int i;

	self = g_67a370;
	memset(((Ent21c**)ch_ContextCharacters), 0, sizeof(Ent21c*[32]));
	n = 0;
	for (i = 0; i < 768; i++) {
		if (n >= 31) {
			break;
		}
		if ((*(char**)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[i].ptr_184) != 0 && *(int*) ((*(char**)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[i].ptr_184) + 0x88) == self) {
			((Ent21c**)ch_ContextCharacters)[n] = ((Ent21c*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[i]);
			n++;
		}
	}
}
