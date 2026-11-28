extern float d3_SampleAverageTerrainHeight(float *pos);
extern int gm_GetSeason(int *p);
extern int *sb_PlayVoice(char *bank, char *name, int loop, int pan, int vol,
    int a, int b);
extern void sb_SetVoiceVolume(int *voice, int vol);
extern void sb_StopVoice(int *voice, int flag);
extern void fcn_0064d41a();
extern int fcn_0064d3f8(void);
extern int ch_CountCharacters(int a, int b);
extern int ch_CountCharactersNear(int a, int b, char *buf, int d);
extern void d3_TransformPoint(int a, int b, char *buf);
extern void d3snd_SetSourceVolume(int a, int b);
extern int msx_SetTrackVolume(int handle, int value);
extern int msx_StartAmbientTrack(char *name, int value);
extern void msx_StopAmbientTrack(int handle);
#include "Develop/DieGildeAddOn/game/building_prototype.h"
extern char *d3_CurrentFloor;
extern unsigned char d3snd_AmbientEnabled;
extern volatile int gm_GameTicks;
extern int d3_CurrentContextIndex;
extern char *d3_ActiveCamera;
extern int g_772d4c;
extern int *g_772d48;
extern int *g_772d44;
extern int g_772d50;
extern int g_772d30;
extern unsigned char *d2_VisitedBuilding;
extern short *sv_SelectedBuilding;
extern int *gm_MarketEntity;
extern int *d3_RainEffect;
extern unsigned char *lpGebaeudePROT;
extern char g_772b10;

extern float g_662a18;


extern char s_689e18[];
extern char s_689e68[];
extern char s_689dfc[];
extern char s_689ddc[];
extern char s_689dc0[];
extern char s_689f48[];
extern char s_689ee8[];
extern char s_689fac[];
extern char s_68a0d0[];
extern char s_68a0c4[];
extern char s_68a09c[];
extern char s_689ff0[];
extern char s_68a03c[];
extern char s_68a070[];
extern char s_689ee0[];
extern char s_689ed4[];
extern char s_689ec8[];
extern char s_689ebc[];
extern char s_68a124[];

#define flt_64 (64.0f)
#define flt_time_scale (0.0005f)

