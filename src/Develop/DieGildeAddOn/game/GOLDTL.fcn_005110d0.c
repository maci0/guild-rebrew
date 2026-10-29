#include <string.h>
#include <stdio.h>

extern int g_6b8010;
extern unsigned char g_7747b0;
extern unsigned char* lpGebaeudePROT;
extern char g_774964;
extern int g_774670;
extern int g_7e46ac;
extern int g_1040494;
extern int g_1040490;
extern int g_67a370;
extern char* g_6b8300;
extern int g_7e2700;

int __cdecl fcn_0042df70(void*);
int __cdecl fcn_0042df30(void*, int);
unsigned char* __cdecl fcn_004730c0(int, int, int, int, char*, int, int);
void __cdecl fcn_00473150(unsigned char*);
int __cdecl fcn_00511040(int idx, char* out);
void __cdecl fcn_004432d0(int a, int b);
char __cdecl fcn_00448360(const char* filename, void* stream, int progress);
void __cdecl fcn_00516c50(void* p, void* unit);
int __cdecl fcn_004026f0(char* p);
void __cdecl gv_Free3Fields(int);
void __cdecl fcn_0045b290(int, int);
char __cdecl fcn_00437ac0(char* scene, char* node, unsigned int flags, void (__cdecl* cb)(char*));
int __cdecl fcn_00451840(float* a, float* b, float eps);
void __cdecl fcn_00455350(char* src, char* pos, float* out);
void __cdecl ch_SetPosition(int, void*, int);
char* __cdecl fcn_00407330(void);
int __cdecl fcn_00413160(void);
void __cdecl fcn_0041d9e0(const char* msg);
int __cdecl fcn_005373e0(void*, int);
char* __cdecl fcn_00445600(int, int, int, char*);

/* ADDRESS: GOLDTL 0x005110d0 */
void __cdecl init_LoadGebaeudeScene(int a0)
{
	char name[260];
	char scene[128];
	char pos[16];
	char tmp[512];
	unsigned char* win;
	char* p;
	unsigned char* mode;
	int v;
	int obj;
	int saved;
	int restore;
	int i;

	saved = g_6b8010;
	restore = 0;
	if ((g_7747b0 & 8) != 0 && !fcn_0042df70((void*) 0x538060)) {
		fcn_0042df30((void*) 0x538060, 1);
		restore = 1;
	}
	p = (char*) (*(unsigned char*) (lpGebaeudePROT + a0 * 0x24d) + 0x7f3b00);
	if (*p != (char) 0xff) {
		if (!*(char*) (*(unsigned char*) p * 0x3dc + 0x1043695)) {
			goto label_511541;
		}
		if (g_774964 != 0 && g_774670 <= 0) {
			mode = fcn_004730c0(0, 0, g_1040494, g_1040490, "BLACK", 0x32, 1);
			while (!(*mode & 4)) {
				fcn_005373e0(0, (g_7e46ac & 0xfffffff7) | 0x80);
			}
			fcn_00473150(mode);
			restore = 0x526bf0;
		}
		obj = *p;
		fcn_004432d0(obj, 0);
		fcn_00511040(a0, scene);
		sprintf(name, "scenes/*gb_%s.ed3", scene);
		strupr(name);
		if (fcn_00448360(name, 0, restore)) {
			if (g_6b8300 != 0) {
				fcn_00516c50(g_6b8300, (void*) 1);
			}
			fcn_004432d0(saved, 0);
			gv_Free3Fields(*(int*) (g_67a370 + 0xb0));
			*(int*) (g_67a370 + 0xb0) = 0;
			fcn_004026f0((char*) g_67a370);
			fcn_0045b290(*(int*) (g_67a370 + 0xb0), (int) g_6b8300);
			fcn_00437ac0((char*) g_67a370, 0, 0x160, (void (__cdecl*)(char*)) 0x5105a0);
			fcn_00437ac0((char*) g_67a370, 0, 6, (void (__cdecl*)(char*)) 0x510bd0);
			for (i = 0x14d0020; i < 0x14d0c20; i += 4) {
				v = *(int*) i;
				if (v != 0 && *(int*) (v + 0x88) == obj * 0x3dc + 0x10432c0) {
					if (fcn_00451840((float*) (v + 0x38), (float*) 0x662d70, 0.5f)) {
						if ((*(int*) (v + 0x124) != 0 && (obj = (int) fcn_00445600(0, 0x100, 0, "dummy_TRANSPORTER")) != 0) || (obj = (int) fcn_00407330()) != 0 || ((obj = (int) fcn_00445600(0, 0x100,
						    0, "dummy_EINGANG")) != 0 || (obj = (int) fcn_00445600(0, 0x100, 0, "dummy_TRANSPORTER_ENTRY")) != 0)) {
							fcn_00455350((char*) obj, (char*) (obj + 0x4c), (float*) pos);
							ch_SetPosition(v, pos, 1);
						}
					} else {
						ch_SetPosition(v, (void*) (v + 0x38), 1);
					}
				}
			}
			*(char*) (*(unsigned char*) p * 0x3dc + 0x1043695) = 0;
		}
	} else {
		if (g_774964 != 0 && (g_774670 <= 0 || g_7e2700 != 0)) {
			mode = fcn_004730c0(0, 0, g_1040494, g_1040490, "BLACK", 0x32, 1);
			while (!(*mode & 4)) {
				fcn_005373e0(0, (g_7e46ac & 0xfffffff7) | 0x80);
			}
			fcn_00473150(mode);
			restore = 0x526bf0;
		}
		v = fcn_00413160();
		if (v == -1) {
			fcn_0041d9e0("init_LoadGebaeudeScene:Could not find a free universe...");
		}
		fcn_004432d0(v, 0);
		fcn_00511040(a0, tmp);
		sprintf(name, "scenes/*gb_%s.ed3", tmp);
		strupr(name);
		sprintf(tmp, "init_LoadGebaeudeScene: %s", name);
		if (fcn_00448360(name, 0, restore)) {
			fcn_004432d0(v, 0);
			if (g_6b8300 != 0) {
				fcn_00516c50(g_6b8300, (void*) 1);
			}
			fcn_004432d0(saved, 0);
			fcn_00437ac0((char*) g_67a370, 0, 0x160, (void (__cdecl*)(char*)) 0x5105a0);
			fcn_00437ac0((char*) g_67a370, 0, 6, (void (__cdecl*)(char*)) 0x510bd0);
			*p = (char) v;
			fcn_004432d0(saved, 0);
			goto label_511541;
		}
	}
	fcn_004432d0(saved, 0);
label_511541:
	if ((g_7747b0 & 8) != 0 && restore != 0) {
		fcn_0042df30((void*) 0x538060, 0);
	}
	return;
}
