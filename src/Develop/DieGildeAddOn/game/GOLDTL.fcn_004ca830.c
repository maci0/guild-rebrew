#include "Develop/DieGildeAddOn/game/ch_motion.h"



#include "Develop/DieGildeAddOn/game/game_data.h"

int __cdecl fcn_0064d41a(char*, char*, ...);
char* __cdecl ch_FindCharacterByName(char*);
#include "Develop/DieGildeAddOn/game/ch_queue.h"
void __cdecl ch_CreateAction(char*, int, int);

int __cdecl fcn_004ca830(char* x, char* out)
{
	char buf[0x80];
	char* o;

	fcn_0064d41a(buf, g_68b0d8, *(int*) (x + 0x10));
	o = ch_FindCharacterByName(buf);
	if (o == 0)
		return 1;
	ch_SetPosition(o, (float*) (x + 0x14), 1);
	if (out != 0) {
		out[0] = 2;
		out[1] = 0;
		*(int*) (out + 6) = 0;
	}
	return 0;
}
