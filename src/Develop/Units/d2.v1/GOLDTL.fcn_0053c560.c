/*
 * Parent-profession chooser of the "ChooseProfession" dialog chain.
 *
 * Entries 4 and 5 of the 0x7e1fc0 table select the father and mother slot;
 * each of the six 48-byte rows below holds the relation named by the
 * fcn_0053b090 profession figures ("dummy_VATER", "dummy_MUTTER", the four
 * grandparent relations).  The candidate figure comes from the dialog at
 * 0x7746a0 and is stored in its +0x23c slot field once picked.
 */
#include <string.h>

#include "Develop/Units/d3/d3_camera.h"
#include "client_lighting.h"

extern int evt_LastGfxScriptId;
extern int g_67a370;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int d3_ActiveCameraAnimation;
extern int d2_ScreenHeight;
extern int g_1040494;
extern int g_774654;
extern int g_7746a0;
extern char g_7e23e3;

typedef struct {
	float a;
	float b;
	float c;
} Vec3;

/* SIZE 0x240 */
typedef struct {
	char pad0[0x23c];
	int slot;
} Figure;

typedef void (__cdecl *VirtFn)(int, int, int, int);


int __cdecl fcn_00533880(void);
int __cdecl fcn_005338a0(void);
int __cdecl d3_SelectSceneContext(int, int);
Figure *__cdecl ch_CreateCharacterAtSceneObject(char *, char *, int);
int __cdecl d2_LoadForm(int, int, char *);
void __cdecl fcn_00471d80(int, int);
void __cdecl d3_InitSkyLayer(char *);
int __cdecl d3_BlendSceneLightingPreset(unsigned int, float, float, int);
void __cdecl d2_DestroyForm(int);
int __cdecl main_RunFrameLoop(int, int);
int __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
void __cdecl d3_FreeObjectAnimation(void *);
void __cdecl d3_AnimateObjectTransform(char *, Vec3 *, Vec3 *, int, int);
char *__cdecl d3_FindSceneObject(char *, int, char *, char *);
void __cdecl ch_QueueWalkToDummyRotate(char *, char *);
int __cdecl fcn_0053b1b0(void);
int __cdecl d2_ShowChooseProfessionDialog(int);
unsigned int __cdecl d2_ChooseCharacterModel(int);
void __cdecl d2_SetFormVisibility(int, int);
char *__cdecl fcn_004730c0(int, int, int, int, char *, int, int);
int __cdecl ch_DestroyCharacter(char *);
void *__cdecl evt_FindScriptById(int);
int __cdecl evt_RequestScriptExit(char *);
void __cdecl evt_WaitForScriptExit(int);
void __cdecl gv_Free3Fields(void *);
void __cdecl d3_DestroySkyLayer(void);
void __cdecl fcn_00473150(char *);

