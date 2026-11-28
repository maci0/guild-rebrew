


#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) < (b) ? (b) : (a))

#include "Develop/DieGildeAddOn/game/game_player.h"
extern char gm_InWorldHud;

unsigned char* __cdecl gm_LookupEntityRecordById(int);
void __cdecl main_ExitToFrameHandler(void*);
void __cdecl d2_RunWorldHudLoop(void);
void __cdecl amt_ReleaseEntityOffices(unsigned char*, int);

/* ADDRESS: GOLDDE 0x004bae70 */
int __cdecl cm_ExBlockCharacter(char* x, char* out)
{
	unsigned char* e;
	int v;

	e = gm_LookupEntityRecordById(*(int*) (x + 0x10));
	if (out != 0) {
		out[0] = 2;
		out[1] = 0;
		*(int*) (out + 6) = 0;
	}
	if (e == 0)
		return 1;
	v = e[0x1b1] + *(int*) (x + 0x14);
	e[0x1b1] = MIN(MAX(v, 0), 0xff);
	e[0x1b1] = MAX(0, e[0x1b1]);
	if (*(unsigned short*) e == gm_LocalPlayerSlot && gm_InWorldHud != 0 && e[0x1b1] > 0)
		main_ExitToFrameHandler(d2_RunWorldHudLoop);
	amt_ReleaseEntityOffices(e, *(int*) (x + 0x18));
	if (out != 0)
		out[0] = 1;
	return 0;
}
