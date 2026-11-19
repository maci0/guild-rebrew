


typedef struct
{
	int used;
	int x4;
	int x8;
	int xc;
	int x10;
	char name[0x348];
} Player35c;
// SIZE 0x35c

#include "Develop/DieGildeAddOn/game/game_data.h"
extern char g_68b300[];

void __cdecl d2_SetForm(int, int);
void __cdecl io_AppendText(char*);

void __cdecl fcn_004e5140(unsigned char* ctx)
{
	int i;

	for (i = 0; i < ctx[0x30]; i++) {
		if (((Player35c*)g_9b0e20)[i].xc == 0 && ((Player35c*)g_9b0e20)[i].x8 != 0) {
			d2_SetForm(*(int*) (ctx + 0x2c), 0);
			io_AppendText(((Player35c*)g_9b0e20)[i].name);
			io_AppendText(g_68b300);
			((Player35c*)g_9b0e20)[i].xc = 1;
		}
	}
}
