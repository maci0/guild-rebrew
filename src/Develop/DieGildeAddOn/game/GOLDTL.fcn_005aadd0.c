#include "Develop/DieGildeAddOn/game/entity_record.h"


#include "Develop/DieGildeAddOn/game/game_player.h"
extern char g_7f4ca0[];
extern int g_14abb84;
extern char* txt_TextEntries[];
extern int g_7746a0;

void __cdecl fcn_005338a0(void);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl fcn_005aad40(void);
int __cdecl RegisterStatusText(char*, int, int);
int __cdecl fcn_004eb320(char*);
void __cdecl d2_RunGildenkasseDialog(char*);
void __cdecl fcn_005aac20(void);

void __cdecl d2_RunZunftMenu(char* e)
{
	int a;
	int b;
	int id;
	char lvl;

	b = 0;
	id = 0;
	lvl = ((char *)&((ENTITY_RECORD_VIEW *)g_7f4ca0)[g_774970])[0x169];
	if (lvl == 0x1e) {
		id = 0x167c;
	} else if (lvl == 0x1f || lvl == 0x21) {
		id = 0x166a;
	} else if (lvl == 0x20) {
		id = 0x1674;
	}
	fcn_005338a0();
	while (main_RunFrameLoop((void*) fcn_005aad40, 0x67fff) != 0) {
		a = RegisterStatusText("ob_ZUNFTKASSE", g_14abb84, 0x16);
		if (fcn_004eb320(((char *)&((ENTITY_RECORD_VIEW *)g_7f4ca0)[g_774970])) != 0 && id != 0) {
			b = RegisterStatusText("contact_ZUNFTLEVEL3", ((int*)txt_TextEntries)[id], 0x16);
		}
		if (g_7746a0 != 0) {
			if (g_7746a0 == a) {
				d2_RunGildenkasseDialog(e);
			} else if (g_7746a0 == b) {
				fcn_005aac20();
			}
		}
	}
}
