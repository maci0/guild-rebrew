


#include <stdio.h>

extern char* evt_CurrentScript;
#include "Develop/Units/d3/d3_camera.h"
char* __cdecl d3_FindSceneObjectByName(char* name, int kind);
void __cdecl d3_SetNodePosition(char* h, char* pos);
void __cdecl d3_SetObjectRotation(char* h, char* rot);
void __cdecl evt_LogScriptError(char* g, int h, const char* msg);

/* ADDRESS: GOLD 0x0040ee10 */
/* ADDRESS: GOLDTL 0x0040fd20 */
/* ADDRESS: GOLDDE 0x0040eb20 */
int __cdecl SetCameraToDummy(char** name)
{
	char buf[0x80];
	char* o;

	o = d3_FindSceneObjectByName(*name, 2);
	if (o != 0) {
		d3_SetNodePosition(d3_ActiveCamera, o + 0x5c);
		d3_SetObjectRotation(d3_ActiveCamera, o + 0x90);
		return 0;
	}
	sprintf(buf, "SetCameraToDummy(): Could not find Cameradummy '%s'!", *name);
	evt_LogScriptError(evt_CurrentScript, *(int*) (evt_CurrentScript + 0x118), buf);
	return 0;
}
