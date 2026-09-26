// FUNCTION: GOLDTL 0x4d1a80
// SIZE: 80

#include <string.h>

typedef struct
{
	char pad[0x184];
	char* ref;
	char tail[0x94];
} Ent21c;
// SIZE 0x21c

extern int g_67a370;
extern Ent21c g_9b4a40[32];
extern char* g_7e4260[32];

void __cdecl fcn_004d1a80(void)
{
	int self;
	int n;
	int i;

	self = g_67a370;
	memset(((Ent21c**)g_7e4260), 0, sizeof(Ent21c*[32]));
	n = 0;
	for (i = 0; i < 32; i++) {
		if (n >= 31) {
			break;
		}
		if (g_9b4a40[i].ref != 0 && *(int*) (g_9b4a40[i].ref + 0x88) == self) {
			((Ent21c**)g_7e4260)[n] = &g_9b4a40[i];
			n++;
		}
	}
}
