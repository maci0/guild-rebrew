#include <string.h>
extern int d3_ActiveScene;

void __cdecl d3_VisitSceneObjects(int, char*, int, void*, void*);
int __cdecl d3_MatchSceneObjectCallback(char*, char**);

/* ADDRESS: GOLD 0x004495f0 */
/* ADDRESS: GOLDTL 0x00445560 */
/* ADDRESS: GOLDDE 0x0043d2f0 */
int __cdecl d3_MatchSceneObjectCallback(char* obj, char** state)
{
	char* trimmedName;

	if (state[0] != 0) {
		trimmedName = obj[0] == '!' ? obj + 1 : obj;
		if (state[1] != 0) {
			if (strcmp(trimmedName, state[0]) == 0 && state[1] == obj) {
				state[2] = obj;
			}
		} else if (strcmp(trimmedName, state[0]) == 0) {
			state[2] = obj;
		}
	} else if (state[1] == obj) {
		state[2] = obj;
	}
	return state[2] != obj;
}

/* ADDRESS: GOLDTL 0x00445600 */
/* ADDRESS: GOLDDE 0x0043d390 */
char* __cdecl d3_FindSceneObject(char* rootObj, int flags, char* matchPtr, char* matchName)
{
	char* state[3];
	int saved;

	if (matchPtr == 0 && matchName == 0) {
		return 0;
	}
	state[1] = matchPtr;
	state[0] = matchName;
	state[2] = 0;
	if (rootObj != 0) {
		saved = *(int*) (rootObj + 0x1f4);
		*(int*) (rootObj + 0x1f4) = 0;
	}
	d3_VisitSceneObjects(d3_ActiveScene, rootObj, flags | 0x200, d3_MatchSceneObjectCallback, state);
	if (rootObj != 0) {
		*(int*) (rootObj + 0x1f4) = saved;
	}
	return state[2];
}
