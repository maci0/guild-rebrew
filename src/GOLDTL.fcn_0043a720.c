#include <string.h>

extern char g_6b5c60;

typedef struct Entry043a720 {
	char name[0x58];
} Entry043a720;

typedef struct List043a720 {
	char pad0[0x74];
	Entry043a720 items[6];
	char pad284[0x2a0 - 0x284];
	unsigned char count;
} List043a720;

typedef struct Ov043a720 {
	char pad0[0xb4];
	char name[0x40];
	char padf4[0x40c - 0xf4];
	List043a720* list;
} Ov043a720;

typedef struct Obj043a720 {
	char pad0[0x1ec];
	Ov043a720* ov;
	char pad1f0[0x1fc - 0x1f0];
	struct Obj043a720* parent;
} Obj043a720;

void __cdecl fcn_004315c0(Obj043a720* o);
void __cdecl fcn_004316c0(Obj043a720* o);

/* ADDRESS: GOLDTL 0x0043a720 */
char __cdecl fcn_0043a720(Obj043a720* o, char* name)
{
	Obj043a720* p;
	List043a720* l;
	int i;
	int n;

	if (o != 0 && name != 0 && o->parent != 0 && o->ov != 0) {
		strcpy(o->ov->name, "");
		p = o->parent;
		if (p->ov != 0) {
			l = p->ov->list;
			if (l != 0) {
				n = l->count;
				for (i = 0; i < n; i++) {
					if (strcmp(l->items[i].name, name) == 0) {
						break;
					}
				}
				if (i < n) {
					strcpy(o->ov->name, name);
					fcn_004315c0(p);
					fcn_004316c0(p);
					return 1;
				}
			}
		}
	}
	return 0;
}
