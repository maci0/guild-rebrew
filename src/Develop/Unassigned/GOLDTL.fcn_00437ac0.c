extern int g_67a370;
#include "Develop/DieGildeAddOn/game/game_data.h"

char __cdecl d3_MatchObjectTypeMask(int, unsigned int);


/* Walks a scene subtree and calls cb for every node whose type matches the
 * flags; flag 0x200 limits the walk to the given node. */
/* ADDRESS: GOLDTL 0x00437ac0 */
char __cdecl d3_TraverseSceneObjects(char* scene, char* node, unsigned int flags, void (__cdecl* cb)(char*))
{
	char* n;

	if (flags == 0) {
		return 0;
	}
	if (node != 0) {
		do {
			if (d3_MatchObjectTypeMask(*(int*) (node + 0x218), flags)) {
				cb(node);
			}
			if (*(char**) (node + 0x200) != 0) {
				d3_TraverseSceneObjects(scene, *(char**) (node + 0x200), flags & ~0x200, cb);
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
		if (scene == ((char*)g_67a370)) {
			*(int*) (scene + 0x80) = (*(int*)&d3_ObjectListHead);
			*(int*) (scene + 0x84) = (*(int*)&g_1042538);
			*(int*) (scene + 0xa4) = (*(int*)&d3_SceneRenderListHead);
			*(int*) (scene + 0xa8) = (*(int*)&g_1040958);
		}
		for (n = *(char**) (scene + 0x80); n != 0 && n != d3_SceneObjectSentinel; n = *(char**) (n + 0x1f4)) {
			d3_TraverseSceneObjects(scene, n, flags, cb);
		}
	}
	return 1;
}
