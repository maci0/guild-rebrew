


typedef char* (__cdecl* pagefn)(void);

#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_774a18;
extern char* g_774a10;
extern int g_6a81dc[5];
extern pagefn g_6a81f0[5];
extern int* d2_TutorialState;
extern volatile int gm_GameTicks;

char* __cdecl d2_InitTutorialMainIntro(void);
char* __cdecl d2_InitTutorialMainOutro(void);
void __cdecl d2_ShutdownTutorial(void);
int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_SetFormVisibility(int, int);
void __cdecl d2_CenterForm(int, int);

/* ADDRESS: GOLDDE 0x005667a0 */
int __cdecl d2_StartTutorial(void)
{
	char* p;
	int n;
	int i;

	if (d2_TutorialActive != 0) {
		return -3;
	}
	n = 0;
	for (i = 0; i < 5; i++) {
		if (g_6a81dc[i] == 1) {
			n++;
		}
	}
	if (n == 0) {
		return -2;
	}
	g_774a10 = d2_InitTutorialMainIntro();
	if (g_774a10 == 0) {
		goto fail;
	}
	p = g_774a10;
	while (*(char**) (p + 0x70) != 0) {
		p = *(char**) (p + 0x70);
	}
	for (i = 0; i < 5; i++) {
		if (g_6a81dc[i] == 1) {
			*(char**) (p + 0x70) = g_6a81f0[i]();
			if (*(char**) (p + 0x70) == 0) {
				goto fail;
			}
			while (*(char**) (p + 0x70) != 0) {
				p = *(char**) (p + 0x70);
			}
		}
	}
	*(char**) (p + 0x70) = d2_InitTutorialMainOutro();
	if (*(char**) (p + 0x70) == 0) {
fail:
		d2_ShutdownTutorial();
		return -1;
	}
	d2_TutorialState[0] = 1;
	d2_TutorialState[1] = 1;
	d2_TutorialState[2] = gm_GameTicks;
	d2_TutorialState[3] = gm_GameTicks;
	d2_TutorialState[4] = 0;
	d2_TutorialState[5] = 0;
	d2_TutorialState[6] = (int) g_774a10;
	d2_TutorialState[5] = 0;
	d2_TutorialState[7] = 0;
	d2_TutorialState[8] = -1;
	d2_TutorialState[9] = d2_LoadForm(0, 0, "tutorial\\inline_form");
	d2_SetFormVisibility(d2_TutorialState[9], 0);
	d2_CenterForm(d2_TutorialState[9], 3);
	d2_TutorialState[10] = 0;
	d2_TutorialState[11] = 0;
	d2_TutorialState[12] = 0;
	d2_TutorialState[13] = d2_LoadForm(0, 0, "tutorial\\aux_form");
	d2_SetFormVisibility(d2_TutorialState[13], 0);
	d2_CenterForm(d2_TutorialState[13], 3);
	d2_TutorialState[15] = 0;
	d2_TutorialState[16] = 0;
	d2_TutorialState[22] = 0;
	d2_TutorialState[21] = 0;
	d2_TutorialState[23] = 0;
	d2_TutorialState[24] = -1;
	d2_TutorialState[26] = -1;
	d2_TutorialState[27] = -1;
	d2_TutorialActive = 1;
	g_774a18 = 1;
	return 0;
}
