typedef struct {
	char c[0x18];
} DuelActionAnim;
// SIZE 0x18

#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_68bfc0;
extern char* cut_DuelFighterB;
extern char cut_DuelAccuracyBoostA;
extern char cut_DuelAccuracyBoostB;
extern char cut_DuelDamageReductionA;
extern char cut_DuelDamageReductionB;
extern DuelActionAnim g_68cc34;

unsigned char* __cdecl gm_FindPlayerById(int);
int __cdecl d2_SetForm(int, int);
char* __cdecl io_AppendText(int, ...);
int __cdecl gm_NextCyclicShuffledIndex(int);
int __cdecl d3snd_PlaySoundEffect(int, int, char*, int);
void __cdecl cut_WaitTicks(int);
char* __cdecl ch_CreateQueuedAction(char*, void*, int, int, int);
void __cdecl cut_ResolveDuelShot(void);
#include "Develop/DieGildeAddOn/game/spiel.h"
float __cdecl cut_RandFloat(void);
int __cdecl ch_QueuePlayAnimation(char*, const char*, int);


/* Duel intro: plays the challenger's opening move chosen by the duel kind. */
/* ADDRESS: GOLDTL 0x004e0210 */
/* ADDRESS: GOLDDE 0x004ccc30 */
void __cdecl cut_PlayDuelIntroMove(char* e, char* foe)
{
	unsigned char* d;
	int t;
	char* o;
	float a;
	float b;

	if (g_772f44 == 0) {
		d = gm_FindPlayerById(*(int*) (e + 4));
		d2_SetForm(g_68bfc0, 0);
		io_AppendText((int) "$C");
		switch (d[0x94]) {
		case 4:
			d2_SetForm(g_68bfc0, 0);
			t = gm_NextCyclicShuffledIndex(7);
			io_AppendText(t + 0x10fa, *(unsigned short*) e);
			d3snd_PlaySoundEffect(*(unsigned short*) e, 0, "_DUELL_INTRO_C2_AUSWAHL_SCHIESSEN", t);
			cut_WaitTicks(2);
			io_AppendText((int) "$N");
			o = ch_CreateQueuedAction(*(char**) (e + 0x184), (void*) cut_ResolveDuelShot, 6, 0x2e, 1);
			*(char**) (o + 0x17c) = foe;
			*(char**) (o + 0x180) = e;
			*(DuelActionAnim*) (o + 0xf0) = g_68cc34;
			break;
		case 3:
			d2_SetForm(g_68bfc0, 0);
			a = gm_GetEntitySkill(e, 2);
			if (cut_RandFloat() < a) {
				if (e[2] == 6 || e[2] == 7) {
					io_AppendText(0x10f6, *(unsigned short*) e);
				} else {
					io_AppendText(0x10f7, *(unsigned short*) e);
				}
				if (e == cut_DuelFighterB) {
					cut_DuelDamageReductionA = 1;
				} else {
					cut_DuelDamageReductionB = 1;
				}
			} else {
				if (e[2] == 6 || e[2] == 7) {
					io_AppendText(0x10f8, *(unsigned short*) e);
				} else {
					io_AppendText(0x10f9, *(unsigned short*) e);
				}
			}
			io_AppendText((int) "$N");
			break;
		case 2:
			d2_SetForm(g_68bfc0, 0);
			io_AppendText(0x10e8, *(unsigned short*) e);
			t = gm_NextCyclicShuffledIndex(8);
			io_AppendText(t + 0x10e9);
			d3snd_PlaySoundEffect(*(unsigned short*) e, 0, "_DUELL_INTRO_C2_AUSWAHL_LAESTERN", t);
			io_AppendText((int) "$N");
			ch_QueuePlayAnimation(*(char**) (e + 0x184), "gestik/abfaellig", 1);
			cut_WaitTicks(2);
			a = gm_GetEntitySkill(e, 4);
			b = gm_GetEntitySkill(foe, 4);
			a += cut_RandFloat();
			if (cut_RandFloat() + b < a) {
				d2_SetForm(g_68bfc0, 0);
				if (foe[2] == 6 || foe[2] == 7) {
					io_AppendText(0x10f2, *(unsigned short*) foe);
				} else {
					io_AppendText(0x10f3, *(unsigned short*) foe);
				}
				if (e == cut_DuelFighterB) {
					cut_DuelAccuracyBoostA = 1;
				} else {
					cut_DuelAccuracyBoostB = 1;
				}
			} else {
				d2_SetForm(g_68bfc0, 0);
				if (foe[2] == 6 || foe[2] == 7) {
					io_AppendText(0x10f4, *(unsigned short*) foe);
				} else {
					io_AppendText(0x10f5, *(unsigned short*) foe);
				}
			}
			io_AppendText((int) "$N");
			break;
		}
		cut_WaitTicks(4);
	}
}
