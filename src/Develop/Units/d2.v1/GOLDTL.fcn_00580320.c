


extern int* g_665f08;
extern char g_6b5c60[];
#include "Develop/DieGildeAddOn/game/game_data.h"

void __cdecl fcn_00533a40(char*);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(char*, ...);
void __cdecl fcn_00471af0(int, int);
int __cdecl fcn_00423460(int);
void __cdecl sb_StopVoice(int, int);
int __cdecl d3snd_PlaySoundEffect(int, int, int, int);

void __cdecl fcn_00580320(void)
{
	if (g_665f08[6] != 0 && *(int*) (g_665f08[6] + 0x14) != 0) {
		fcn_00533a40(g_6b5c60);
		d2_SetForm(g_665f08[9], 0);
		io_AppendText(g_6811b0);
		io_AppendText(*(char**) (g_665f08[6] + 0x14));
		fcn_00471af0(g_665f08[9], 1);
		if (*(int*) (g_665f08[6] + 0x18) != 0) {
			if (g_665f08[5] != 0) {
				if (fcn_00423460(g_665f08[5]) != 0) {
					sb_StopVoice(g_665f08[5], 0);
				}
				g_665f08[5] = 0;
			}
			g_665f08[5] = d3snd_PlaySoundEffect(-7, 0, *(int*) (g_665f08[6] + 0x18), -1);
		}
	}
}
