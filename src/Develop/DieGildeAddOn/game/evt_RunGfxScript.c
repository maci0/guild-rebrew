extern int evt_GfxScriptStackDepth;
extern char* evt_GfxScriptStack[0x20];
extern char* evt_CurrentScript;
extern int evt_LastGfxScriptId;
extern int evt_ActiveContextId;
#include "Develop/DieGildeAddOn/game/game_data.h"

void __cdecl d3_SelectSceneContext(int, int);
void __cdecl evt_InvokeExternalCommand(char*);
void __cdecl evt_ExecuteStatements(char*);


/* Runs a script until it blocks, with the script pushed as the current one
 * for the duration. */
/* ADDRESS: GOLDTL 0x00429670 */
/* ADDRESS: GOLDDE 0x00424090 */
void __cdecl evt_RunGfxScript(char* s)
{
	int saved;
	char* c;

	saved = -1;
	evt_LastGfxScriptId = -1;
	if (evt_GfxScriptStackDepth < 0x20) {
		evt_GfxScriptStack[evt_GfxScriptStackDepth] = evt_CurrentScript;
		evt_GfxScriptStackDepth++;
	}
	evt_CurrentScript = s;
	if (*(int*) (s + 0x104) == -1 || *(int*) (s + 0x104) == evt_ActiveContextId || *(int*) (s + 0xc8c) != 0 || (s[0x124] & 2) || *(int*) (s + 0x118) == 0) {
		c = *(char**) (s + 0xc94);
		if (c != 0 && *(int*) (c + 0x30) != *(int*) (s + 0x104) && *(int*) (c + 0x2c) != *(int*) (s + 0x104)) {
			if (evt_GfxScriptStackDepth > 0) {
				evt_CurrentScript = evt_GfxScriptStack[--evt_GfxScriptStackDepth];
				evt_GfxScriptStack[evt_GfxScriptStackDepth] = 0;
			}
			return;
		}
		if (*(int*) (s + 0xc8c) != 0 || (s[0x124] & 2)) {
			saved = d3_CurrentContextIndex;
			d3_SelectSceneContext(*(int*) (s + 0xc90), 1);
		}
		if (*(int*) (s + 0xc60) != 0) {
			evt_InvokeExternalCommand(s);
		}
		if (*(int*) (s + 0xc60) == 0) {
			do {
				evt_ExecuteStatements(s);
			} while (*(int*) (s + 0xc84) == 2 && (s[0x124] & 1));
		}
		if (saved != -1) {
			d3_SelectSceneContext(saved, 1);
		}
	}
	if (evt_GfxScriptStackDepth > 0) {
		evt_CurrentScript = evt_GfxScriptStack[--evt_GfxScriptStackDepth];
		evt_GfxScriptStack[evt_GfxScriptStackDepth] = 0;
	}
}
