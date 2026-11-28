#include "Develop/DieGildeAddOn/game/game_timestamp.h"








typedef struct {
	float v[24];
} Vec24;

/* SIZE 0x4 */
typedef struct {
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
} Col;

/* SIZE 0x2f4 */
typedef struct {
	char pad0[0x108];
	int f108[4];
	int f118[4];
	char pad128[0x2f4 - 0x128];
} SkyFrame;

/* SIZE 0x3dc */
typedef struct {
	char pad0[0x2c];
	int f2c;
	char pad30[0x3dc - 0x30];
} D3_CONTEXT_SLOT;

#include "Develop/client_types.h"

extern unsigned char gm_ActiveTownIndex;
extern char gm_TownTable[];
extern pos14_7f4c00 gm_GameTime;
extern int g_7e43a0;
extern int g_7e43a4;
extern int g_7e4530;
extern int g_7e4534;
extern int d3_RainEffect;
extern int d3_SnowEffect;
extern int d3_SkyLayers[6];
extern int g_7e4468;
extern int g_7e446c;
extern int g_7e4380;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern char g_7746fc;
extern Slot_1043340 g_1043340[64];
extern Tabs_7e43a8 gm_HourlyWeatherSlots;
extern float g_6a2640;
extern float g_6a2644;
extern float g_6a2648;
extern float g_6a268c;
extern float g_6a2690;
extern float g_6a2694;
extern float g_6a28f0;
extern float g_6a28f4;
extern float g_6a28f8;

void __cdecl gm_PackGameTime(int*, char*);
int __cdecl gm_QuerySeason(int*);
unsigned short __cdecl gm_RandomMod(int);
int __cdecl rand(void);
float __cdecl gm_RandomFloat01(void);
double __cdecl sin(double);
double __cdecl cos(double);
#pragma intrinsic(sin, cos)

int* __cdecl d3_CreateSky(float, float, float);
int __cdecl d3_CreateSkyLayer(int, int, int, Col, float, int, float, float);
void __cdecl d3_SetSkyLayerScrollSpeed(int, int, float);
void __cdecl d3_RemoveSkyLayer(int, int);
void __cdecl gm_InitWeatherWave(int, int, Vec24*, Vec24*);
void __cdecl d3_SelectSceneContext(int, int);
void __cdecl d3_ApplySceneLightingPreset(void);
void __cdecl d3_UpdateDaylightPhase(GAME_TIMESTAMP*);
int* __cdecl d3_CreateRain(int);
void __cdecl d3_DestroyRain(int);
int* __cdecl d3_CreateSnowEffect(int);
void __cdecl d3_DestroySnowEffect(int);
void __cdecl d3_SetSnowEffectOptions(int*, int, ...);
void __cdecl d3_SetRainEffectOptions(int*, int, ...);

