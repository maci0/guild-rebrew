#include "Develop/DieGildeAddOn/game/game_data.h"

int __cdecl d3_GetContextIndex(int);
void __cdecl d3_SelectSceneContext(int, int);
void __cdecl d3_DestroyObject(int);
int* __cdecl fcn_00442910(int, float*, float*, char*);
void __cdecl fcn_0043a720(int*, char*);

/* ADDRESS: GOLDTL 0x00407800 */
void __cdecl ch_SetBodyAttachment(char* e, int mode, char* name)
{
	int* slot;

	float rotation[3];
	float position[4];
	int saved_mode;

	slot = (int*) 0;
	position[0] = 0.0f;
	position[1] = 0.0f;
	position[2] = 0.0f;
	position[3] = 0.0f;
	rotation[0] = 0.0f;
	rotation[1] = 0.0f;
	rotation[2] = 0.0f;
	if (mode == 1) {
		slot = (int*) (e + 0x68);
	} else if (mode == 2) {
		slot = (int*) (e + 0x64);
	} else if (mode == 3) {
		slot = (int*) (e + 0x6c);
	}
	saved_mode = d3_CurrentContextIndex;
	if (name != 0) {
		d3_SelectSceneContext(d3_GetContextIndex(*(int*) (e + 0x88)), 1);
		if (*slot != 0) {
			d3_DestroyObject(*slot);
			*slot = 0;
		}
		*slot = (int) fcn_00442910(*(int*) (e + 0x34), position, rotation, name);

		if (*slot == 0) {
			d3_SelectSceneContext(saved_mode, 1);
			return;
		}
		*(unsigned char*) ((char*) *slot + 0x216) |= 3;
		*(unsigned char*) ((char*) *slot + 0x214) &= 0x7f;
		*(unsigned char*) ((char*) *slot + 0x217) &= 0xfe;
		*(int*) ((char*) *slot + 0x220) = 5;
		if (mode == 1) {
			fcn_0043a720((int*) *slot, "d3_LeftHand");
			d3_SelectSceneContext(saved_mode, 1);
			return;
		}
		if (mode == 2) {
			fcn_0043a720((int*) *slot, "d3_RightHand");
			d3_SelectSceneContext(saved_mode, 1);
			return;
		}
		if (mode == 3) {
			fcn_0043a720((int*) *slot, "d3_Head");
		}
		d3_SelectSceneContext(saved_mode, 1);
	} else {
		d3_SelectSceneContext(d3_GetContextIndex(*(int*) (e + 0x88)), 1);
		if (*slot != 0) {
			d3_DestroyObject(*slot);
			*slot = 0;
		}
		d3_SelectSceneContext(saved_mode, 1);
	}
}
