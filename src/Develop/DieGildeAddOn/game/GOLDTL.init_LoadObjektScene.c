#include <stdio.h>
#include <string.h>

#include "client_timer.h"
#include "client_scene_loader.h"

extern int d3_CurrentContextIndex;
extern char* lpObjektePROT;
extern char g_774964;
extern int g_774670;
extern int d2_ScreenHeight;
extern int g_1040494;
extern int main_LoopFlags;
extern char g_7747b0;
extern char init_SceneContextIndices[];
extern char g_10432c0[];
extern void* ch_CharacterSlots[];
extern int g_67a370;
extern int g_6b8300;
extern float g_662d70[];
extern char s_67d67c[];
extern char s_6a1c1c[];
extern char s_6a1c30[];
extern char s_68b0f4[];
extern char s_675908[];
extern char s_68b1e0[];

int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00473150(char*);
void __cdecl fcn_004432d0(int, int);
char __cdecl d3_LoadScene(const char*, void*, SCENE_PROGRESS);
void __cdecl gv_Free3Fields(int*);
int __cdecl fcn_004026f0(char*);
void __cdecl fcn_0045b290(char*, int);
char __cdecl d3_TraverseSceneObjects(int, void*, int, void (__cdecl*)(void));
int __cdecl CompareVector3WithinTolerance(float*, float*, float);
char* __cdecl fcn_00445600(char*, int, char*, char*);
char* __cdecl ch_SelectRandomDummy(void);
void __cdecl d3_TransformPoint(char*, float*, float*);
void __cdecl ch_SetPosition(char*, float*, int);
#include "Develop/DieGildeAddOn/game/ch_ground.h"
int __cdecl fcn_00413160(void);
void __cdecl ReportClientMessage(const char*);
int __cdecl fcn_005105a0(char*);
void __cdecl fcn_00510bd0(char*);
void __cdecl fcn_00526bf0(int, int, int);
void __cdecl fcn_00538060(void);
char* __cdecl fcn_004730c0(int, int, int, int, int, int, int);

/* ADDRESS: GOLDTL 0x00510c90 */
void __cdecl init_LoadObjektScene(int a0)
{
	char path[0x100];
	char buf[0x10];
	int saved;
	int progress;
	int paused;
	int type;
	int slot;
	char* name;
	char* obj;
	char* found;
	void** p;

	saved = d3_CurrentContextIndex;
	name = lpObjektePROT + a0 * 0x41;
	progress = 0;
	paused = 0;
	if (g_774964 && g_774670 <= 0) {
		unsigned int flags;
		unsigned char* ch;

		flags = (main_LoopFlags & 0xfffffff7) | 0x100080;
		ch = (unsigned char*) fcn_004730c0(0, 0, g_1040494, d2_ScreenHeight, s_67d67c, 0x32, 1);
		while ((*ch & 4) == 0) {
			fcn_005373e0(0, flags);
		}
		fcn_00473150((char*) ch);
		progress = (int) fcn_00526bf0;
	}
	if ((g_7747b0 & 8) && !fcn_0042df70((TIMER_CALLBACK) fcn_00538060)) {
		fcn_0042df30((TIMER_CALLBACK) fcn_00538060, 1);
		paused = 1;
	}
	if (init_SceneContextIndices[a0] == -1) {
		type = fcn_00413160();
		if (type == -1) {
			ReportClientMessage(s_6a1c30);
		}
		fcn_004432d0(type, 0);
		sprintf(path, s_6a1c1c, name + 1);
		strupr(path);
		if (d3_LoadScene(path, 0, (SCENE_PROGRESS) progress)) {
			fcn_004432d0(d3_CurrentContextIndex, 0);
			d3_TraverseSceneObjects(g_67a370, 0, 0x1e0, (void (__cdecl*)(void)) fcn_005105a0);
			d3_TraverseSceneObjects(g_67a370, 0, 6, (void (__cdecl*)(void)) fcn_00510bd0);
			init_SceneContextIndices[a0] = (char) type;
			fcn_004432d0(saved, 0);
		}
	} else {
		type = (signed char) init_SceneContextIndices[a0];
		if (g_10432c0[type * 0xf7 * 4 + 0x3d5] != 0) {
			slot = type * 0xf7;
			fcn_004432d0(type, 0);
			sprintf(path, s_6a1c1c, name + 1);
			strupr(path);
			if (d3_LoadScene(path, 0, (SCENE_PROGRESS) progress)) {
				fcn_004432d0(d3_CurrentContextIndex, 0);
				gv_Free3Fields((int*) *(int*) (g_67a370 + 0xb0));
				*(int*) (g_67a370 + 0xb0) = 0;
				fcn_004026f0((char*) g_67a370);
				fcn_0045b290((char*) *(int*) (g_67a370 + 0xb0), g_6b8300);
				d3_TraverseSceneObjects(g_67a370, 0, 0x1e0, (void (__cdecl*)(void)) fcn_005105a0);
				d3_TraverseSceneObjects(g_67a370, 0, 6, (void (__cdecl*)(void)) fcn_00510bd0);
				p = ch_CharacterSlots;
				do {
					obj = (char*) *p;
					if (obj != 0
					    && *(int*) (obj + 0x88) == (int) (g_10432c0 + slot * 4)) {
						if (CompareVector3WithinTolerance((float*) (obj + 0x38), g_662d70, 0.5f) != 0) {
							if ((*(int*) (obj + 0x124) != 0
							     && (found = fcn_00445600(0, 0x100, 0, s_68b0f4)) != 0)
							    || (found = ch_SelectRandomDummy()) != 0
							    || ((found = fcn_00445600(0, 0x100, 0, s_675908)) != 0
							        || (found = fcn_00445600(0, 0x100, 0, s_68b1e0)) != 0)) {
								d3_TransformPoint(found, (float*) (found + 0x4c), (float*) buf);
								ch_SetPosition(obj, (float*) buf, 1);
							}
						} else {
							ch_SetPosition(obj, (float*) (obj + 0x38), 1);
							ch_PlaceOnGround(obj, 1);
						}
					}
					p++;
				} while ((int) p < 0x14d0c20);
				g_10432c0[(signed char) init_SceneContextIndices[a0] * 0x3dc + 0x3d5] = 0;
				fcn_004432d0(saved, 0);
			}
		}
	}
	if ((g_7747b0 & 8) && paused) {
		fcn_0042df30((TIMER_CALLBACK) fcn_00538060, 0);
	}
}
