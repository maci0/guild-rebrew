#include <string.h>

extern char* g_6b7e98;
extern float g_662d40[3];

void __cdecl fcn_00425bf0(char*, int, const char*);
void __cdecl fcn_00455350(char*, char*, float*);
#include "Develop/DieGildeAddOn/game/ch_motion.h"
void __cdecl fcn_00455140(char*, float*, float*);
float __cdecl fcn_00451380(float*, float*);
void __cdecl fcn_00438cb0(void*, float*);
void __cdecl fcn_00438b40(void*, float*);

/* ADDRESS: GOLD 0x0040ba90 */
/* ADDRESS: GOLDTL 0x0040c9b0 */

/* CreateCharacterAtDummy(): loads a character at a dummy object, facing
 * along the dummy's forward axis. */
char* __cdecl CreateCharacterAtDummy(char** file, char** dummy, char** name)
{
	char* ch;
	float rot[3];
	float dir[3];
	float pos[4];

	if (*dummy == 0) {
		fcn_00425bf0(g_6b7e98, *(int*) (g_6b7e98 + 0x118), "CreateCharacterAtDummy(): invalid dummy");
		return 0;
	}
	fcn_00455350(*dummy, *dummy + 0x4c, pos);
	ch = fcn_00403b90(*file, pos);
	if (ch != 0) {
		strcpy(ch + 8, *name);
		strcpy(*(char**) (ch + 0x34), *name);
		rot[0] = 0.0f;
		rot[1] = 0.0f;
		rot[2] = 0.0f;
		fcn_00455140(*dummy, g_662d40, dir);
		rot[1] = fcn_00451380(g_662d40, dir);
		fcn_00438cb0(*(void**) (ch + 0x34), rot);
		fcn_00438b40(*(void**) (ch + 0x34), pos);
		*(int*) (ch + 0x30) = *(int*) (g_6b7e98 + 0x104);
	} else {
		fcn_00425bf0(g_6b7e98, *(int*) (g_6b7e98 + 0x118), "CreateCharacterAtDummy(): Could not load character");
	}
	return ch;
}
