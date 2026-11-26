#include <string.h>
#include <stdio.h>
#include "Develop/DieGildeAddOn/game/building_prototype.h"
extern int d3_CurrentContextIndex;
extern unsigned char g_7747b0;
extern unsigned char* lpGebaeudePROT;
extern char g_774964;
extern int g_774670;
extern int main_LoopFlags;
extern int g_1040494;
extern int d2_ScreenHeight;
extern int g_67a370;
extern char* g_6b8300;
extern int g_7e2700;

int __cdecl fcn_0042df70(void*);
int __cdecl fcn_0042df30(void*, int);
unsigned char* __cdecl fcn_004730c0(int, int, int, int, char*, int, int);
void __cdecl fcn_00473150(unsigned char*);
int __cdecl init_GetGebaeudeSceneName(int idx, char* out);
void __cdecl d3_SelectSceneContext(int a, int b);
char __cdecl d3_LoadScene(const char* filename, void* stream, int progress);
void __cdecl fcn_00516de0(char* a1, unsigned char a2);
int __cdecl fcn_004026f0(char* p);
void __cdecl gv_Free3Fields(int);
void __cdecl fcn_0045b290(int, int);
char __cdecl d3_TraverseSceneObjects(char* scene, char* node, unsigned int flags, void (__cdecl* cb)(char*));
int __cdecl CompareVector3WithinTolerance(float* a, float* b, float eps);
void __cdecl d3_TransformPoint(char* src, char* pos, float* out);
void __cdecl ch_SetPosition(int, void*, int);
char* __cdecl ch_SelectRandomDummy(void);
int __cdecl fcn_00413160(void);
void __cdecl ReportClientMessage(const char* msg);
int __cdecl main_RunFrameLoop(void*, int);
char* __cdecl fcn_00445600(int, int, int, char*);

/* lpGebaeudePROT row (0x24d bytes); only the leading type byte is read here. */
typedef struct {
	unsigned char type;
	char pad1[0x24c];
} GebProt_5110d0;

/* ADDRESS: GOLDTL 0x005110d0 */
void __cdecl init_LoadGebaeudeScene(int prototypeIndex)
{
	char name[260];
	char scene[128];
	char pos[16];
	char tmp[512];
	char* p;
	unsigned char* mode;
	int v;
	int obj;
	int saved;
	int restore;
	int progress;
	int flags;

	saved = d3_CurrentContextIndex;
	progress = 0;
	restore = 0;
	if ((g_7747b0 & 8) != 0 && !fcn_0042df70((void*) 0x538060)) {
		fcn_0042df30((void*) 0x538060, 1);
		restore = 1;
	}
	p = (char*) (((BUILDING_PROTOTYPE*)lpGebaeudePROT)[prototypeIndex].category + 0x7f3b00);
	if (*p == (char) 0xff) {
		if (g_774964 != 0 && (g_774670 <= 0 || g_7e2700 != 0)) {
			flags = (main_LoopFlags & 0xfffffff7) | 0x80;
			mode = fcn_004730c0(0, 0, g_1040494, d2_ScreenHeight, "BLACK", 0x32, 1);
			while (!(*mode & 4)) {
				main_RunFrameLoop(0, flags);
			}
			fcn_00473150(mode);
			progress = 0x526bf0;
		}
		v = fcn_00413160();
		if (v == -1) {
			ReportClientMessage("init_LoadGebaeudeScene:Could not find a free universe...");
		}
		d3_SelectSceneContext(v, 0);
		init_GetGebaeudeSceneName(prototypeIndex, tmp);
		sprintf(name, "scenes/*gb_%s.ed3", tmp);
		strupr(name);
		sprintf(tmp, "init_LoadGebaeudeScene: %s", name);
		if (!d3_LoadScene(name, 0, progress)) {
			d3_SelectSceneContext(saved, 0);
			goto done;
		}
		d3_SelectSceneContext(v, 0);
		if (g_6b8300 != 0) {
			fcn_00516de0(g_6b8300, 1);
		}
		d3_SelectSceneContext(d3_CurrentContextIndex, 0);
		d3_TraverseSceneObjects((char*) g_67a370, 0, 0x160, (void (__cdecl*)(char*)) 0x5105a0);
		d3_TraverseSceneObjects((char*) g_67a370, 0, 6, (void (__cdecl*)(char*)) 0x510bd0);
		*p = (char) v;
		d3_SelectSceneContext(saved, 0);
		goto done;
	}
	if (!*(char*) (*p * 0x3dc + 0x1043695)) {
		goto done;
	}
	if (g_774964 != 0 && g_774670 <= 0) {
		flags = (main_LoopFlags & 0xfffffff7) | 0x80;
		mode = fcn_004730c0(0, 0, g_1040494, d2_ScreenHeight, "BLACK", 0x32, 1);
		while (!(*mode & 4)) {
			main_RunFrameLoop(0, flags);
		}
		fcn_00473150(mode);
		progress = 0x526bf0;
	}
	obj = *p;
	d3_SelectSceneContext(obj, 0);
	init_GetGebaeudeSceneName(prototypeIndex, scene);
	sprintf(name, "scenes/*gb_%s.ed3", scene);
	strupr(name);
	if (!d3_LoadScene(name, 0, progress)) {
		d3_SelectSceneContext(saved, 0);
		goto done;
	}
	if (g_6b8300 != 0) {
		fcn_00516de0(g_6b8300, 1);
	}
	d3_SelectSceneContext(d3_CurrentContextIndex, 0);
	gv_Free3Fields(*(int*) (g_67a370 + 0xb0));
	*(int*) (g_67a370 + 0xb0) = 0;
	fcn_004026f0((char*) g_67a370);
	fcn_0045b290(*(int*) (g_67a370 + 0xb0), (int) g_6b8300);
	d3_TraverseSceneObjects((char*) g_67a370, 0, 0x160, (void (__cdecl*)(char*)) 0x5105a0);
	d3_TraverseSceneObjects((char*) g_67a370, 0, 6, (void (__cdecl*)(char*)) 0x510bd0);
	for (v = 0x14d0020; v < 0x14d0c20; v += 4) {
		char* e = *(char**) v;

		if (e != 0 && *(int*) (e + 0x88) == obj * 0x3dc + 0x10432c0) {
			if (CompareVector3WithinTolerance((float*) (e + 0x38), (float*) 0x662d70, 0.5f)) {
				char* d;

				if ((*(int*) (e + 0x124) == 0 || (d = fcn_00445600(0, 0x100, 0, "dummy_TRANSPORTER")) == 0)
					&& (d = ch_SelectRandomDummy()) == 0
					&& (d = fcn_00445600(0, 0x100, 0, "dummy_EINGANG")) == 0
					&& (d = fcn_00445600(0, 0x100, 0, "dummy_TRANSPORTER_ENTRY")) == 0)
					continue;
				d3_TransformPoint(d, d + 0x4c, (float*) pos);
				ch_SetPosition((int) e, pos, 1);
			} else {
				ch_SetPosition((int) e, e + 0x38, 1);
			}
		}
	}
	*(char*) (*p * 0x3dc + 0x1043695) = 0;
	d3_SelectSceneContext(saved, 0);
done:
	if ((g_7747b0 & 8) != 0 && restore != 0) {
		fcn_0042df30((void*) 0x538060, 0);
	}
}
