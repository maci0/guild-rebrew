#include "Develop/Units/d3/d3_object.h"
extern int d3_ActiveScene;
#include "Develop/DieGildeAddOn/game/game_data.h"

#include "Develop/DieGildeAddOn/game/ch_queue.h"
void __cdecl ch_ReleaseMorphAnimation(char*);
int __cdecl d3_GetContextIndex(int);
void __cdecl d3_SelectSceneContext(int, int);

void __cdecl ch_FreeAuxData(char*);
void __cdecl m_FreeTracked(char*);


/* Removes an object from the live-object table and releases its scene
 * nodes. */
/* ADDRESS: GOLDTL 0x004030e0 */
int __cdecl ch_DestroyCharacter(char* obj)
{
	int i = 0;
	int saved;

	if (obj != 0) {
		while (((char**)ch_CharacterSlots)[i] != obj && i < 0x300) {
			i++;
		}
		if (i < 0x300) {
			((char**)ch_CharacterSlots)[i] = 0;
			*(int*) obj = -1;
			ch_ClearActionQueue(obj);
			if (*(int*) (obj + 0x34) != 0) {
				saved = -1;
				ch_ReleaseMorphAnimation(obj);
				if (d3_ActiveScene != *(int*) (obj + 0x88)) {
					saved = d3_CurrentContextIndex;
					d3_SelectSceneContext(d3_GetContextIndex(*(int*) (obj + 0x88)), 1);
				}
				if (*(void (__cdecl**)(char*)) (obj + 0x228) != 0) {
					(*(void (__cdecl**)(char*)) (obj + 0x228))(obj);
				}
				d3_DestroyObject((D3_OBJECT*) (*(void**) (obj + 0x34)));
				*(int*) (obj + 0x34) = 0;
				if (*(void***) (obj + 0x124) != 0 && **(void***) (obj + 0x124) != 0) {
					d3_DestroyObject((D3_OBJECT*) (**(void***) (obj + 0x124)));
				}
				if (*(void**) (obj + 0x22c) != 0) {
					d3_DestroyObject((D3_OBJECT*) (*(void**) (obj + 0x22c)));
				}
				if (saved != -1) {
					d3_SelectSceneContext(saved, 1);
				}
			}
			if (*(int*) (obj + 0x124) != 0) {
				ch_FreeAuxData(obj);
			}
			m_FreeTracked(obj);
			return 1;
		}
	}
	return 0;
}
