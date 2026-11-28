#include "Develop/Units/d3/d3_object.h"



extern char g_868354[][0x2f4];
extern int sv_ClickedObjekt;
extern char* d2_HoveredSceneObject;
extern short io_ActiveCursorX;
extern short io_ActiveCursorY;
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/Units/d2.v1/client_dialog_state.h"
extern char s_6a41a4[];

int __cdecl sprintf(char*, const char*, ...);
char* __cdecl d3_SpawnCityMarkerObject(char*);
char* __cdecl RegisterStatusText(char*, char*, int);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_ClearStatusTextSlots(void);
int __cdecl main_RunFrameLoop(void*, int);
char* __cdecl d3_FindSceneObjectAtScreenPoint(float, float, int, int);
char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
char* __cdecl gm_AddObjekt(void);
char* __cdecl gm_FindNextFilteredEntity(void);
void __cdecl d2_ShowCityTradeInfoDialog(char*, int);

void __cdecl d3_ClearSceneObjectCache(void);
void __cdecl d3_EndCameraAndUiMode(void);

/* ADDRESS: GOLDDE 0x00588400 */
void __cdecl d3_SelectTavernCardTableCity(void)
{
	char* items[4];
	int i;
	char* city;

	items[0] = 0;
	items[1] = 0;
	items[2] = 0;
	items[3] = 0;
	for (i = 0; i < 3; i++) {
		items[i] = d3_SpawnCityMarkerObject(g_868354[i]);
		sprintf(items[i], s_6a41a4, g_868354[i]);
		RegisterStatusText(items[i], g_868354[i], 0);
	}
	d2_SetOverlayAnimation(0, 0);
	d2_ClearStatusTextSlots();
	if (main_RunFrameLoop((void*) d3_SelectTavernCardTableCity, 0x677d7) != 0) {
		do {
			(*(char**)&sv_ClickedObjekt) = 0;
			for (i = 0; i < 3; i++) {
				RegisterStatusText(items[i], g_868354[i], 0);
			}
			d2_HoveredSceneObject = d3_FindSceneObjectAtScreenPoint((float) io_ActiveCursorX, (float) io_ActiveCursorY, 0x60, 1);
			if (g_14ce8cc != 0 && d2_HoveredSceneObject != 0) {
				(*(char**)&sv_ClickedObjekt) = d2_HoveredSceneObject;
				for (i = 0; i < 3; i++) {
					if ((*(char**)&sv_ClickedObjekt) == items[i]) {
						for (city = gm_StartFilteredEntitySearch(1, 0, 0x47); city != 0; city = gm_FindNextFilteredEntity()) {
							if (*(int*) (city + 0x65) == i + 1) {
								d2_ShowCityTradeInfoDialog(city, 1);
								break;
							}
						}
					}
				}
			}
			else if (io_RightButtonReleased != 0) {
				d2_DialogCloseRequested = 1;
			}
		} while (main_RunFrameLoop((void*) d3_SelectTavernCardTableCity, 0x677d7) != 0);
	}
	d2_ClearStatusTextSlots();
	for (i = 0; i < 3; i++) {
		if (items[i] != 0) {
			d3_DestroyObject((D3_OBJECT*) (items[i]));
		}
	}
	d3_ClearSceneObjectCache();
	d3_EndCameraAndUiMode();
}
