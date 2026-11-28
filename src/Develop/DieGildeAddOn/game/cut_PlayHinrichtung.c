#include <stdio.h>
#include <string.h>
#include "game_data.h"
extern int cut_EventLoopFlags;
extern int d2_SuppressOverlay;
extern int cut_StartTick;

char* __cdecl gm_LookupEntityRecordById(int);
int __cdecl cut_RandMod(int);
void __cdecl cut_StartSceneCutscene(char*);
void __cdecl d3_InitSkyLayer(char*);
void __cdecl msx_StartMusicIfAllowed(char*);
void __cdecl d3_CreateSceneRain(int);
int __cdecl gm_SelectEntityHeadSet(int);
int __cdecl gm_FindOrAllocHeadSet(int, int);
int __cdecl evt_StartGfxScript(char*, char*);
void __cdecl cut_WaitForScript(int);
int __cdecl gm_RandomMod(unsigned short);
float __cdecl gm_ApplyEntityHealthDelta(unsigned short, int);
void __cdecl cut_WaitSeconds(int);
void __cdecl cut_FadeToBlack(void);
void __cdecl d3_DestroySceneRain(void);
void __cdecl d3_DestroySkyLayer(void);
void __cdecl cut_CleanupCutscene(void);
void __cdecl msx_RestoreMusicIfAllowed(void);
int __cdecl d3_BlendSceneLightingPreset(int, float, float, int);
void __cdecl d3_InterpolateSceneFog(int, int, float);

/* ADDRESS: GOLDTL 0x004e1b00 */
/* ADDRESS: GOLDDE 0x004ce510 */
void __cdecl cut_PlayHinrichtung(int eventRecord)
{
	int mode;
	unsigned short* p;
	int ranges[5];
	char buf[256];
	unsigned short* q;
	unsigned short* r;
	unsigned short* s;
	char* scene;
	int id;
	char* s_dst;
	char* r_dst;


	mode = cut_RandMod(3);
	ranges[0] = 14000;
	ranges[1] = 12000;
	ranges[2] = 12000;
	ranges[3] = 15000;
	ranges[4] = 10000;
	p = (unsigned short*) gm_LookupEntityRecordById(*(int*) (eventRecord + 0x34));
	if (p == 0) {
		return;
	}
	q = (unsigned short*) gm_LookupEntityRecordById(*(int*) (eventRecord + 0x38));
	r = (unsigned short*) gm_LookupEntityRecordById(*(int*) (eventRecord + 0x3c));
	s = (unsigned short*) gm_LookupEntityRecordById(*(int*) (eventRecord + 0x40));
	cut_EventLoopFlags = 0x702c6;
	d2_SuppressOverlay = 1;
	cut_StartSceneCutscene((char*) ((int) &str_fmt_s + 0x13f50));
	d3_BlendSceneLightingPreset(0, 0, 1.0f, 1);
	d3_InterpolateSceneFog(0, 0, 0);
	if (mode == 1) {
		d3_InitSkyLayer((char*) (cut_RandMod(3) * 0x4c + ((int) &str_fmt_s + 0x297b8)));
	} else if (mode == 2) {
		d3_InitSkyLayer((char*) (cut_RandMod(3) * 0x4c + ((int) &str_fmt_s + 0x296d0)));
	} else {
		d3_InitSkyLayer((char*) (cut_RandMod(4) * 0x4c + ((int) &str_fmt_s + 0x295a0)));
	}
	msx_StartMusicIfAllowed((char*) ((int) &str_fmt_s + 0x13aa8));
	if (mode == 1) {
		d3_CreateSceneRain(500);
	}
	if (q != 0) {
		id = gm_SelectEntityHeadSet(*q);
	} else {
		id = gm_FindOrAllocHeadSet(gm_RandomMod(2) & 0xffff, (gm_RandomMod(0x5e) & 0xffff) + 1);
	}
	sprintf(buf, (char*) ((int) &str_fmt_s + 0x13a78), id + 4);

	r_dst = buf + strlen(buf);
	sprintf(r_dst, (char*) ((int) &str_fmt_s + 0x13a78), gm_SelectEntityHeadSet(*p) + 4);

	r_dst = buf + strlen(buf);
	if (r != 0) {
		id = gm_SelectEntityHeadSet(*r);
	} else {
		id = gm_FindOrAllocHeadSet(gm_RandomMod(2) & 0xffff, (gm_RandomMod(0x5e) & 0xffff) + 1);
	}
	sprintf(r_dst, (char*) ((int) &str_fmt_s + 0x13a78), id + 4);

	s_dst = buf + strlen(buf);
	if (s != 0) {
		id = gm_SelectEntityHeadSet(*s);
	} else {
		id = gm_FindOrAllocHeadSet(gm_RandomMod(2) & 0xffff, (gm_RandomMod(0x5e) & 0xffff) + 1);
	}
	sprintf(s_dst, (char*) &str_fmt_s, id + 4);
	evt_StartGfxScript((char*) ((int) &str_fmt_s + 0x13f20), buf);
	cut_WaitForScript(evt_StartGfxScript((char*) ((int) &str_fmt_s + 0x13ef4), (char*) ((int) &str_fmt_s + 0x3cc00)));
	if (*(int*) (eventRecord + 0xc) == *(int*) (gm_LocalPlayerSlot * 0x21c + (int) &gm_EntityIdField)) {
		gm_ApplyEntityHealthDelta(*p, (int) -(*(float*) ((char*) p + 0x1c) + 5.0f));
	}
	switch (*(char*) (eventRecord + 0x7c)) {
	case 0:
		evt_StartGfxScript((char*) ((int) &str_fmt_s + 0x13ec8), (char*) ((int) &str_fmt_s + 0x3cc00));
		break;
	case 1:
	case 2:
		evt_StartGfxScript((char*) ((int) &str_fmt_s + 0x13e98), (char*) ((int) &str_fmt_s + 0x3cc00));
		break;
	case 3:
		evt_StartGfxScript((char*) ((int) &str_fmt_s + 0x13e68), (char*) ((int) &str_fmt_s + 0x3cc00));
		break;
	case 4:
		evt_StartGfxScript((char*) ((int) &str_fmt_s + 0x13e38), (char*) ((int) &str_fmt_s + 0x3cc00));
		break;
	}
	cut_WaitSeconds(ranges[*(char*) (eventRecord + 0x7c)]);
	cut_FadeToBlack();
	cut_WaitForScript(evt_StartGfxScript((char*) ((int) &str_fmt_s + 0x13e0c), (char*) ((int) &str_fmt_s + 0x3cc00)));
	if (mode != 0) {
		d3_DestroySceneRain();
	}
	d3_DestroySkyLayer();
	cut_StartTick = 0;
	cut_CleanupCutscene();
	d2_SuppressOverlay = 0;
	msx_RestoreMusicIfAllowed();
}
