#include "Develop/DieGildeAddOn/game/ch_script.h"
#include <string.h>

extern char* evt_CurrentScript;
extern float g_662d40[3];

void __cdecl evt_LogScriptError(char*, int, const char*);
void __cdecl d3_TransformPoint(char*, char*, float*);
#include "Develop/DieGildeAddOn/game/ch_motion.h"
void __cdecl fcn_00455140(char*, float*, float*);
float __cdecl fcn_00451380(float*, float*);
void __cdecl d3_SetObjectRotation(void*, float*);
void __cdecl fcn_00438b40(void*, float*);


/* CreateCharacterAtDummy(): loads a character at a dummy object, facing
 * along the dummy's forward axis. */
/* ADDRESS: GOLDTL 0x0040c9b0 */
char* __cdecl CreateCharacterAtDummy(char** file, char** dummy, char** name)
{
	char* ch;
	float rot[3];
	float dir[3];
	float pos[4];

	if (*dummy == 0) {
		evt_LogScriptError(evt_CurrentScript, *(int*) (evt_CurrentScript + 0x118), "CreateCharacterAtDummy(): invalid dummy");
		return 0;
	}
	d3_TransformPoint(*dummy, *dummy + 0x4c, pos);
	ch = ch_CreateAtPosition(*file, pos);
	if (ch != 0) {
		strcpy(ch + 8, *name);
		strcpy(*(char**) (ch + 0x34), *name);
		rot[0] = 0.0f;
		rot[1] = 0.0f;
		rot[2] = 0.0f;
		fcn_00455140(*dummy, g_662d40, dir);
		rot[1] = fcn_00451380(g_662d40, dir);
		d3_SetObjectRotation(*(void**) (ch + 0x34), rot);
		fcn_00438b40(*(void**) (ch + 0x34), pos);
		*(int*) (ch + 0x30) = *(int*) (evt_CurrentScript + 0x104);
	} else {
		evt_LogScriptError(evt_CurrentScript, *(int*) (evt_CurrentScript + 0x118), "CreateCharacterAtDummy(): Could not load character");
	}
	return ch;
}
