

#include "Develop/Units/d3/d3_camera.h"
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_67a370;


void __cdecl fcn_00438cb0(char*, char*);

void __cdecl fcn_00439aa0(char* o)
{
	if (*(int*) (o + 0x218) == 3 && d3_ActiveCamera == 0) {
		fcn_00439c60(o);
		fcn_00438cb0(o, o + 0x84);
	}
	if (*(int*) (o + 0x218) != 0) {
		*(char**) (o + 0x1f8) = g_1042538;
		*(char**) (o + 0x1f4) = d3_SceneObjectSentinel;
		*(char**) (g_1042538 + 0x1f4) = o;
		g_1042538 = o;
		o[0x214] |= 3;
	}
	*(int*) (o + 0x20c) = g_67a370;
}
