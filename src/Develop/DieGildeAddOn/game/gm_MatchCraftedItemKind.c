#pragma pack(push, 1)
typedef struct {
	unsigned char kind;
	char pad[0x40];
} GM_OBJ_PROTOTYPE_KIND_VIEW;
#pragma pack(pop)
// SIZE 0x41
#include "Develop/DieGildeAddOn/game/object_prototype.h"
extern char* lpObjektePROT;

/* ADDRESS: GOLDTL 0x005013c0 */
int __cdecl gm_MatchCraftedItemKind(unsigned short* id)
{
	int t[16] = { 1, 3, 4, 0xb, 0xd, 0xe, 0x12, 0x13, 0x15, 0x16, 0x1a, 0x1b, 0x1c, 0x1f, 0x21, 0 };
	OBJECT_PROTOTYPE* o;
	int i;

	i = 0;
	o = &((OBJECT_PROTOTYPE*)lpObjektePROT)[*id];
	while (t[i] != 0) {
		if (o->kind == t[i]) {
			return t[i];
		}
		i++;
	}
	return 0;
}
