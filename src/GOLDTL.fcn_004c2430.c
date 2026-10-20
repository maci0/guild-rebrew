#include <string.h>
#include <stdio.h>

#include "client_sound.h"

int __cdecl fcn_00500e20(char*);
int __cdecl fcn_004c27f0(void);
int __cdecl fcn_004c2820(int);
void* __cdecl fcn_0041fd70(char*, int);
unsigned short __cdecl gm_RandomMod(int);

/* ADDRESS: GOLDTL 0x004c2430 */
void __cdecl fcn_004c2430(void)
{
	char* dst;
	int season;
	int slot;
	int idx;
	int roll;

	season = fcn_00500e20((char*) 0x7f4c00);
	slot = fcn_004c27f0();
	if (slot >= 0) {
		idx = slot * 0x114;
		*(short*) (0x688228 + idx) = (short) (*(short*) (0x688228 + idx) - 0x1e);
		*(char*) (0x68822a + idx) = 0;
	}
	slot = fcn_004c2820(0x2694);
	if (slot < 0) {
		return;
	}
	idx = slot * 0x114;
	dst = (char*) (0x688128 + idx);
	if (strlen(dst) != 0) {
		sprintf((char*) 0x772910, "Resuming Outdoor-Track %s !", dst);
		*(short*) (0x688228 + idx) = (short) (*(short*) (0x688228 + idx) + 0x1e);
		*(char*) (0x68822a + idx) = 1;
		g_772d20 = (Chan_14cc460*) fcn_0041fd70(dst, 0);
		g_772d1c = g_772d20;
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
			sprintf((char*) 0x772910, "Outdoor-Track for GM_SPRING selected: %s.", dst);
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
			sprintf((char*) 0x772910, "Outdoor-Track for GM_SUMMER selected: %s.", dst);
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
			sprintf((char*) 0x772910, "Outdoor-Track for GM_AUTUMN selected: %s.", dst);
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
			sprintf((char*) 0x772910, "Outdoor-Track for GM_WINTER selected: %s.", dst);
			break;
		default:
			break;
		}
		if (strlen((char*) 0x772d58) == 0) {
			break;
		}
	} while (strcmp((char*) 0x772d58, dst) == 0);
	*(short*) (0x688228 + idx) = (short) (*(short*) (0x688228 + idx) + 0x1e);
	*(char*) 0x772d58 = 0;
	*(char*) (0x68822a + idx) = 1;
	g_772d1c = (Chan_14cc460*) fcn_0041fd70(dst, 0);
	g_772d20 = g_772d1c;
	return;
}
