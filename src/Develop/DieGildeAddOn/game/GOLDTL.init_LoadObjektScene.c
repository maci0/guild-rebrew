#include <stdio.h>
#include <string.h>

#include "client_timer.h"
#include "client_scene_loader.h"

extern int g_6b8010;
extern char* g_item_def_table;
extern char g_774964;
extern int g_774670;
extern int g_1040490;
extern int g_1040494;
extern int g_7e46ac;
extern char g_7747b0;
extern char g_7f3b40[];
extern char g_10432c0[];
extern void* g_14d0020[];
extern int g_67a370;
extern int g_6b8300;
extern char g_662d70[];
extern char s_67d67c[];
extern char s_6a1c1c[];
extern char s_6a1c30[];
extern char s_68b0f4[];
extern char s_675908[];
extern char s_68b1e0[];

int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00473150(char*);
void __cdecl fcn_004432d0(int, int);
char __cdecl fcn_00448360(const char*, void*, SCENE_PROGRESS);
void __cdecl gv_Free3Fields(int*);
int __cdecl fcn_004026f0(char*);
void __cdecl fcn_0045b290(char*, int);
char __cdecl fcn_00437ac0(int, void*, int, void (__cdecl*)(void));
int __cdecl fcn_00451840(float*, float*, float);
char* __cdecl fcn_00445600(char*, int, char*, char*);
char* __cdecl fcn_00407330(void);
void __cdecl fcn_00455350(char*, float*, float*);
void __cdecl ch_SetPosition(char*, float*, int);
int __cdecl fcn_004053a0(char*, int);
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

	saved = g_6b8010;
	name = g_item_def_table + a0 * 0x41;
	progress = 0;
	paused = 0;
	if (g_774964 && g_774670 <= 0) {
		unsigned int flags;
		unsigned char* ch;

		flags = (g_7e46ac & 0xfffffff7) | 0x100080;
		ch = (unsigned char*) fcn_004730c0(0, 0, g_1040494, g_1040490, s_67d67c, 0x32, 1);
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
	if (g_7f3b40[a0] == -1) {
		type = fcn_00413160();
		if (type == -1) {
			ReportClientMessage(s_6a1c30);
		}
		fcn_004432d0(type, 0);
		sprintf(path, s_6a1c1c, name + 1);
		strupr(path);
		if (fcn_00448360(path, 0, (SCENE_PROGRESS) progress)) {
			fcn_004432d0(g_6b8010, 0);
			fcn_00437ac0(g_67a370, 0, 0x1e0, (void (__cdecl*)(void)) fcn_005105a0);
			fcn_00437ac0(g_67a370, 0, 6, (void (__cdecl*)(void)) fcn_00510bd0);
			g_7f3b40[a0] = (char) type;
			fcn_004432d0(saved, 0);
		}
	} else {
		type = (signed char) g_7f3b40[a0];
		slot = type * 0xf7;
		if (g_10432c0[slot * 4 + 0x3d5] != 0) {
			fcn_004432d0(type, 0);
			sprintf(path, s_6a1c1c, name + 1);
			strupr(path);
			if (fcn_00448360(path, 0, (SCENE_PROGRESS) progress)) {
				fcn_004432d0(g_6b8010, 0);
				gv_Free3Fields((int*) *(int*) (g_67a370 + 0xb0));
				*(int*) (g_67a370 + 0xb0) = 0;
				fcn_004026f0((char*) g_67a370);
				fcn_0045b290((char*) *(int*) (g_67a370 + 0xb0), g_6b8300);
				fcn_00437ac0(g_67a370, 0, 0x1e0, (void (__cdecl*)(void)) fcn_005105a0);
				fcn_00437ac0(g_67a370, 0, 6, (void (__cdecl*)(void)) fcn_00510bd0);
				p = g_14d0020;
				do {
					obj = (char*) *p;
					if (obj != 0
					    && *(int*) (obj + 0x88) == (int) (g_10432c0 + slot * 4)) {
						if (fcn_00451840((float*) (obj + 0x38), (float*) g_662d70, 0.5f) != 0) {
							if ((*(int*) (obj + 0x124) != 0
							     && (found = fcn_00445600(0, 0x100, 0, s_68b0f4)) != 0)
							    || (found = fcn_00407330()) != 0
							    || ((found = fcn_00445600(0, 0x100, 0, s_675908)) != 0
							        || (found = fcn_00445600(0, 0x100, 0, s_68b1e0)) != 0)) {
								fcn_00455350(found, (float*) (found + 0x4c), (float*) buf);
								ch_SetPosition(obj, (float*) buf, 1);
							}
						} else {
							ch_SetPosition(obj, (float*) (obj + 0x38), 1);
							fcn_004053a0(obj, 1);
						}
					}
					p++;
				} while ((int) p < 0x14d0c20);
				g_10432c0[(signed char) g_7f3b40[a0] * 0x3dc + 0x3d5] = 0;
				fcn_004432d0(saved, 0);
			}
		}
	}
	if ((g_7747b0 & 8) && paused) {
		fcn_0042df30((TIMER_CALLBACK) fcn_00538060, 0);
	}
}
