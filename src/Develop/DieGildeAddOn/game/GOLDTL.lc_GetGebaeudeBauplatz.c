#include "client_placement.h"

extern int g_6b8010;
extern int g_633444;
extern int g_67a370;
extern char s_6aa1b4[];

int __cdecl sprintf(char*, const char*, ...);
#ifdef REBREW_GOLD
void __cdecl fcn_004478e0(int, int);
void __cdecl fcn_00458a10(char*, float*, float*);
char __cdecl fcn_00438d40(char*, char*, unsigned int, char (__cdecl*)(char*, void*), void*);
#define lc_RenderState fcn_004478e0
#define lc_ScenePoint fcn_00458a10
#define lc_WalkScene fcn_00438d40
#define lc_SavedRender g_633444
#else
void __cdecl fcn_004432d0(int, int);
void __cdecl fcn_00455350(char*, float*, float*);
char __cdecl fcn_004379a0(char*, char*, unsigned int, char (__cdecl*)(char*, void*), void*);
#define lc_RenderState fcn_004432d0
#define lc_ScenePoint fcn_00455350
#define lc_WalkScene fcn_004379a0
#define lc_SavedRender g_6b8010
#endif
int __cdecl lc_GetGebaeudeBauplatz(LC_GEBAEUDE_BAUPLATZ* out, unsigned char* obj)
{
	char buf[0x100];
	int old;

	if (*(char**) (obj + 0x61) == 0) {
		return 0;
	}
	old = lc_SavedRender;
	lc_RenderState(0, 1);
	*(int*) out->name = 0;
	if (fcn_00597ff0(obj[0], out->name) == 0) {
		lc_RenderState(old, 1);
		return 0;
	}
	lc_ScenePoint(*(char**) (obj + 0x61), (float*) (*(char**) (obj + 0x61) + 0x4c), out->position);
	sprintf(buf, s_6aa1b4, out->position[0], out->position[1], out->position[2]);
	out->node = 0;
	lc_WalkScene((char*) g_67a370, 0, 0x180, fcn_00598550, out);
	if (out->node == 0) {
		lc_RenderState(old, 1);
		return 0;
	}
	lc_RenderState(old, 1);
	return 1;
}