/* ADDRESS: GOLDTL 0x0053c560 */
int __cdecl d2_RunParentProfessionSelection(void)
{
	int ret = 0;
	Figure *rhFrau;
	Figure *rhMann;
	Figure *hwMann;
	Figure *vhFrau;
	Figure *kampfMann;
	Figure *nnFrau;
	Figure *vhMann;
	Figure *hwFrau;
	Figure *nnMann;
	char *spr = 0;
	Vec3 parentB;
	int oldSound;
	Vec3 parentA;
	int i;
	char buf[6][48] = {
		"dummy_GROSSVATER_VAETERLICH",
		"dummy_GROSSMUTTER_VAETERLICH",
		"dummy_GROSSVATER_MUETTERLICH",
		"dummy_GROSSMUTTER_MUETTERLICH",
		"dummy_VATER",
		"dummy_MUTTER"
	};
	int mode;
	int flag = 1;
	int obj;
	Figure *obj2;
	char *found;
	int base;
	int sub;
	VirtFn fn;

	memset((void *) 0x7e1fc0, 0, 0x2c);
	memset((void *) 0x7e1fc0, -1, 0x18);
	fcn_00533880();
	fcn_005338a0();
	d3_SelectSceneContext(1, 0);
	base = g_67a370;
	if (base != 0) {
		sub = *(int *) (base + 0x3c8);
		if (sub != 0) {
			fn = *(VirtFn *) (sub + 0x210);
			if (fn != 0)
				fn(base, 4, sub + 0x214, 0);
		}
	}
	oldSound = evt_LastGfxScriptId;
	if (g_6b8300 != 0) {
		base = g_6b8300;
		*(unsigned char *) (base + 0x8036) =
		    (unsigned char) ((*(unsigned char *) (base + 0x8036) & 0xeb) | 8);
	}
	nnMann = ch_CreateCharacterAtSceneObject((char *) 0x6a3ecc, (char *) 0x6a3ee8, 0);
	nnFrau = ch_CreateCharacterAtSceneObject((char *) 0x6a3eb0, (char *) 0x6a3c34, 8);
	hwMann = ch_CreateCharacterAtSceneObject((char *) 0x6a3e84, (char *) 0x6a3ea0, 1);
	hwFrau = ch_CreateCharacterAtSceneObject((char *) 0x6a3e68, (char *) 0x6a3ccc, 7);
	kampfMann = ch_CreateCharacterAtSceneObject((char *) 0x6a3e54, (char *) 0x6a3d7c, 4);
	vhMann = ch_CreateCharacterAtSceneObject((char *) 0x6a3e3c, (char *) 0x67fa28, 3);
	vhFrau = ch_CreateCharacterAtSceneObject((char *) 0x6a3e24, (char *) 0x68d45c, 5);
	rhMann = ch_CreateCharacterAtSceneObject((char *) 0x6a3e00, (char *) 0x6a3e14, 2);
	rhFrau = ch_CreateCharacterAtSceneObject((char *) 0x6a3dec, (char *) 0x6a3c78, 6);
	obj = d2_LoadForm(0, 0, (char *) 0x6a3dd4);
	fcn_00471d80(obj, 1);
	d3_InitSkyLayer((char *) 0x6a3dc4);
	i = 4;
	d3_BlendSceneLightingPreset(i, 0, 1.0f, 1);
	if (*(int *) 0x6a37f8 != -1) {
		d2_DestroyForm(*(int *) 0x6a37f8);
		*(int *) 0x6a37f8 = -1;
	}
	d2_SuppressOverlay = 0;
	if (main_RunFrameLoop((int) d2_RunParentProfessionSelection, 0x12d6) != 0) {
		do {
			if (flag) {
				for (i = 4; i < 6; i++) {
					if (((int *) 0x7e1fc0)[i] == -1)
						break;
				}
				if (i < 6) {
					d2_SetForm(obj, 0);
					io_AppendText(0x6811b0);
					io_AppendText(0x1ae6, i + 0x1aea);
					if (i % 2) {
						parentA = *(Vec3 *) (d3_ActiveCamera + 0xfc);
						parentB = *(Vec3 *) (d3_ActiveCamera + 0x108);
					} else {
						parentA = *(Vec3 *) (d3_ActiveCamera + 0xe4);
						parentB = *(Vec3 *) (d3_ActiveCamera + 0xf0);
					}
					d3_FreeObjectAnimation(d3_ActiveCamera);
					d3_CameraAnimating = 0;
					d3_ActiveCameraAnimation = 0;
					d3_AnimateObjectTransform(d3_ActiveCamera, &parentA, &parentB, 0x50, 8);
				}
				flag = 0;
			}
			if (g_14ce8e0 != 0)
				g_774654 = 1;
			if (g_7746a0 != 0) {
				obj2 = (Figure *) *(int *) (g_7746a0 + 0x204);
				if (obj2 != 0) {
					if (obj2->slot == -1) {
						mode = 0;
						if (obj2 == nnMann || obj2 == nnFrau)
							mode = 2;
						else if (obj2 == vhMann || obj2 == vhFrau)
							mode = 0;
						else if (obj2 == kampfMann)
							mode = 3;
						else if (obj2 == rhMann || obj2 == rhFrau)
							mode = 4;
						else if (obj2 == hwMann || obj2 == hwFrau)
							mode = 1;
						if (i % 2) {
							if (obj2 == nnFrau || obj2 == vhFrau ||
							    obj2 == rhFrau || obj2 == hwFrau) {
								i = 5;
								goto slot_found;
							}
						} else if (obj2 == nnMann || obj2 == vhMann ||
						    obj2 == rhMann || obj2 == hwMann ||
						    obj2 == kampfMann) {
							i = 4;
slot_found:
							((int *) 0x7e1fc0)[i] = mode;
							obj2->slot = i;
							found = d3_FindSceneObject(0, 0x100, 0, buf[i]);
							if (found != 0)
								ch_QueueWalkToDummyRotate((char *) obj2, found);
						}
					}
					flag = 1;
				}
			}
			if (i >= 6) {
				d2_SetForm(obj, 0);
				io_AppendText(0x6811b0);
				d2_SetFormVisibility(obj, 0);
				d3_FreeObjectAnimation(d3_ActiveCamera);
				d3_CameraAnimating = 0;
				d3_ActiveCameraAnimation = 0;
				d3_AnimateObjectTransform(d3_ActiveCamera,
				    (Vec3 *) (d3_ActiveCamera + 0x114),
				    (Vec3 *) (d3_ActiveCamera + 0x120), 0x50, 8);
				if (fcn_0053b1b0()) {
					if (d2_ShowChooseProfessionDialog(0xc6) &&
					    d2_ChooseCharacterModel((unsigned char) g_7e23e3)) {
						g_774654 = 1;
						ret = 1;
					} else if (!ret) {
						d2_SetFormVisibility(obj, 1);
					}
				} else {
					g_774654 = 1;
					ret = 0;
					d2_SetFormVisibility(obj, 1);
				}
			}
		} while (main_RunFrameLoop((int) d2_RunParentProfessionSelection, 0x12d6) != 0);
		if (ret == 1) {
			spr = fcn_004730c0(0, 0, g_1040494,
			    d2_ScreenHeight, (char *) 0x67d67c, 0x5a, 1);
			while ((*(unsigned char *) spr & 4) == 0)
				main_RunFrameLoop(0, 0xc6);
		}
	}
	if (nnMann != 0)
		ch_DestroyCharacter((char *) nnMann);
	if (nnFrau != 0)
		ch_DestroyCharacter((char *) nnFrau);
	if (hwMann != 0)
		ch_DestroyCharacter((char *) hwMann);
	if (hwFrau != 0)
		ch_DestroyCharacter((char *) hwFrau);
	if (kampfMann != 0)
		ch_DestroyCharacter((char *) kampfMann);
	if (vhMann != 0)
		ch_DestroyCharacter((char *) vhMann);
	if (vhFrau != 0)
		ch_DestroyCharacter((char *) vhFrau);
	if (rhFrau != 0)
		ch_DestroyCharacter((char *) rhFrau);
	if (rhMann != 0)
		ch_DestroyCharacter((char *) rhMann);
	if (obj != -1)
		d2_DestroyForm(obj);
	if (oldSound != -1) {
		found = evt_FindScriptById(oldSound);
		if (found != 0)
			evt_RequestScriptExit(found);
		evt_WaitForScriptExit(oldSound);
	}
	if (*(int *) (g_67a370 + 0xb0) != 0) {
		gv_Free3Fields((void *) *(int *) (g_67a370 + 0xb0));
		*(int *) (g_67a370 + 0xb0) = 0;
	}
	d3_DestroySkyLayer();
	base = g_67a370;
	if (base != 0) {
		sub = *(int *) (base + 0x3c8);
		if (sub != 0) {
			fn = *(VirtFn *) (sub + 0x294);
			if (fn != 0)
				fn(base, 5, sub + 0x298, 0);
		}
	}
	d3_FreeObjectAnimation(d3_ActiveCamera);
	d3_CameraAnimating = 0;
	d3_ActiveCameraAnimation = 0;
	if (spr != 0)
		fcn_00473150(spr);
	return ret;
}
