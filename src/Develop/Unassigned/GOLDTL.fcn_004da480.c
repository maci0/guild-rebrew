


#include <string.h>

typedef struct
{
	char pad[0x184];
	char* ref;
	char tail[0x94];
} Ent21c;
// SIZE 0x21c

extern int g_67a370;
extern char g_7f4ca0[];
extern char* g_7e4260[32];

void __cdecl fcn_004da480(void)
{
	int self;
	int n;
	int i;

	self = g_67a370;
	memset(((Ent21c**)g_7e4260), 0, sizeof(Ent21c*[32]));
	n = 0;
	for (i = 0; i < 768; i++) {
		if (n >= 31) {
			break;
		}
		if (((Ent21c*)g_7f4ca0)[i].ref != 0 && *(int*) (((Ent21c*)g_7f4ca0)[i].ref + 0x88) == self) {
			((Ent21c**)g_7e4260)[n] = &((Ent21c*)g_7f4ca0)[i];
			n++;
		}
	}
}
