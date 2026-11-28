#include "scene_event_entry.h"

extern SCENE_EVENT_ENTRY d3_SceneEvents[8];

int __cdecl fcn_0065f220(const char* a, const char* b);

/* ADDRESS: GOLDTL 0x0043b500 */
/* ADDRESS: GOLDDE 0x004342b0 */
int __cdecl d3_FindSceneEventId(const char* name)
{
	unsigned int i;

	for (i = 0; i < 8; i++) {
		if (fcn_0065f220(name, d3_SceneEvents[i].name) == 0) {
			return d3_SceneEvents[i].value;
		}
	}
	return 0;
}
