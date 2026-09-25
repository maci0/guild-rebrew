// FUNCTION: GOLDTL 0x4da480
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
extern Ent21c g_7f4ca0[768];
extern Ent21c* g_7e4260[32];

void __cdecl fcn_004da480(void)
{
	int self;
	int n;
	int i;

	self = g_67a370;
	memset(g_7e4260, 0, sizeof(g_7e4260));
	n = 0;
	for (i = 0; i < 768; i++) {
		if (n >= 31) {
			break;
		}
		if (g_7f4ca0[i].ref != 0 && *(int*) (g_7f4ca0[i].ref + 0x88) == self) {
			g_7e4260[n] = &g_7f4ca0[i];
			n++;
		}
	}
}
