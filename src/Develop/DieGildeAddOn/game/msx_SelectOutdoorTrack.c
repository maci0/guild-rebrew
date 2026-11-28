extern char g_688128[];
extern char g_7f4c00[];
extern char g_772910[];
#include <string.h>
#include <stdio.h>

#include "Develop/Units/Msx/client_sound.h"

int __cdecl gm_GetSeason(char*);
int __cdecl msx_FindActiveGroup(void);
int __cdecl msx_FindGroupByKey(int);
extern char g_772d58[];
void* __cdecl msx_StartTrack(char*, int);
unsigned short __cdecl gm_RandomMod(int);

/* ADDRESS: GOLDTL 0x004c2430 */
/* ADDRESS: GOLDDE 0x004aff50 */
void __cdecl msx_SelectOutdoorTrack(void)
{
	char* dst;
	int season;
	int slot;
	int idx;
	int roll;

	season = gm_GetSeason((char*) &g_7f4c00);
	slot = msx_FindActiveGroup();
	if (slot >= 0) {
		idx = slot * 0x114;
		*(short*) (((int) &g_688128 + 0x100) + idx) = (short) (*(short*) (((int) &g_688128 + 0x100) + idx) - 0x1e);
		*(char*) (((int) &g_688128 + 0x102) + idx) = 0;
	}
	slot = msx_FindGroupByKey(0x2694);
	if (slot < 0) {
		return;
	}
	idx = slot * 0x114;
	dst = (char*) ((int) &g_688128 + idx);
	if (strlen(dst) != 0) {
		sprintf((char*) &g_772910, "Resuming Outdoor-Track %s !", dst);
		*(short*) (((int) &g_688128 + 0x100) + idx) = (short) (*(short*) (((int) &g_688128 + 0x100) + idx) + 0x1e);
		*(char*) (((int) &g_688128 + 0x102) + idx) = 1;
		tp_msx_CurrentTrack = g_772d20 = (Chan_14cc460*) msx_StartTrack(dst, 0);
		return;
	}
	do {
		roll = gm_RandomMod(0x75) % 4;
		switch (season) {
		case 0:
			if (gm_RandomMod(0xb) < 4) {
				strcpy(dst, "CD2\\KraeuterUndPhiolen.mp3");
			} else {
				if (roll == 0) {
					strcpy(dst, "cd1\\Burgfraeulein.mp3");
				} else if (roll == 1) {
					strcpy(dst, "cd1\\ImFruehling.mp3");
				} else {
					memcpy(dst, "CD3\\Crescendo.mp3", 18);
				}
			}
			sprintf((char*) &g_772910, "Outdoor-Track for GM_SPRING selected: %s.", dst);
			break;
		case 1:
			if (gm_RandomMod(0xb) < 3) {
				strcpy(dst, "CD3\\Heldenglanz.mp3");
			} else {
				if (roll == 0) {
					strcpy(dst, "cd1\\Burgfraeulein.mp3");
				} else if (roll == 1) {
					strcpy(dst, "cd1\\ZurSommerzeit.mp3");
				} else {
					strcpy(dst, "CD3\\MitFlinkemStich.mp3");
				}
			}
			sprintf((char*) &g_772910, "Outdoor-Track for GM_SUMMER selected: %s.", dst);
			break;
		case 2:
			if (gm_RandomMod(0xb) < 3) {
				strcpy(dst, "CD3\\DerStolzenTraum.mp3");
			} else {
				if (roll == 0) {
					strcpy(dst, "cd1\\AufDenStrassen.mp3");
				} else if (roll == 1) {
					strcpy(dst, "cd1\\ImHerbst.mp3");
				} else {
					strcpy(dst, "CD3\\BurgUndFeste.mp3");
				}
			}
			sprintf((char*) &g_772910, "Outdoor-Track for GM_AUTUMN selected: %s.", dst);
			break;
		case 3:
			if (gm_RandomMod(0xb) < 4) {
				strcpy(dst, "CD3\\SchmerzlichErinnerung.mp3");
			} else {
				if (roll == 0) {
					strcpy(dst, "cd1\\AufDenStrassen.mp3");
				} else if (roll == 1) {
					strcpy(dst, "cd1\\InkalterNovembernacht.mp3");
				} else {
					strcpy(dst, "cd1\\ImmerKalt.mp3");
				}
			}
			sprintf((char*) &g_772910, "Outdoor-Track for GM_WINTER selected: %s.", dst);
			break;
		default:
			break;
		}
		if (strlen(g_772d58) == 0) {
			break;
		}
	} while (strcmp(g_772d58, dst) == 0);
	*(short*) (((int) &g_688128 + 0x100) + idx) = (short) (*(short*) (((int) &g_688128 + 0x100) + idx) + 0x1e);
	g_772d58[0] = 0;
	*(char*) (((int) &g_688128 + 0x102) + idx) = 1;
	tp_msx_CurrentTrack = g_772d20 = (Chan_14cc460*) msx_StartTrack(dst, 0);
	return;
}
