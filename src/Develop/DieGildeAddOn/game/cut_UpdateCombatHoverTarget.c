#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/Units/d2.v1/d2_gui.h"
int __cdecl d3_FindSceneObjectAtScreenPoint(float, float, int, int); int __cdecl d3_SetObjectVisible(int, int);
int __cdecl d3sm_RaycastScreenPoint(int, int, int, int*, int*);
char __cdecl d3_GridPointToWorld(int, int, int, float*);
int __cdecl gm_GetEntityControlMask(int, int);
int* __cdecl gm_GetEquippedCombatGear(int);
int __cdecl fcn_0064f170(char*, char*, int);
#include <string.h>

/* ADDRESS: GOLDTL 0x004d06d0 */
void __cdecl cut_UpdateCombatHoverTarget(void)
{
	float buf[3];
	char* obj;
	int* rec;
	int* meta;
	unsigned int sceneObj;
	int i;
	int count;
	int x;
	int y;
	int kind;
	int same;
	unsigned short code;

	sceneObj = *(unsigned int*) (*(int*) &d3_ActiveScene + 0xb0);
	code = 0x23;
	i = 0;
	*(int*) &d2_HoveredSceneObject = 0;
	d2_CursorStateId = 0;
	if (*(short*) &io_ActiveCursorX > 0 && *(short*) &io_ActiveCursorX < g_1040494
		&& *(short*) &io_ActiveCursorY > 0 && *(short*) &io_ActiveCursorY < d2_ScreenHeight
		&& d2_CurrentElementId == -1) {
		x = *(short*) &io_ActiveCursorX;
		y = *(short*) &io_ActiveCursorY;
		*(int*) &d2_HoveredSceneObject = d3_FindSceneObjectAtScreenPoint((float) x, (float) y, 0x40, 1);
		if (*(int*) &d2_HoveredSceneObject != 0 || *(int*) 0x772eb8 == 0) {



			if (*(int*) 0x772ea0 != 0) {
				d3_SetObjectVisible(*(int*) 0x772ea0, 0);
			}
		}
		else if ((d3sm_RaycastScreenPoint(sceneObj, x + 0x1a, y + 0x1a, &x, &y) & 0xff) != 0xffffffff) {
			d3_GridPointToWorld(sceneObj, x, y, buf);
			buf[1] = buf[1] + *(float*) 0x6640cc;
			d2_CursorStateId = 0;
		}
		if (*(int*) &d2_HoveredSceneObject != 0) {
			count = 0;
			for (rec = (int*) &ch_ContextCharacters; rec < (int*) 0x7e42dc; rec++) {
				i = *rec;
				if (i != 0 && *(char*) (i + 0x188) != 0) {
					if ((gm_GetEntityControlMask(*cut_ActivePlayerEntity, i) & 0x800) != 0
						&& io_RightShiftKeyDown == 0) {
						kind = 0;
						meta = gm_GetEquippedCombatGear(i);
						if (meta != 0) {
							if (*meta == 0x160) code = 0x18;
							else if (*meta == 0x174) code = 0x19;
							else if (*meta == 0x16e) code = 0x1e;
							else if (*meta == 0x154) code = 0x1a;
							else if (*meta == 0x158) code = 0x1f;
							else if (*meta == 0x15e) code = 0x21;
							else if (*meta == 0x156) code = 0x23;
							else if (*meta == 0x176) code = 0x25;



						}
						count += 1;
					}
				}
			}
			if (count > 1) {
				code = 0x23;
			}
			if (*(int*) &d2_HoveredSceneObject == 0 || d2_CurrentElementId != -1) {
				d2_CursorStateId = 0;
				return;
			}
			obj = (char*) *(int*) &d2_HoveredSceneObject;
			if (memcmp(obj, (char*) 0x68b82c, 10) == 0 && count != 0) {
				d2_CursorStateId = 0x1c;
				*(int*) 0x772e90 = (int) *(int*) &d2_HoveredSceneObject;
				return;
			}
			if (fcn_0064f170((char*) *(int*) &d2_HoveredSceneObject, (char*) 0x68b820, 10) == 0 && count != 0) {
				d2_CursorStateId = 0x1b;
				*(int*) 0x772e90 = (int) *(int*) &d2_HoveredSceneObject;
				return;
			}
			if (fcn_0064f170((char*) *(int*) &d2_HoveredSceneObject, (char*) 0x68b818, 4) == 0 && count != 0) {
				d2_CursorStateId = 0xe;
				*(int*) 0x772e90 = (int) *(int*) &d2_HoveredSceneObject;
				return;
			}
			if (*(int*) (*(int*) &d2_HoveredSceneObject + 0x220) == 2 && count != 0) {
				sceneObj = *(unsigned int*) (*(int*) &d2_HoveredSceneObject + 0x204);
				if ((gm_GetEntityControlMask(*cut_ActivePlayerEntity, sceneObj) & 0x800) == 0
					|| io_RightShiftKeyDown != 0) {
					d2_CursorStateId = code;
					*(int*) 0x772e90 = (int) *(int*) &d2_HoveredSceneObject;
					return;
				}
			}
			else {
				d2_CursorStateId = 0;
			}
			*(int*) 0x772e90 = (int) *(int*) &d2_HoveredSceneObject;
			return;
		}
	}
	*(int*) 0x772e90 = 0;
	*(int*) &sv_HoveredCharacter = 0;
}
