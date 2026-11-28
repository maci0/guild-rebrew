

// SIZE 0x30
typedef struct {
	int h;
	char* sample;
	int prio;
	int loop;
	int time;
	int flags;
	int f18;
	int f1c;
	int f20;
	int vol;
	int pan;
	int f2c;
} Voice;

extern int sb_WaveDriver;
extern char* sb_Voices;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_6b7e90;
extern int g_678dec;
extern volatile int gm_GameTicks;
int __cdecl msx_GetSampleStatus(int h);
void __cdecl sb_StopVoice(Voice* v, int a);

void __cdecl sb_StopAllVoices(int fade)
{
	int i;
	int t;
	Voice* v;

	if (sb_WaveDriver == 0) {
		return;
	}
	if (fade == 0) {
		for (i = 0; i < sb_VoiceCount; i++) {
			v = &((Voice*)sb_Voices)[i];
			if (v->sample != 0 && msx_GetSampleStatus(v->h) == 4) {
				sb_StopVoice(v, 0);
			}
		}
		return;
	}
	t = gm_GameTicks * 8 + gm_GameTicks * 4 + gm_GameTicks;
	g_678dec = fade;
	g_6b7e90 = 1;
	for (i = 0; i < sb_VoiceCount; i++) {
		v = &((Voice*)sb_Voices)[i];
		if (v->sample != 0 && msx_GetSampleStatus(v->h) == 4) {
			v->time = t;
		}
	}
}
