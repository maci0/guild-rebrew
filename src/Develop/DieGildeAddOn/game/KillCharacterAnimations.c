#include "Develop/DieGildeAddOn/game/ch_script.h"
extern char g_6761ec[];



#include "Develop/DieGildeAddOn/game/ch_queue.h"
extern char* evt_CurrentScript;
void __cdecl evt_LogScriptError(void*, int, char*);

int __cdecl KillCharacterAnimations(char** target)
{
	char* p;
	char* q;
	char* e;

	p = *target;
	if (p == 0) {
		evt_LogScriptError(evt_CurrentScript, *(int*) (evt_CurrentScript + 0x118), g_6761ec);
	} else {
		q = *(char**) (p + 0x128);
		if (q != 0) {
			q[0x190] = 1;
			while ((e = *(char**) (q + 0x28)) != 0) {
				ch_RemoveQueueEntry(e);
			}
		}
	}
	return 0;
}