/* ADDRESS: GOLDTL 0x004c16c0 */
int __cdecl gm_UpdateAmbientAudio(void)
{
	char buf[16];
	int tickOrOffset;
	int metric;
	int offset;
	int i;
	float f;
	float fv;
	unsigned char c;
	unsigned char *p;

	if (d3_CurrentFloor != 0 && d3snd_AmbientEnabled != 0) {
		metric = 0;
		tickOrOffset = (gm_GameTicks + gm_GameTicks * 2) * 4
		    + gm_GameTicks;
		if (g_772d4c != gm_GetSeason((int *) 0x7f4c00)) {
			g_772d4c = gm_GetSeason((int *) 0x7f4c00);
			if (g_772d48 != 0) {
				sb_StopVoice(g_772d48, 0);
				*(int *) ((char *) g_772d48 + 0x18) = 0;
				g_772d48 = 0;
			}
			if (g_772d44 != 0) {
				sb_StopVoice(g_772d44, 0);
				*(int *) ((char *) g_772d44 + 0x18) = 0;
				g_772d44 = 0;
			}
		}
		f = (2000.0f - *(float *) (d3_ActiveCamera + 0x50)
		    - d3_SampleAverageTerrainHeight((float *) (d3_ActiveCamera + 0x4c))) * flt_time_scale;
		if (d3_RainEffect != 0) {
			metric = *d3_RainEffect;
		}
		offset = g_772d4c * 100;
		if ((unsigned) (tickOrOffset - *(int *) (offset + 0x681830)) >
		    (unsigned) (fcn_0064d3f8() % 2000 + *(int *) (offset + 0x68182c))) {
			if (metric < 0x15e) {
				*(int *) (offset + 0x681830) = tickOrOffset;
				offset = g_772d4c * 100;
				if (1.0f < (float) fcn_0064d3f8() * 3.0518509447574615e-05f
				    + *(float *) (offset + 0x681820)) {
					sb_PlayVoice(0, s_68a124,
					    fcn_0064d3f8() % *(int *) (g_772d4c * 100 + 0x681828) + 1,
					    0x3f,
					    (int) ((float) (*(float *) (offset + 0x681824)) * 127.0f),
					    0, 0);
				}
				if (fcn_0064d3f8() % 10 > 6) {
					sb_PlayVoice(0, s_68a124,
					    fcn_0064d3f8() % *(int *) (g_772d4c * 100 + 0x681828) + 1,
					    0x3f,
					    (int) (*(float *) (g_772d4c * 100 + 0x681824) * 127.0f),
					    0, 0);
				}
			}
		}
		offset = g_772d4c * 100;
		if ((unsigned) (tickOrOffset - *(int *) (offset + 0x681844)) <=
		    (unsigned) (fcn_0064d3f8() % 2000 + *(int *) (offset + 0x681840)) || metric >= 100) {
			if (metric > 0x64 || g_772d4c == 3) {
				if (g_772d44 != 0) {
					fcn_0064d41a(&g_772b10, s_689f48, g_772d44);
					sb_StopVoice(g_772d44, 0);
					g_772d44 = 0;
					*(int *) ((char *) g_772d44 + 0x18) = 0; /* stores through the just-cleared pointer, as in the original */
				}
				if (g_772d48 != 0) {
					fcn_0064d41a(&g_772b10, s_689ee8, g_772d48);
					sb_StopVoice(g_772d48, 0);
					*(int *) ((char *) g_772d48 + 0x18) = 0;
					g_772d48 = 0;
				}
			}
			else {
				fcn_0064d41a(&g_772b10, s_689fac, g_772d48, g_772d44);
				if (g_772d44 != 0) {
					sb_SetVoiceVolume(g_772d44,
					    (int) (f * *(float *) (g_772d4c * 100 + 0x681838)
						* 127.0f) >> 1);
				}
				if (g_772d48 != 0) {
					sb_SetVoiceVolume(g_772d48,
					    (int) (f * *(float *) (g_772d4c * 100 + 0x681838)
						* 127.0f) >> 1);
				}
			}
		}
		else {
			*(int *) (offset + 0x681844) = tickOrOffset;
			if (1.0f < (float) fcn_0064d3f8() * 3.0518509447574615e-05f
			    + *(float *) (g_772d4c * 100 + 0x681834)) {
				if (g_772d48 != 0) {
					i = *(int *) ((char *) g_772d48 + 0xc);
					if (i > 2) {
						goto join;
					}
				}
				else {
					i = 0;
				}
				fcn_0064d41a(&g_772b10, s_68a0d0, g_772d48, i);
				g_772d48 = sb_PlayVoice(0, s_68a0c4,
				    fcn_0064d3f8() % *(int *) (g_772d4c * 100 + 0x68183c) + 2,
				    0x3f,
				    (int) (f * *(float *) (g_772d4c * 100 + 0x681838)
					* 127.0f),
				    0, 0);
				fcn_0064d41a(&g_772b10, s_68a09c, g_772d48);
			}
join:
			if (g_772d4c == 1) {
				if (g_772d44 == 0) {
					g_772d44 = sb_PlayVoice(0, s_68a0c4, 0, 0x3f,
					    (int) (*(float *) (g_772d4c * 100 + 0x681838) * f
						* 127.0f) >> 1, 0, 0);
					fcn_0064d41a(&g_772b10, s_68a070, g_772d44);
				}
				else {
					sb_SetVoiceVolume(g_772d44,
					    (int) (*(float *) (g_772d4c * 100 + 0x681838) * f
						* 127.0f) >> 1);
					fcn_0064d41a(&g_772b10, s_68a03c, g_772d44);
				}
			}
			else if (g_772d44 != 0) {
				fcn_0064d41a(&g_772b10, s_689ff0, g_772d44);
				sb_StopVoice(g_772d44, 0);
				g_772d44 = 0;
				*(int *) ((char *) g_772d44 + 0x18) = 0; /* stores through the just-cleared pointer, as in the original */
			}
		}
		offset = g_772d4c * 100;
		if ((unsigned) (fcn_0064d3f8() % 2000 + *(int *) (offset + 0x68187c)) <
		    (unsigned) (tickOrOffset - *(int *) (offset + 0x681880))) {
			*(int *) (offset + 0x681880) = tickOrOffset;
			offset = g_772d4c * 100;
			if (1.0f < (float) fcn_0064d3f8() * 3.0518509447574615e-05f
			    + *(float *) (offset + 0x681820)) {
				sb_PlayVoice(0, s_689ee0, 1, 0x3f,
				    (int) (f * *(float *) (offset + 0x681874) * 127.0f),
				    0, 0);
			}
		}
		offset = g_772d4c * 100;
		if ((unsigned) (fcn_0064d3f8() % 2000 + *(int *) (offset + 0x681868)) <
		    (unsigned) (tickOrOffset - *(int *) (offset + 0x68186c))) {
			*(int *) (offset + 0x68186c) = tickOrOffset;
			if (1.0f < (float) fcn_0064d3f8() * 3.0518509447574615e-05f
			    + *(float *) (g_772d4c * 100 + 0x68185c)) {
				p = s_689ed4;
				if (fcn_0064d3f8() % 10 >= 5) {
					p = s_689ec8;
				}
				sb_PlayVoice(0, p, 1, 0x3f,
				    (int) (f * *(float *) (g_772d4c * 100 + 0x681860)
					* 127.0f), 0, 0);
			}
		}
		offset = g_772d4c * 100;
		if ((unsigned) (fcn_0064d3f8() % 2000 + *(int *) (offset + 0x681854)) <
		    (unsigned) (tickOrOffset - *(int *) (offset + 0x681858))) {
			*(int *) (offset + 0x681858) = tickOrOffset;
			offset = g_772d4c * 100;
			if (1.0f < (float) fcn_0064d3f8() * 3.0518509447574615e-05f
			    + *(float *) (offset + 0x681848)) {
				sb_PlayVoice(0, s_689ebc,
				    fcn_0064d3f8() % *(int *) (g_772d4c * 100 + 0x681850) + 1,
				    0x3f,
				    (int) (f * *(float *) (offset + 0x68184c)
					* 127.0f), 0, 0);
			}
		}
		if (g_772d30 != 0 && gm_MarketEntity != 0) {
			i = *(int *) ((char *) gm_MarketEntity + 0x61);
			d3_TransformPoint(i, i + 0x4c, buf);
			i = ch_CountCharactersNear(0, 0, buf, 0x44610000) * 0x14;
			if (i >= 0x7f) {
				i = 0x7f;
			}
			d3snd_SetSourceVolume(g_772d30, i);
		}
	}
	else {
		metric = (gm_GameTicks + gm_GameTicks * 2) * 4
		    + gm_GameTicks;
		if (g_772d4c != gm_GetSeason((int *) 0x7f4c00)) {
			g_772d4c = gm_GetSeason((int *) 0x7f4c00);
		}
		if (g_772d44 != 0) {
			fcn_0064d41a(&g_772b10, s_689e68, g_772d44);
			sb_StopVoice(g_772d44, 0);
			*(int *) ((char *) g_772d44 + 0x18) = 0;
			g_772d44 = 0;
		}
		if (g_772d48 != 0) {
			fcn_0064d41a(&g_772b10, s_689e18, g_772d48);
			sb_StopVoice(g_772d48, 0);
			*(int *) ((char *) g_772d48 + 0x18) = 0;
			g_772d48 = 0;
		}
		tickOrOffset = g_772d4c * 100;
		*(int *) (tickOrOffset + 0x681830) = metric;
		*(int *) (tickOrOffset + 0x681844) = metric;
		*(int *) (tickOrOffset + 0x68186c) = metric;
		*(int *) (tickOrOffset + 0x681858) = metric;
		*(int *) (tickOrOffset + 0x681880) = metric;
	}
	if (d2_VisitedBuilding != 0 && d3snd_AmbientEnabled != 0) {
		c = ((BUILDING_PROTOTYPE*)lpGebaeudePROT)[(unsigned) *d2_VisitedBuilding].category;
		if (c == 0x16 && sv_SelectedBuilding != 0 && *sv_SelectedBuilding == 0x120) {
			if (g_772d50 == 0) {
				i = msx_StartAmbientTrack(s_689dfc, 5);
				g_772d50 = i;
				return i;
			}
			i = ch_CountCharacters(d3_CurrentContextIndex, 0) * 9;
			fv = flt_64 < (float) i ? flt_64 : (float) i;
			return msx_SetTrackVolume(g_772d50, (int) fv);
		}
		if (c != 0x12 && c != 0x14 && c != 8 && c != 0x15 && c != 0x0e) {
			if (c != 7 || sv_SelectedBuilding == 0 || *sv_SelectedBuilding != 0xf7) {
				goto label;
			}
			i = ch_CountCharacters(d3_CurrentContextIndex, 0) * 6;
			fv = flt_64 < (float) i ? flt_64 : (float) i;
			if (g_772d50 == 0) {
				i = msx_StartAmbientTrack(s_689ddc, 5);
				g_772d50 = i;
				return i;
			}
			return msx_SetTrackVolume(g_772d50, (int) fv);
		}
		i = ch_CountCharacters(d3_CurrentContextIndex, 0) * 6;
		fv = flt_64 < (float) i ? flt_64 : (float) i;
		if (g_772d50 == 0) {
			if (*(int *) ((char *) d2_VisitedBuilding + 0x95) == -1) {
				return 0;
			}
			i = msx_StartAmbientTrack(s_689dc0, (int) fv);
			g_772d50 = i;
			return i;
		}
		if (*(int *) ((char *) d2_VisitedBuilding + 0x95) == -1) {
			msx_StopAmbientTrack(g_772d50);
			g_772d50 = 0;
			return 0;
		}
		return msx_SetTrackVolume(g_772d50, (int) fv);
	}
label:
	if (g_772d50 == 0) {
		return 0;
	}
	msx_StopAmbientTrack(g_772d50);
	g_772d50 = 0;
	return 0;
}
