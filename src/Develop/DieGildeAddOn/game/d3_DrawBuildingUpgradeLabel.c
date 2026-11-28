#include <stdio.h>
#include <string.h>
#include "Develop/DieGildeAddOn/game/game_data.h"

unsigned short* __cdecl gm_NextEntityQueryMatch(void);
void* __cdecl gm_QueryEntities(int, int, ...);
char __cdecl d3_GetObjectScreenRect(void*, int*);
void __cdecl d2_DrawWordWrappedText(int, int, int, int, int, char*, int);

/* ADDRESS: GOLDTL 0x00532750 */
/* ADDRESS: GOLDDE 0x0051b0d0 */
void __cdecl d3_DrawBuildingUpgradeLabel(char* sceneNode)
{
	int rc[4];
	char key[0x60];
	char value[0x100];
	unsigned short* item;
	unsigned short* hit;
	char* ownerRec;

	if ((int) d2_InteriorBuilding != 0) {
		ownerRec = (char*) d2_InteriorBuilding;
	} else {
		if (d2_VisitedBuilding == 0) {
			return;
		}
		ownerRec = d2_VisitedBuilding;
	}
	if (strstr(sceneNode, (char*) 0x6a1f84) == 0) {
		return;
	}
	strcpy(key, sceneNode + 0x10);
	if ((int) d2_InteriorBuilding != 0) {
		item = (unsigned short*) gm_QueryEntities(*(int*) (ownerRec + 0x5d), 1, 4, 6);
	} else {
		item = (unsigned short*) gm_QueryEntities(*(int*) (ownerRec + 0x5d), 1, 4, 2);
	}
	while (item != 0) {
		if (strcmpi(key,
		        (char*) (*(int*) 0x99ec10 + (int) *item * 0x40 + (int) *item + 1)) == 0) {
			hit = item;
			goto found;
		}
		item = gm_NextEntityQueryMatch();
	}
	if ((int) d2_InteriorBuilding == 0) {
		return;
	}
	hit = (unsigned short*) gm_QueryEntities(*(int*) (ownerRec + 0x5d), 1, 0, 0xfd);
found:
	if (hit == 0) {
		return;
	}
	if (*hit == 0xfd) {
		if ((int) sv_SelectedBuilding != 0) {
			sprintf(value, (char*) 0x68b3f8,
				*(char**) ((int) *(unsigned short*) (int) sv_SelectedBuilding * 8 + 0x14a79c0),
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
		d2_DrawWordWrappedText((rc[2] - rc[0]) / 2 + rc[0] - 0x50, rc[1], 0xa0, 0x60,
			d2_ScreenSurface, value, 0x28);
	}
}
