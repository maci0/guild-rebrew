

extern int g_7746a0;
#include "Develop/DieGildeAddOn/game/game_player.h"
#include "Develop/DieGildeAddOn/game/entity_record.h"
extern int g_14aac94;
extern char g_6aafac[];

void __cdecl fcn_005338a0(void);
int __cdecl fcn_005373e0(void*, int);
int __cdecl RegisterStatusText(char*, int, int);
int __cdecl fcn_004eb260(char*);
void __cdecl fcn_005aa390(int);

/* ADDRESS: GOLD 0x5a1a20 */
void __cdecl fcn_005aad40(int a)
{
	int x;

	x = 0;
	fcn_005338a0();
	while (fcn_005373e0(fcn_005aad40, 0x67fff) != 0) {
		if (fcn_004eb260(((char*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[g_774970])) != 0) {
			x = RegisterStatusText(g_6aafac, g_14aac94, 0x16);
		}
		if (g_7746a0 != 0 && g_7746a0 == x) {
			fcn_005aa390(a);
		}
	}
}
