#include <stdio.h>
#include <string.h>
#include "Develop/DieGildeAddOn/game/game_data.h"

unsigned short* __cdecl gm_NextEntityQueryMatch(void);
void* __cdecl fcn_00502cd0(int, int, ...);
char __cdecl d3_GetObjectScreenRect(void*, int*);
void __cdecl fcn_0046bd20(int, int, int, int, int, char*, int);

/* ADDRESS: GOLDTL 0x00532750 */
void __cdecl d3_DrawBuildingUpgradeLabel(char* sceneNode)
{
	int rc[4];
	char key[0x60];
	char value[0x100];
	unsigned short* item;
	unsigned short* hit;
	char* ownerRec;

	if ((int) g_7746c8 != 0) {
		ownerRec = (char*) g_7746c8;
	} else {
		if (g_7746c4 == 0) {
			return;
		}
		ownerRec = g_7746c4;
	}
	if (strstr(sceneNode, (char*) 0x6a1f84) == 0) {
		return;
	}
	strcpy(key, sceneNode + 0x10);
	if ((int) g_7746c8 != 0) {
		item = (unsigned short*) fcn_00502cd0(*(int*) (ownerRec + 0x5d), 1, 4, 6);
	} else {
		item = (unsigned short*) fcn_00502cd0(*(int*) (ownerRec + 0x5d), 1, 4, 2);
	}
	while (item != 0) {
		if (strcmpi(key,
		        (char*) (*(int*) 0x99ec10 + (int) *item * 0x40 + (int) *item + 1)) == 0) {
			hit = item;
			goto found;
		}
		item = gm_NextEntityQueryMatch();
	}
	if ((int) g_7746c8 == 0) {
		return;
	}
	hit = (unsigned short*) fcn_00502cd0(*(int*) (ownerRec + 0x5d), 1, 0, 0xfd);
found:
	if (hit == 0) {
		return;
	}
	if (*hit == 0xfd) {
		if ((int) g_7746cc != 0) {
			sprintf(value, (char*) 0x68b3f8,
				*(char**) ((int) *(unsigned short*) (int) g_7746cc * 8 + 0x14a79c0),
				*(char**) 0x14a5530);
		} else {
			sprintf(value, (char*) 0x68b3f8,
				*(char**) ((int) *(unsigned char*) ownerRec * 0x38 + 0x14a6558),
				*(char**) 0x14a5530);
		}
	} else {
		sprintf(value, (char*) 0x68b3f8,
			*(char**) ((int) *hit * 8 + 0x14a79c0), *(char**) 0x14a552c);
	}
	if (d3_GetObjectScreenRect(sceneNode, rc)) {
		fcn_0046bd20((rc[2] - rc[0]) / 2 + rc[0] - 0x50, rc[1], 0xa0, 0x60,
			g_77250c, value, 0x28);
	}
}
