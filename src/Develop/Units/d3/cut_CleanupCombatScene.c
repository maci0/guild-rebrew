extern char g_9b8f44[];
extern char g_1043378[];
extern char g_772ea0[];
extern char g_772ebc[];
extern char g_772ec0[];
extern int cut_BombSampleBank;
extern char g_772ec8[];
extern char g_772ecc[];
extern char g_772ed0[];
extern char g_772ed4[];
extern char g_772edc[];
extern char g_772ee4[];
extern char g_772eec[];
extern char g_772ef4[];
extern char g_772f00[];
extern char g_772f04[];
extern char g_772ed8[];
extern char g_772ee0[];
extern char g_772ee8[];
extern char g_772ef0[];
extern char g_772ef8[];
extern char g_9b4bc4[];
extern char g_6a2570[];
extern char g_6a2574[];
extern char str_empty[];
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int d3_CurrentFloor;
extern unsigned short gm_LocalPlayerSlot;
/* Release the client path/mode tables and reset the scene clock state. */

void __cdecl cut_FadeToBlack(void);
void __cdecl d3_DestroyObject(int);
void __cdecl sb_ReleaseSampleBank(int);
void __cdecl gv_SpawnIfPending(int);
char* __cdecl gm_LookupEntityRecordById(int);
float __cdecl gm_ApplyEntityHealthDelta(unsigned short, int);
void __cdecl ch_DestroyCharacter(int);
void __cdecl cut_CleanupCutscene(void);
void __cdecl msx_RestoreMusicVolume(void);
void __cdecl d2_SetMouseTooltip(char*);

/* ADDRESS: GOLDTL 0x004d2a60 */
/* ADDRESS: GOLDDE 0x004bfd50 */
void __cdecl cut_CleanupCombatScene(int dlg)
{
	int i;
	int v;
	char* p;
	int* q;

	cut_FadeToBlack();
	v = *(int*) &g_772ea0;
	if (v) {
		d3_DestroyObject(v);
		*(int*) &g_772ea0 = 0;
	}
	sb_ReleaseSampleBank(*(int*) &g_772ebc);
	sb_ReleaseSampleBank(*(int*) &g_772ec0);
	sb_ReleaseSampleBank(*(int*) &cut_BombSampleBank);
	sb_ReleaseSampleBank(*(int*) &g_772ec8);
	sb_ReleaseSampleBank(*(int*) &g_772ecc);
	sb_ReleaseSampleBank(*(int*) &g_772ed0);
	sb_ReleaseSampleBank(*(int*) &g_772ed4);
	sb_ReleaseSampleBank(*(int*) &g_772edc);
	sb_ReleaseSampleBank(*(int*) &g_772ee4);
	sb_ReleaseSampleBank(*(int*) &g_772eec);
	sb_ReleaseSampleBank(*(int*) &g_772ef4);
	if (*(int*) &g_772f00 != *(int*) &g_772f04) {
		sb_ReleaseSampleBank(*(int*) &g_772ed8);
		sb_ReleaseSampleBank(*(int*) &g_772ee0);
		sb_ReleaseSampleBank(*(int*) &g_772ee8);
		sb_ReleaseSampleBank(*(int*) &g_772ef0);
		sb_ReleaseSampleBank(*(int*) &g_772ef8);
	}
	for (i = 0; i < g_772f08; i++) {
		d3_DestroyObject(*(int*) (((int) &g_9b8f44 + 0xefc) + i * 4));
	}
	v = *(int*) ((int) &g_772f08 + 0x4);
	if (v) {
		gv_SpawnIfPending(v);
		*(int*) ((int) &g_772f08 + 0x4) = 0;
	}
	q = (int*) &g_9b4bc4;
	do {
		if (*(unsigned short*) ((char*) q - 0x184) != 0xffff && *q) {
			v = *(int*) (dlg + 0xc);
			if (v ==
			        *(int*) ((unsigned short) gm_LocalPlayerSlot *
			                     0x21c +
			                 (int) &gm_EntityIdField) ||
			    nt_ClientSocket == -1) {
				p = gm_LookupEntityRecordById(*(int*) ((char*) q - 0x180));
				if (p[2] != 11) {
					gm_ApplyEntityHealthDelta(*(unsigned short*) p,
					             *(int*) ((char*) q - 0x160) -
					                 *(int*) (p + 0x24));
				}
			}
			ch_DestroyCharacter(*q);
			*q = 0;
		}
		q = (int*) ((char*) q + 0x21c);
	} while ((int) q < (int) &g_9b8f44);
	v = d3_CurrentFloor;
	*(float*) &g_6a2570 = 1.0f;
	if (v) {
		i = d3_CurrentContextIndex;
		g_6b89c0 = 0;
		*(int*) ((int) &g_1043378 + i * 0x3dc) = 0;
	}
	cut_CleanupCutscene();
	msx_RestoreMusicVolume();
	*(char*) &g_6a2574 = 1;
	d2_SetMouseTooltip((char*) &str_empty);
}
