

#include <string.h>

typedef struct
{
	char pad[0x184];
	char* ref;
	char tail[0x94];
} Ent21c;
// SIZE 0x21c

extern int g_67a370;
extern int g_9b4a40[];
extern char* ch_ContextCharacters[32];

void __cdecl cut_RefreshCombatContextCharacters(void)
{
	int self;
	int n;
	int i;

	self = g_67a370;
	memset(((Ent21c**)ch_ContextCharacters), 0, sizeof(Ent21c*[32]));
	n = 0;
	for (i = 0; i < 32; i++) {
		if (n >= 31) {
			break;
		}
		if (((Ent21c*) g_9b4a40)[i].ref != 0 && *(int*) (((Ent21c*) g_9b4a40)[i].ref + 0x88) == self) {
			((Ent21c**)ch_ContextCharacters)[n] = &((Ent21c*) g_9b4a40)[i];
			n++;
		}
	}
}
