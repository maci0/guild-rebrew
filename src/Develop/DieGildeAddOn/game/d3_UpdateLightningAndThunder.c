


extern int d3_RainEffect;
extern int d3_SnowEffect;
extern unsigned short gm_GameTimeHour;
extern int g_7f4c06;
extern int g_7e4408[];
extern int g_7e43a4[];
extern int g_7e4468;
extern int g_7e446c;
extern volatile int gm_GameTicks;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern char* SonnenstrahlenObjekt;
extern int g_6a2c24;
extern int g_7747c0;
extern float g_699b0c;
extern float g_664e80;
extern char g_6a33a4[];

void __cdecl d3_RenderRainLines(int);
void __cdecl d3_RenderSnowLines(int);
unsigned short __cdecl gm_RandomMod(int);
int __cdecl sb_PlayVoice(int, char*, int, int, int, int, int);
#include "Develop/DieGildeAddOn/game/sonnenstrahlen.h"

void __cdecl d3_UpdateLightningAndThunder(void)
{
	if (d3_RainEffect != 0) {
		d3_RenderRainLines(d3_RainEffect);
	}
	if (d3_SnowEffect != 0) {
		d3_RenderSnowLines(d3_SnowEffect);
	}
	if (g_7e4408[(unsigned short) (*(int*)&gm_GameTimeHour)] != 0) {
		if (gm_RandomMod(300) == 0 || (g_7e4408[(unsigned short) (*(int*)&gm_GameTimeHour)] == 3 && gm_RandomMod(100) == 0)) {
			g_7e4468 = gm_GameTicks;
			g_7e446c = gm_RandomMod(8) + 8;
			sb_PlayVoice(g_7747c0, g_6a33a4, 1, 0x3f, (int) (g_664e80 * g_699b0c), 0, 0);
		}
	}
	if (d3_CurrentContextIndex == 0) {
		if ((unsigned short) (*(int*)&gm_GameTimeHour) >= 0xb && (unsigned short) (*(int*)&gm_GameTimeHour) <= 0x11 && g_7e43a4[(unsigned short) (*(int*)&gm_GameTimeHour)] != 0
		    && g_7e43a4[(unsigned short) (*(int*)&gm_GameTimeHour) + 1] == 0
		    && g_7f4c06 > 0x1e) {
			if (gm_RandomMod(0x80) > 0x60 && (*(int*)&SonnenstrahlenObjekt) == 0) {
				CreateSonnenstrahlen();
			}
			g_6a2c24 = (unsigned short) (*(int*)&gm_GameTimeHour);
		}
		if (g_6a2c24 != -1 && (unsigned short) (*(int*)&gm_GameTimeHour) > g_6a2c24 && g_7f4c06 > 0x1e) {
			if ((*(int*)&SonnenstrahlenObjekt) != 0) {
				StopSonnenstrahlen(SonnenstrahlenObjekt, 1);
			}
			g_6a2c24 = -1;
		}
	}
}
