extern int d3_ActiveScene;
#include "Develop/DieGildeAddOn/game/game_data.h"

char __cdecl d3_MatchObjectTypeMask(int, unsigned int);


/* Walks a scene subtree and calls cb(node, ctx) for every node whose type
 * matches the flags; stops and returns 0 when cb returns 0. */
/* ADDRESS: GOLDTL 0x004379a0 */
/* ADDRESS: GOLDDE 0x00430bf0 */
char __cdecl d3_VisitSceneObjects(char* scene, char* node, unsigned int flags, char (__cdecl* cb)(char*, void*), void* ctx)
{
	char* n;
	char ok;

	if (flags == 0) {
		return 0;
	}
	if (node != 0) {
		do {
			ok = 1;
			if (d3_MatchObjectTypeMask(*(int*) (node + 0x218), flags)) {
				ok = cb(node, ctx);
				if (!ok) {
					return 0;
				}
			}
			if (*(char**) (node + 0x200) != 0 && (ok & 0x80) == 0) {
				ok = d3_VisitSceneObjects(scene, *(char**) (node + 0x200), flags & ~0x200, cb, ctx);
			}
			if (!ok) {
				return 0;
			}
			if (flags & 0x200) {
				break;
			}
			node = *(char**) (node + 0x1f4);
			if (node == 0) {
				break;
			}
		} while (!(node[0x214] & 1));
	} else {
		if (scene == ((char*)d3_ActiveScene)) {
			*(int*) (scene + 0x80) = (*(int*)&d3_ObjectListHead);
			*(int*) (scene + 0x84) = (*(int*)&g_1042538);
			*(int*) (scene + 0xa4) = (*(int*)&d3_SceneRenderListHead);
			*(int*) (scene + 0xa8) = (*(int*)&g_1040958);
		}
		for (n = *(char**) (scene + 0x80); n != 0 && n != d3_SceneObjectSentinel; n = *(char**) (n + 0x1f4)) {
			if (!d3_VisitSceneObjects(scene, n, flags, cb, ctx)) {
				return 0;
			}
		}
	}
	return 1;
}
