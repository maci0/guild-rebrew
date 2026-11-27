#include <string.h>

extern char g_6b5c60;

typedef struct D3_ANIM_LIST_ENTRY {
	char name[0x58];
} D3_ANIM_LIST_ENTRY;

typedef struct D3_ANIM_LIST {
	char pad0[0x74];
	D3_ANIM_LIST_ENTRY items[6];
	char pad284[0x2a0 - 0x284];
	unsigned char count;
} D3_ANIM_LIST;

typedef struct D3_ANIM_OV {
	char pad0[0xb4];
	char name[0x40];
	char padf4[0x40c - 0xf4];
	D3_ANIM_LIST* list;
} D3_ANIM_OV;

typedef struct D3_ANIM_OBJ {
	char pad0[0x1ec];
	D3_ANIM_OV* ov;
	char pad1f0[0x1fc - 0x1f0];
	struct D3_ANIM_OBJ* parent;
} D3_ANIM_OBJ;

void __cdecl d3_BindAnimTrackNodes(D3_ANIM_OBJ* o);
void __cdecl d3_UpdateObjectAnimPose(D3_ANIM_OBJ* o);

/* ADDRESS: GOLDTL 0x0043a720 */
char __cdecl d3_StartChildAnimByName(D3_ANIM_OBJ* o, char* name)
{
	D3_ANIM_OBJ* p;
	D3_ANIM_LIST* l;
	int i;

	if (o != 0 && name != 0 && o->parent != 0 && o->ov != 0) {
		o->ov->name[0] = g_6b5c60;
		p = o->parent;
		if (p->ov != 0) {
			l = p->ov->list;
			if (l != 0) {
				for (i = 0; i < l->count; i++) {
					if (strcmp(l->items[i].name, name) == 0) {
						break;
					}
				}
				if (i < l->count) {
					strcpy(o->ov->name, name);
					d3_BindAnimTrackNodes(p);
					d3_UpdateObjectAnimPose(p);
					return 1;
				}
			}
		}
	}
	return 0;
}
