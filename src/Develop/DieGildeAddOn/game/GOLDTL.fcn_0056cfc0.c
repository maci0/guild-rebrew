#include "client_types.h"
#include "Develop/DieGildeAddOn/game/game_player.h"
extern volatile int g_6b7fb8;
extern int d3_CurrentContextIndex;
extern int g_7e4538;
extern int gm_GameTime;
extern int g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;
extern char g_7f4ca4[];
extern char g_6b5c60[];
extern char g_68149c[];
extern char g_6a2edc[];
extern char g_6a2f08[];
extern char g_6a6b50[];
extern char g_6a6ad0[];
extern char g_6a6ae0[];
extern char g_6a6af4[];
extern char g_6a6afc[];
extern char g_6a6b0c[];
extern char g_6a6b28[];
extern char g_6a6b38[];
extern char g_6a6b48[];

int __cdecl cm_GetCommandStatus(int);
char *__cdecl gm_StartFilteredEntitySearch(int, ...);
int __cdecl fcn_0050cad0(int *, int *);
void __cdecl gm_AdjustGebaeudeCondition(char *, int);
int __cdecl d3snd_QueueSound(int, int, char *, int, int);
void __cdecl gm_AddTime(char *, int, int, int);
char *__cdecl gm_LookupEntityRecordById(int);
char *__cdecl fcn_00445600(char *, int, int, char *);
void __cdecl d3_TransformPoint(char *, char *, float *);
int __cdecl CompareVector3WithinTolerance(float *, float *, float);
int __cdecl ch_StartMovement(int, int, int, char *, int, char *);
int __cdecl fcn_004c5620(int, char *);
void __cdecl cm_SendCancelCharacterActions(int);
int __cdecl sprintf(char *, char *, ...);
int __cdecl evt_FindScriptByName(char *);
int __cdecl evt_RequestScriptExit(char *);
void __cdecl fcn_00418f90(int);
void __cdecl he_FreeAction(char *);
void __cdecl d3_SelectSceneContext(int, int);
char *__cdecl sb_PrepareVoice(int, char *);
int __cdecl d3snd_AttachSoundSource(int, int, int, float);
void __cdecl d3snd_PlaySource(int, int, int, int);
void __cdecl d3snd_PlayObjectSound(int, int, int, float);
void __cdecl io_FormatTextBuffer(char *, int, ...);
int __cdecl he_MessageBoxQuickjump(int, int, char *, unsigned char, int, int, int, char *, char *);
int __cdecl gm_RandomMod(unsigned short);
char *__cdecl evt_LoadGfxScript(char *);
int __cdecl fcn_00428340(int, int, int, int, int);
char *__cdecl gm_FindNearestBuildingByKind(char *, int);
void __cdecl cm_RequestChangePlayerHe(int, int, int);
void __cdecl cm_RequestPlayAnimation(int, char *, int);

