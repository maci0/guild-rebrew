#include "Develop/DieGildeAddOn/game/ch_script.h"
extern char* evt_CurrentScript;
extern char g_6761c8[];



void __cdecl evt_LogScriptError(int*, int, char*);
#include "Develop/DieGildeAddOn/game/ch_queue.h"

int __cdecl StopCharacter(void* actorRef)
{
	void* actor;

	actor = *(void**) actorRef;
	if (actor == 0) {
		evt_LogScriptError(((int*)evt_CurrentScript), *(int*) ((char*) ((int*)evt_CurrentScript) + 0x118), g_6761c8);
	} else {
		ch_CancelActionQueue(actor);
	}
	return 0;
}
