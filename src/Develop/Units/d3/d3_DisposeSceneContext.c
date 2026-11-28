#include "Develop/DieGildeAddOn/game/game_data.h"

// SIZE 0x3dc
typedef struct {
	int used;
	char p4[0x344];
	int res;
	char p34c[0x90];
} Slot;

#include "Develop/client_types.h"
extern Slot_1043340 g_1043340[64];
extern int d3_CurrentFloor;
extern int g_6b8484;

void __cdecl d3_ClearSceneState(void);
void __cdecl d3_SelectSceneContext(int, int);
void __cdecl d3_DisposeObject(void*);
void __cdecl d3_FreeMeshObject(void*);
void __cdecl d3_ReleaseRenderDeviceContext(int);
void __cdecl d3_FreeSkyDome(int);
void __cdecl m_FreeTracked(int);


/* ADDRESS: GOLDTL 0x004437a0 */
/* ADDRESS: GOLDDE 0x0043bbf0 */
char __cdecl d3_DisposeSceneContext(int idx)
{
	int prev;
	char ok;

	ok = 0;
	if (idx >= 0 && idx < 0x40) {
		if (idx != d3_CurrentContextIndex) {
			if (((Slot*)g_1043340)[idx].used != 0) {
				prev = d3_CurrentContextIndex;
				d3_SelectSceneContext(idx, 1);
				while (((void*)d3_ObjectListHead) != &(*(char*)d3_SceneObjectSentinel)) {
					d3_DisposeObject(((void*)d3_ObjectListHead));
				}
				while (((void*)d3_SceneRenderListHead) != &(*(char*)g_1040640)) {
					d3_FreeMeshObject(((void*)d3_SceneRenderListHead));
				}
				if (d3_CurrentFloor != 0) {
					d3_ReleaseRenderDeviceContext(d3_CurrentFloor);
					d3_CurrentFloor = 0;
				}
				if (g_6b89c0 != 0) {
					d3_FreeSkyDome(g_6b89c0);
					g_6b89c0 = 0;
				}
				if (((Slot*)g_1043340)[idx].res != 0) {
					m_FreeTracked(((Slot*)g_1043340)[idx].res);
					((Slot*)g_1043340)[idx].res = 0;
				}
				g_6b8058 = 0;
				g_6b8484 = 0;
				if (prev != d3_CurrentContextIndex) {
					d3_SelectSceneContext(prev, 1);
				}
			}
		} else {
			d3_ClearSceneState();
		}
		ok = 1;
	}
	return ok;
}