/* ADDRESS: GOLDTL 0x0052a3a0 */
/* ADDRESS: GOLDDE 0x005135b0 */
void __cdecl gm_UpdateWeatherAndSky(GAME_TIMESTAMP* now, int flag)
{
	char buf[12];
	float step;
	float angle;
	int mode;
	int i;
	int maxv;
	int player;
	Col col;

	gm_PackGameTime((int*) now, buf);
	mode = gm_QuerySeason((int*) now);
	g_7e43a0 = ((int*) ((char*) gm_TownTable + 0x108))[gm_ActiveTownIndex * 189 + mode];
	g_7e43a4 = ((int*) ((char*) gm_TownTable + 0x118))[gm_ActiveTownIndex * 189 + mode];
	if (flag != 0) {
		if (mode == 3) {
			g_7e4530 = (gm_RandomMod(100) < g_7e43a0 / 2) + 1;
		} else {
			g_7e4530 = 0;
		}
		for (i = 0; i < 24; i++) {
			gm_HourlyWeatherSlots.a[i] = 0;
		}
		for (i = 0; i < 24; i++) {
			if (gm_RandomMod(100) < g_7e43a0) {
				gm_HourlyWeatherSlots.a[i] = gm_RandomMod(g_7e43a0 * 10);
			}
			if (gm_HourlyWeatherSlots.a[i] > 700) {
				gm_HourlyWeatherSlots.a[i] = (gm_HourlyWeatherSlots.a[i] & 1) + 999;
			} else if (gm_HourlyWeatherSlots.a[i] > 500) {
				gm_HourlyWeatherSlots.a[i] = (gm_HourlyWeatherSlots.a[i] & 1) + 499;
			} else if (gm_HourlyWeatherSlots.a[i] > 250) {
				gm_HourlyWeatherSlots.a[i] = (gm_HourlyWeatherSlots.a[i] & 1) + 149;
			} else {
				gm_HourlyWeatherSlots.a[i] = 0;
			}
			if (g_7e4530 == 0 && gm_HourlyWeatherSlots.a[i] >= 999) {
				gm_HourlyWeatherSlots.b[i] = gm_RandomMod(3);
			} else {
				gm_HourlyWeatherSlots.b[i] = 0;
			}
		}
		angle = gm_RandomFloat01() * 6.2831853;
		step = rand() > 0x3fff ? -0.175f : 0.175f;
		for (i = 0; i < 24; i++) {
			((Vec24*) &gm_HourlyWeatherSlots.c)->v[i] = sin(angle);
			((Vec24*) &gm_HourlyWeatherSlots.d)->v[i] = cos(angle);
			angle += gm_RandomFloat01() * step;
		}
	}
	gm_InitWeatherWave(mode, gm_GameTime.a, (Vec24*) &gm_HourlyWeatherSlots.c, (Vec24*) &gm_HourlyWeatherSlots.d);
	g_7e4468 = 0;
	g_7e446c = 0;
	g_7e4534 = -1;
	maxv = 0;
	for (i = 0; i < 24; i++) {
		if (maxv <= gm_HourlyWeatherSlots.a[i]) {
			maxv = gm_HourlyWeatherSlots.a[i];
		}
	}
	if (g_7e4530 != 0) {
		if (g_7e4530 == 1) {
			if (d3_RainEffect != 0) {
				d3_DestroyRain(d3_RainEffect);
				d3_RainEffect = 0;
			}
		} else if (d3_RainEffect == 0) {
			d3_RainEffect = (int) d3_CreateRain(maxv);
		}
		if (d3_SnowEffect == 0) {
			d3_SnowEffect = (int) d3_CreateSnowEffect(maxv);
		}
		d3_SetSnowEffectOptions((int*) d3_SnowEffect, 2, 0, 0, 3, 0xff);
		d3_SetSnowEffectOptions((int*) d3_SnowEffect, 1, 0, 0);
	} else {
		if (d3_SnowEffect != 0) {
			d3_DestroySnowEffect(d3_SnowEffect);
			d3_SnowEffect = 0;
		}
		if (d3_RainEffect == 0) {
			d3_RainEffect = (int) d3_CreateRain(maxv);
		}
		d3_SetRainEffectOptions((int*) d3_RainEffect, 1, 0, 0);
	}
	if (g_6b89c0 == 0) {
		g_6b89c0 = (int) d3_CreateSky(-0.95f, -0.2f, 600.0f);
	}
	for (i = 0; i < 6; i++) {
		if (d3_SkyLayers[i] != 0) {
			d3_RemoveSkyLayer(g_6b89c0, d3_SkyLayers[i]);
			d3_SkyLayers[i] = 0;
		}
	}
	*(int*) &col = 0xff;
	col.b = 0;
	d3_SkyLayers[0] = d3_CreateSkyLayer(g_6b89c0, 0, (int) "Sky_Schoen_01", col, g_6a2640, 0, g_6a2644, g_6a2648);
	d3_SetSkyLayerScrollSpeed(g_6b89c0, d3_SkyLayers[0], 0);
	*(int*) &col = 0;
	col.b = 0;
	d3_SkyLayers[1] = d3_CreateSkyLayer(g_6b89c0, 0, (int) "Sky_Schoen_02", col, g_6a268c, 0, g_6a2690, g_6a2694);
	d3_SetSkyLayerScrollSpeed(g_6b89c0, d3_SkyLayers[1], 0);
	*(int*) &col = 0;
	col.b = 0;
	d3_SkyLayers[2] = d3_CreateSkyLayer(g_6b89c0, 0, (int) "sky_dunkel_01", col, g_6a28f0, 0, g_6a28f4, g_6a28f8);
	d3_SetSkyLayerScrollSpeed(g_6b89c0, d3_SkyLayers[2], 0);
	player = d3_CurrentContextIndex;
	for (i = 0; i < 64; i++) {
		if (((D3_CONTEXT_SLOT*) g_1043340)[i].f2c != 0) {
			d3_SelectSceneContext(i, 1);
			d3_ApplySceneLightingPreset();
		}
	}
	d3_SelectSceneContext(player, 1);
	g_7e4380 = -100;
	g_7746fc = 0;
	d3_UpdateDaylightPhase(now);
}
#if defined(REBREW_SERVER) || defined(REBREW_GOLD)
unsigned char _dpad_7e43a8[400];
unsigned char _dpad_7e4540[364];
#else
/* Reference gaps only; the emitted objects inside the span keep their own rows. */
unsigned char _dpad_7e43ac[92];
unsigned char _dpad_7e440c[92];
unsigned char _dpad_7e4474[92];
unsigned char _dpad_7e44d4[92];
unsigned char _dpad_7e4558[340];
#endif