/* ADDRESS: GOLDTL 0x0056cfc0 */
void __cdecl he_RunHausbrand(char *a0)
{
	char *e;
	char *r;
	char *m;
	char *h;
	int *p;
	int *q;
	int i;
	int n;
	int d;
	float f;

	if ((*(unsigned char *)(a0 + 0x78) & 2) &&
	    (n = *(int *)(a0 + 0x84)) != -1) {
		if (!cm_GetCommandStatus(n))
			return;
		*(int *)(a0 + 0x84) = -1;
	}
	switch (*(int *)(a0 + 0x70)) {
	case 0:
		e = gm_StartFilteredEntitySearch(1, 1, *(int *)(a0 + 0xac));
		if (e != 0) {
			if (*(unsigned char *)(e + 0x5a) & 1) {
				*(int *)(a0 + 0x70) = -1;
				return;
			}
			if (*(unsigned char *)(a0 + 0xb4) >= 3)
				goto inc_step;
			{
				char names[3][64] = {"dummy_FAHNE", "dummy_RAUCH_0", "dummy_BRAND"};
				float pos[3] = {-243.0f, -90.0f, 190.0f};
				char text[0x400];
				int v10 = d3_CurrentContextIndex;

				if (*(int *)(e + 0x61) != 0) {
					d3_SelectSceneContext(0, 1);
					if (*(char *)(a0 + 0xb4) == 1) {
						r = sb_PrepareVoice(0, g_6a6b48);
						if (r != 0 &&
						    (r = (char *)d3snd_AttachSoundSource((int)r, *(int *)(e + 0x61), 0x6b, 2200.0f)) != 0)
							d3snd_PlaySource((int)r, 0, 0, 0);
					} else if (*(char *)(a0 + 0xb4) == 0) {
						r = sb_PrepareVoice(0, g_6a6b38);
						if (r != 0)
							d3snd_PlayObjectSound((int)r, *(int *)(e + 0x61), 0x6b, 2200.0f);
						if (*(unsigned short *)(e + 0x27) == g_774970) {
							d3snd_QueueSound(-8, 0, g_6a6b28, 0, 100);
							if (*(char *)(a0 + 0x104)) {
								io_FormatTextBuffer(text, 0x42d6, e);
								he_MessageBoxQuickjump(
									*(int *)(g_7f4ca4 + (unsigned short)g_774970 * 0x21c),
									-1, text, 0, 0x5ed, *(int *)(e + 1), -1, 0,
									g_6b5c60);
							}
						}
					}
					r = fcn_00445600((char *)*(int *)(e + 0x61), 0x100, 0,
							 &names[(unsigned char)*(unsigned char *)(a0 + 0xb4)][0]);
					if (r != 0) {
						d3_TransformPoint(r, r + 0x4c, pos);
					} else {
						r = fcn_00445600((char *)*(int *)(e + 0x61), 0x100, 0,
								 g_6a2edc);
					}
					if (r != 0) {
						d3_TransformPoint(r, r + 0x4c, pos);
						pos[0] = (float)(gm_RandomMod(0x40) & 0xffff) + pos[0] - 32.0f;
						pos[2] = (float)(gm_RandomMod(0x40) & 0xffff) + pos[2] - 32.0f;
						pos[1] = pos[1] - 20.0;
						m = evt_LoadGfxScript(g_6a6b0c);
						if (m != 0) {
							sprintf(m, g_6a6afc, *(int *)(a0 + 4),
								*(unsigned char *)(a0 + 0xb4));
							fcn_00428340((int)m, 3, (int)pos[0], (int)pos[1],
								     (int)pos[2]);
							*(int *)(m + 0x104) = 0;
						}
					}
				} else if (*(unsigned char *)(a0 + 0x78) & 2) {
					*(int *)(a0 + 0x84) = fcn_004c5620(-1, (char *)a0);
					return;
				}
				*(pos14_7f4c00*) (a0 + 0x52) = *(pos14_7f4c00*) &gm_GameTime;



				*(pos14_7f4c00*) (a0 + 0x60) = *(pos14_7f4c00*) &gm_GameTime;



				gm_AddTime(a0 + 0x52, 0, 4, 0);
				d3_SelectSceneContext(v10, 1);
			}
		} else {
inc_step:
			(*(int *)(a0 + 0x70))++;
		}
		if (e == 0) {
			*(pos14_7f4c00*) (a0 + 0x52) = *(pos14_7f4c00*) &gm_GameTime;



		}
		if ((*(unsigned char *)(a0 + 0x78) & 2) &&
		    *(unsigned char *)(a0 + 0xb4) == 1) {
			i = 0;
			n = (int)gm_FindNearestBuildingByKind(e, 3);
			if (n != 0) {
				h = g_7f4ca4 + 0x180;
				q = (int *)(a0 + 0xb8);
				do {
					if (*(char *)(h - 0x17c) != 0 &&
					    *(int *)h != 0 &&
					    *(int *)(*(int *)h + 0x2c) == *(int *)(e + 1) &&
					    (*(char *)(h - 4) == 0 || *(char *)(h - 4) == 4) &&
					    i < 0x10) {
						m = (char *)*(int *)(h - 0x180);
						*q = (int)m;
						cm_RequestChangePlayerHe((int)m, 0, 0);
						cm_SendCancelCharacterActions(*q);
						ch_StartMovement(*q, *(int *)(n + 1), -1, 0, 1, g_6a6af4);
						cm_RequestPlayAnimation(*q, g_6a6ae0,
							     (gm_RandomMod(2) & 0xffff) + 1);
						i++;
						q++;
					}
					h += 0x21c;
				} while ((int)h < 0x85a224);
			}
		}
		if (*(unsigned char *)(a0 + 0xb4) >= 3)
			break;
		*(unsigned char *)(a0 + 0xb4) = *(unsigned char *)(a0 + 0xb4) + 1;
		return;
	case 1:
		if (!(*(unsigned char *)(a0 + 0x78) & 2))
			return;
		e = gm_StartFilteredEntitySearch(1, 1, *(int *)(a0 + 0xac));
		if (*(int *)(a0 + 0xb0) > 0) {
			if (e != 0) {
				float pos[3];
				float tmp;
				double dtmp;

				f = 1.0f;
				p = (int *)(a0 + 0x60);
				tmp = (float)fcn_0050cad0(p, (int *)0x7f4c00) * (1.0f / 6.0f);
				n = (int)(tmp + tmp);
				if (g_7e4538 != 0) {
					dtmp = *(int *)g_7e4538 * 0.002;
					f = 1.0 + dtmp * 0.7;
				}
				*(int *)(a0 + 0xb0) =
					(int)((float)*(int *)(a0 + 0xb0) - n * f);
				gm_AdjustGebaeudeCondition(e, -n);
				if (*(unsigned short *)(e + 0x27) == g_774970 &&
				    *(unsigned int *)(a0 + 0xfc) + 0x20d < (unsigned int)g_6b7fb8) {
					d = *(char *)(e + 0x5c) - n;
					if (d <= 0) {
						d3snd_QueueSound(-8, 0, g_6a6ad0, 2, 100);
						*(int *)(a0 + 0xfc) = g_6b7fb8;
					} else if (d <= 0xa) {
						d3snd_QueueSound(-8, 0, g_6a6ad0, 1, 100);
						*(int *)(a0 + 0xfc) = g_6b7fb8;
					} else if (d <= 0x19) {
						d3snd_QueueSound(-8, 0, g_6a6ad0, 0, 100);
						*(int *)(a0 + 0xfc) = g_6b7fb8;
					}
				}
				*(pos14_7f4c00*) (a0 + 0x52) = *(pos14_7f4c00*) &gm_GameTime;



				*(pos14_7f4c00*) (a0 + 0x60) = *(pos14_7f4c00*) &gm_GameTime;



				e = 0;
				gm_AddTime(a0 + 0x52, 0, 4, 0);
				if (*(unsigned char *)(a0 + 0xb4) < 3)
					*(int *)(a0 + 0x70) = 0;
				i = 0;
				p = (int *)(a0 + 0xb8);
				n = 0x10;
				do {
					if (*p != -1) {
						if (e == 0) {
							e = gm_StartFilteredEntitySearch(1, 1,
										 *(int *)(a0 + 0xac));
							i = (int)gm_FindNearestBuildingByKind(e, 3);
						}
						r = gm_LookupEntityRecordById(*p);
						if (r != 0 &&
						    (m = *(char **)(r + 0x184)) != 0 &&
						    *(int *)(m + 0x2c) == -1 &&
						    *(int *)(m + 0x128) == 0 &&
						    (m = fcn_00445600((char *)*(int *)(e + 0x61), 0x100, 0,
								      g_68149c)) != 0) {
							d3_TransformPoint(m, m + 0x4c, pos);
							if (!(CompareVector3WithinTolerance(
								    (float *)(*(int *)(*(int *)(r + 0x184) + 0x34) + 0x4c),
								    pos, 80.0f) != 0)) {
								ch_StartMovement(*p, *(int *)(e + 1), -1, 0, 1,
									     g_6a6af4);
							} else {
								if (i != 0)
									ch_StartMovement(*p, *(int *)(i + 1), -1, 0, 1,
										     g_6a6af4);
							}
						}
					}
					p++;
				} while (--n);
			}
			if (*(int *)(a0 + 0xb0) > 0 && e != 0)
				return;
		}
		*(int *)(a0 + 0x84) = fcn_004c5620(-1, (char *)a0);
		return;
	case 0xfffffffe:
	case 0xffffffff: {
		char buf[0x40];

		e = gm_StartFilteredEntitySearch(1, 1, *(int *)(a0 + 0xac));
		if ((*(unsigned char *)(a0 + 0x78) & 2) && e != 0) {
			p = (int *)(a0 + 0xb8);
			i = 0x10;
			do {
				if (*p != -1) {
					cm_SendCancelCharacterActions(*p);
					ch_StartMovement(*p, *(int *)(e + 1), -1, 0, 0, g_6a6af4);
				}
				p++;
			} while (--i);
		}
		for (i = 0; i < 3; i++) {
			sprintf(buf, g_6a6afc, *(int *)(a0 + 4), i);
			n = evt_FindScriptByName(buf);
			if (n != 0)
				evt_RequestScriptExit((char *)n);
		}
		if (e != 0 && *(int *)(e + 0x61) != 0 &&
		    (n = *(int *)(*(int *)(e + 0x61) + 0x210)) != 0)
			fcn_00418f90(n);
		he_FreeAction(a0);
		break;
	}
	default:
		break;
	}
}
