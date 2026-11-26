#include "Develop/DieGildeAddOn/game/game_data.h"

// SIZE 0x8038
struct s_6b8300 {
	int kind;
	char pad[0x8032];
	unsigned char lo : 2;
	unsigned char mode : 3;
};

extern int g_6b8300;
extern char g_1043370[];
extern char g_699b08;
extern int g_67a370;



void __cdecl d3_SelectSceneContext(int, int);
void __cdecl fcn_004437a0(int);
#include "client_scene_loader.h"
int __cdecl fcn_0045b700(struct s_6b8300*, int, int);
void __cdecl d3_TraverseSceneObjects(int, int, int, void*);
void __cdecl fcn_005224b0(void);
void __cdecl fcn_005224f0(void);

int __cdecl fcn_005222a0(void* stream)
{
	int save;

	d3_SelectSceneContext(1, 0);
	fcn_004437a0(0);
	d3_SelectSceneContext(0, 0);
	d3_LoadScene(0, stream, d2_UpdateSceneLoadProgress);
	d3_SelectSceneContext(1, 0);
	d3_SelectSceneContext(0, 0);
	if (((struct s_6b8300*)g_6b8300)->kind == 0x80) {
		(*(int*)g_1043370) = fcn_0045b700(((struct s_6b8300*)g_6b8300), 0x100, 2);
	} else if (((struct s_6b8300*)g_6b8300)->kind == 0x40) {
		(*(int*)g_1043370) = fcn_0045b700(((struct s_6b8300*)g_6b8300), 0x80, 2);
	} else {
		(*(int*)g_1043370) = fcn_0045b700(((struct s_6b8300*)g_6b8300), 0x100, 2);
	}
	save = d3_CurrentContextIndex;
	d3_SelectSceneContext(0, 0);
	if (((struct s_6b8300*)g_6b8300) != 0) {
		((struct s_6b8300*)g_6b8300)->mode = g_699b08;
	}
	d3_TraverseSceneObjects(g_67a370, 0, 0x1c0, (void*) fcn_005224b0);
	d3_TraverseSceneObjects(g_67a370, 0, 0xc0, (void*) fcn_005224f0);
	d3_SelectSceneContext(save, 0);
	return 1;
}
