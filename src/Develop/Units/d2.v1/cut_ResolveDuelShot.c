extern int g_68bfc0;
extern char* cut_DuelFighterB;
extern int g_9afde0;
extern char cut_DuelAccuracyBoostA;
extern char cut_DuelAccuracyBoostB;
extern char cut_DuelDamageReductionA;
extern char cut_DuelDamageReductionB;
extern unsigned char g_772f58;
extern unsigned char g_772f59;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern double g_664108;
extern double dbl_1_5;
extern double g_664180;

void __cdecl d2_SetForm(int, int);
float __cdecl gm_GetEntitySkill(char*, int);
int __cdecl gm_HasActiveSpecialObject(void*, int);
float __cdecl cut_RandFloat(void);
int __cdecl cut_RandMod(int);
void __cdecl sb_PlayVoice(char*, char*, int, int, int, int, int);
int __cdecl gm_CheckDuelKnockout(char*, int);
void __cdecl d3_SpawnBlutEffect(char*, int, float, float, float, float);
int __cdecl ch_QueuePlayAnimation(char*, char*, int);
int __cdecl gm_NextCyclicShuffledIndex(int);
char* __cdecl io_AppendText(int, ...);
int __cdecl d3snd_PlaySoundEffect(int, int, char*, int);
float __cdecl gm_ApplyEntityHealthDelta(unsigned short, int);
void __cdecl d3_ScheduleActionTimer(char*, int, int);

/* Resolves the shot of a duel action: the challenger's skill decides whether
 * the bullet hits, the victim takes damage and the matching gesture and log
 * message are played. */
/* ADDRESS: GOLDTL 0x004dff50 */
void __cdecl cut_ResolveDuelShot(char* task)
{
	char* e;
	char* foe;
	float a;
	int n;
	int hit;

	d2_SetForm(g_68bfc0, 0);
	e = *(char**) (task + 0x180);
	foe = *(char**) (task + 0x17c);
	a = gm_GetEntitySkill(e, 3);
	gm_GetEntitySkill(foe, 3);
	a = a * g_664108;
	if (gm_HasActiveSpecialObject(e, 0x16f) != 0) {
		a = a * dbl_1_5;
	}
	if ((e == cut_DuelFighterB && cut_DuelAccuracyBoostB) || (e == (*(char * *)&g_9afde0) && cut_DuelAccuracyBoostA)) {
		a = a * g_664180;
	}
	if (cut_RandFloat() < a) {
		hit = 1;
		if ((e == cut_DuelFighterB && cut_DuelDamageReductionB) || (e == (*(char * *)&g_9afde0) && cut_DuelDamageReductionA)) {
			n = cut_RandMod(0xf) + 5;
		} else {
			n = cut_RandMod(0x1e) + 0xf;
		}
		if (gm_HasActiveSpecialObject(foe, 0x2b5) != 0) {
			n = (int) ((float) n * g_662a6c);
		}
		if (foe == cut_DuelFighterB) {
			g_772f58 = g_772f58 + n;
		} else {
			g_772f59 = g_772f59 + n;
		}
		d3_ScheduleActionTimer(foe, (int) (*(float*) (foe + 0x1c) * 0.01 * n), 0);
	} else {
		hit = 0;
		n = 0;
	}


	sb_PlayVoice(0, (char*) 0x68cbf4, 1, 0x3f, 0x7f, 0, 0);
	if (gm_CheckDuelKnockout(foe, n) == 0) {
		if (hit) {
			d3_SpawnBlutEffect(*(char**) (*(char**) (foe + 0x184) + 0x34), 0x40, 0.25f, 0.1f, 0.14f, 55.0f);
			if (*(int*) (*(char**) (foe + 0x184) + 0x128) == 0) {
				ch_QueuePlayAnimation(*(char**) (foe + 0x184), (char*) 0x68cbe4, 1);
			}
			d2_SetForm(g_68bfc0, 0);
			task = (char*) gm_NextCyclicShuffledIndex(6);
			io_AppendText((int) task + 0x1102, *(unsigned short*) foe);
			d3snd_PlaySoundEffect(*(unsigned short*) foe, 0, (char*) 0x68cbb8, (int) task);
			{
				float x;
				float y;

				y = *(float*) (foe + 0x1c) * 0.01 * n;
				x = (float) *(int*) (foe + 0x24) - y;
				*(int*) (foe + 0x24) = (int) x;
				gm_ApplyEntityHealthDelta(*(unsigned short*) foe, (int) -y);
			}
		} else {
			if (*(int*) (*(char**) (foe + 0x184) + 0x128) == 0) {
				ch_QueuePlayAnimation(*(char**) (foe + 0x184), (char*) 0x68cba0, 1);
			}
			task = (char*) gm_NextCyclicShuffledIndex(9);
			io_AppendText((int) task + 0x1109, *(unsigned short*) foe);
			d3snd_PlaySoundEffect(*(unsigned short*) foe, 0, (char*) 0x68cb74, (int) task);
		}
	} else {
		g_772f44 = 1;
	}
}
