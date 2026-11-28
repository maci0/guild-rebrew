#include <math.h>
#include <string.h>

#include "Develop/DieGildeAddOn/game/game_data.h"
extern char* g_773d78;

void __cdecl d3_SelectSceneContext(int, int);
#include "Develop/DieGildeAddOn/game/client_placement.h"
int __cdecl d3_CollectUnusedSceneObjects(char*, char**);
unsigned short __cdecl gm_RandomMod(int);
void __cdecl d3_TransformPoint(char* src, char* pos, float* out);
float __cdecl gm_RandomFloat01(void);


/* Picks one entity of the list the key resolves to: the one nearest (with a
 * random weight) to the owner's or the player's reference entity, else a
 * random non-empty entry. */
/* ADDRESS: GOLDTL 0x004a48e0 */
char* __cdecl gm_PickRandomOrNearestBuilding(char* u, int key)
{
	char* list[0x100];
	char text[0x40];
	float p1[4];
	float p2[4];
	float dist;
	float d[4];
	float best;
	float score;
	char* ref;
	char* found;
	int saved;
	int n;
	int i;
	int cnt;

	saved = d3_CurrentContextIndex;
	d3_SelectSceneContext(0, 1);
	if (lc_GetBauplatzPrefix(key, text) != 0) {
		memset(list, 0, sizeof(list));
		n = d3_CollectUnusedSceneObjects(text, list);
		if (n != 0) {
			if (*(char**) (u + 0x170) != 0 && *(char**) (*(char**) (u + 0x170) + 0x61) != 0 && gm_RandomMod(3) != 0) {
				ref = *(char**) (*(char**) (u + 0x170) + 0x61);
				d3_TransformPoint(ref, ref + 0x4c, p1);
				found = 0;
				best = 1.00000002e+21f;
				for (i = 0; i < n; i++) {
					if (list[i] != 0) {
						d3_TransformPoint(list[i], list[i] + 0x4c, p2);
						d[0] = p2[0] - p1[0];
						d[1] = p2[1] - p1[1];
						d[2] = p2[2] - p1[2];
						score = (gm_RandomFloat01() * 0.5f + 0.75f) * (dist = (float) sqrt(d[2] * d[2] + d[1] * d[1] + d[0] * d[0]));
						if (score < best) {
							best = score;
							found = list[i];
						}
					}
				}
				d3_SelectSceneContext(saved, 1);
				return found;
			}
			if (g_773d78 != 0 && *(char**) (g_773d78 + 0x61) != 0) {
				ref = *(char**) (g_773d78 + 0x61);
				d3_TransformPoint(ref, ref + 0x4c, p1);
				found = 0;
				best = 1.00000002e+21f;
				for (i = 0; i < n; i++) {
					if (list[i] != 0) {
						d3_TransformPoint(list[i], list[i] + 0x4c, p2);
						d[0] = p2[0] - p1[0];
						d[1] = p2[1] - p1[1];
						d[2] = p2[2] - p1[2];
						score = (gm_RandomFloat01() * 0.5f + 0.75f) * (dist = (float) sqrt(d[2] * d[2] + d[1] * d[1] + d[0] * d[0]));
						if (score < best) {
							best = score;
							found = list[i];
						}
					}
				}
				d3_SelectSceneContext(saved, 1);
				return found;
			}
			cnt = n;
			i = gm_RandomMod(n);
			do {
				if (list[i] != 0) {
					d3_SelectSceneContext(saved, 1);
					return list[i];
				}
				i = (i + 1) % n;
			} while (--cnt != 0);
		}
	}
	d3_SelectSceneContext(saved, 1);
	return 0;
}
