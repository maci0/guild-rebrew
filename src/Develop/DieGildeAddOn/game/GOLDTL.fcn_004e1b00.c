#include <stdio.h>
#include <string.h>
#include "game_data.h"
extern int cut_EventLoopFlags;
extern int d2_SuppressOverlay;
extern int g_772f54;

char* __cdecl gm_LookupEntityRecordById(int);
int __cdecl cut_RandMod(int);
void __cdecl fcn_004e4730(char*);
void __cdecl d3_InitSkyLayer(char*);
void __cdecl msx_StartMusicIfAllowed(char*);
void __cdecl fcn_004e4c40(int);
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
	fcn_004e4730((char*) 0x68cfb0);
	d3_BlendSceneLightingPreset(0, 0, 1.0f, 1);
	d3_InterpolateSceneFog(0, 0, 0);
	if (mode == 1) {
		d3_InitSkyLayer((char*) (cut_RandMod(3) * 0x4c + 0x6a2818));
	} else if (mode == 2) {
		d3_InitSkyLayer((char*) (cut_RandMod(3) * 0x4c + 0x6a2730));
	} else {
		d3_InitSkyLayer((char*) (cut_RandMod(4) * 0x4c + 0x6a2600));
	}
	msx_StartMusicIfAllowed((char*) 0x68cb08);
	if (mode == 1) {
		fcn_004e4c40(500);
	}
	if (q != 0) {
		id = gm_SelectEntityHeadSet(*q);
	} else {
		id = gm_FindOrAllocHeadSet(gm_RandomMod(2) & 0xffff, (gm_RandomMod(0x5e) & 0xffff) + 1);
	}
	sprintf(buf, (char*) 0x68cad8, id + 4);

	r_dst = buf + strlen(buf);
	sprintf(r_dst, (char*) 0x68cad8, gm_SelectEntityHeadSet(*p) + 4);

	r_dst = buf + strlen(buf);
	if (r != 0) {
		id = gm_SelectEntityHeadSet(*r);
	} else {
		id = gm_FindOrAllocHeadSet(gm_RandomMod(2) & 0xffff, (gm_RandomMod(0x5e) & 0xffff) + 1);
	}
	sprintf(r_dst, (char*) 0x68cad8, id + 4);

	s_dst = buf + strlen(buf);
	if (s != 0) {
		id = gm_SelectEntityHeadSet(*s);
	} else {
		id = gm_FindOrAllocHeadSet(gm_RandomMod(2) & 0xffff, (gm_RandomMod(0x5e) & 0xffff) + 1);
	}
	sprintf(s_dst, (char*) 0x679060, id + 4);
	evt_StartGfxScript((char*) 0x68cf80, buf);
	cut_WaitForScript(evt_StartGfxScript((char*) 0x68cf54, (char*) 0x6b5c60));
	if (*(int*) (eventRecord + 0xc) == *(int*) (g_774970 * 0x21c + 0x7f4ca4)) {
		gm_ApplyEntityHealthDelta(*p, (int) -(*(float*) ((char*) p + 0x1c) + *(float*) 0x662a98));
	}
	switch (*(char*) (eventRecord + 0x7c)) {
	case 0:
		evt_StartGfxScript((char*) 0x68cf28, (char*) 0x6b5c60);
		break;
	case 1:
	case 2:
		evt_StartGfxScript((char*) 0x68cef8, (char*) 0x6b5c60);
		break;
	case 3:
		evt_StartGfxScript((char*) 0x68cec8, (char*) 0x6b5c60);
		break;
	case 4:
		evt_StartGfxScript((char*) 0x68ce98, (char*) 0x6b5c60);
		break;
	}
	cut_WaitSeconds(ranges[*(char*) (eventRecord + 0x7c)]);
	cut_FadeToBlack();
	cut_WaitForScript(evt_StartGfxScript((char*) 0x68ce6c, (char*) 0x6b5c60));
	if (mode != 0) {
		d3_DestroySceneRain();
	}
	d3_DestroySkyLayer();
	g_772f54 = 0;
	cut_CleanupCutscene();
	d2_SuppressOverlay = 0;
	msx_RestoreMusicIfAllowed();
}
