#include "Develop/Units/d3/d3_object.h"
#include "Develop/Units/d3/d3_camera.h"

extern int g_67a370;
void __cdecl fcn_00438cb0(char* object, int* vector);

/* ADDRESS: GOLD 0x0043ca20 */
void __cdecl fcn_0043ca20(char* object)
{
	if (*(int*) (object + 0x218) == 3 && g_6b8014 == 0) {
		fcn_00439c60(object);
		fcn_00438cb0(object, (int*) (object + 0x84));
	}
	if (*(int*) (object + 0x218) != 0) {
		*(char**) (object + 0x1f4) = g_fc28f4;
		*(char**) (object + 0x1f0) = g_fc2700;
		*(char**) (g_fc28f4 + 0x1f0) = object;
		g_fc28f4 = object;
		object[0x210] |= 3;
		*(int*) (object + 0x208) = g_67a370;
		return;
	}
	*(int*) (object + 0x208) = g_67a370;
}
