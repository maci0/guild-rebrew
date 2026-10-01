extern unsigned char g_slot_table[0x300 * 0x21c];
/* gm_AllocObjekt - high-level object allocation: resolve the parent record,
 * link a fresh pool slot into the parent's object list, initialize the object
 * record, then run the per-type field setup selected by the object prototype.
 *
 * Frame: dynamic/existing/static_ptr/entry occupy [esp+0x10..0x1c], the
 * sprintf scratch buffer is the 0x400 bytes at [esp+0x20].
 * Type dispatch uses two jump tables, at 0x10016b04 (prototypes below 0x160,
 * index map 0x10016b1c) and 0x10016bc4 (above 0x160, index map 0x10016bd0).
 */

// FUNCTION: SERVER 0x10016760

#include <stdlib.h>
#include <string.h>
#include "rebrew_types.h"
#include "rebrew_globals.h"

extern int g_query_limit;      /* 0x10035450 */
extern int g_next_object_id;   /* 0x10030b6c */

int __cdecl LogMessageInternal(char*, int, char*, int);
int __cdecl gm_ResolveEntityById(void** dynamic, void** existing, void** static_ptr, int entity_id);
char* __cdecl gm_AllocateObjectSlot(void);
char* __cdecl gm_ResolveParentEntity(void*);
int __cdecl sprintf(char* buffer, const char* format, ...); /* 0x1001a299 */

char* __cdecl gm_AllocObjekt(int parent_id, int type, int param3)
{
	void* dynamic;
	void* existing;
	void* static_ptr;
	char* entry;
	char buffer[0x400];
	char* slot;
	char* last;
	char* head;
	char* cur;
	char* extra;
	char* child;
	int walk_id;

	last = NULL;
	slot = NULL;
	existing = NULL;
	dynamic = NULL;
	static_ptr = NULL;
	if (g_item_def_table == NULL) {
		return NULL;
	}
	if (parent_id == -1) {
		LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0xcb2, "gm_AllocObjekt(): Versuch Objekt au\337erhalb einer Hirachie zu erzeugen", 1);
		return NULL;
	}
	if (gm_ResolveEntityById(&dynamic, &existing, &static_ptr, parent_id) == 0) {
		LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0xcb8, "gm_AllocObjekt(): Parent not found", 1);
		return NULL;
	}
	if (dynamic != NULL) {
		head = (char*) dynamic + 0x5d;
	} else if (existing != NULL) {
		head = (char*) existing + 0x14;
	} else if (static_ptr != NULL) {
		head = (char*) static_ptr + 0x178;
	} else {
		return NULL;
	}
	if (head != NULL) {
		if (*(char**) head != NULL) {
			cur = *(char**) head;
			while (cur != NULL) {
				last = cur;
				cur = *(char**) (cur + 0x3f);
			}
			slot = gm_AllocateObjectSlot();
			if (slot == NULL) {
				LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0xcd4, "gm_AllocObjekt(): Kein Platz mehr", 1);
				return NULL;
			}
			*(char**) (last + 0x3f) = slot;
		} else {
			slot = gm_AllocateObjectSlot();
			if (slot == NULL) {
				LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0xcdd, "gm_AllocObjekt(): Kein Platz mehr", 1);
				return NULL;
			}
			*(char**) head = slot;
		}
	}

	entry = g_item_def_table + (type << 6) + type;
	*(unsigned short*) slot = (unsigned short) type;
	sprintf(buffer, "----->ObjID= %i ObjProt= %i", g_next_object_id, type & 0xffff);
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0xcee, buffer, 8);
	*(int*) (slot + 2) = g_next_object_id;
	g_next_object_id++;
	if (dynamic != NULL) {
		*(int*) (slot + 0xa) = *(int*) ((char*) dynamic + 1);
	} else if (existing != NULL) {
		*(int*) (slot + 0xa) = *(int*) ((char*) existing + 0xa);
	} else if (static_ptr != NULL) {
		*(int*) (slot + 0xa) = *(int*) ((char*) static_ptr + 4);
	}
	*(int*) (slot + 6) = parent_id;
	*(int*) (slot + 0xe) = param3;
	slot[0x12] = 0x64;
	slot[0x13] = 0;
	*(int*) (slot + 0x14) = 0;
	*(int*) (slot + 0x3f) = 0;
	g_query_limit++;
	extra = slot + 0x1c;
	memset(extra, 0, 0x1f);

	switch (type) {
	case 0x12c:
		*(int*) extra = -1;
		*(int*) (slot + 0x20) = -1;
		*(int*) (slot + 0x24) = -1;
		*(int*) (slot + 0x28) = g_current_year - 1;
		break;
	case 0x12d:
		*(int*) extra = -1;
		*(int*) (slot + 0x20) = -1;
		*(int*) (slot + 0x24) = -1;
		*(int*) (slot + 0x28) = -1;
		break;
	case 0xb8:
		*extra = 6;
		break;
	case 0x134:
	case 0x135:
	case 0x136:
		if (dynamic != NULL) {
			*(int*) (slot + 0xa) = *(int*) ((char*) (g_slot_table + 4)
				+ *(unsigned short*) ((char*) dynamic + 0x27) * 0x21c);
		} else if (existing != NULL) {
			*(int*) (slot + 0xa) = *(int*) (gm_ResolveParentEntity(existing) + 4);
		} else if (static_ptr != NULL) {
			*(int*) (slot + 0xa) = *(int*) ((char*) static_ptr + 4);
		}
		walk_id = parent_id;
		while (gm_ResolveEntityById(&dynamic, &existing, &static_ptr, walk_id) != 0) {
			if (dynamic != NULL) {
				break;
			}
			if (existing != NULL) {
				walk_id = *(int*) ((char*) existing + 6);
			} else if (static_ptr != NULL) {
				LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0xd3d, "gm_AllocObjekt(): Karren in Spieler erzeugt?!?", 1);
			}
		}
		slot[0x28] = 0;
		slot[0x31] = 2;
		if (dynamic != NULL) {
			*(int*) extra = *(int*) ((char*) dynamic + 1);
		} else {
			*(int*) extra = -1;
		}
		child = gm_AllocObjekt(*(int*) (slot + 2), 0x1dd, 1);
		*(int*) (child + 0xe) = (int) *(unsigned short*) slot - 0x133;
		child[0x1c] = (char) (*slot - 0x33);
		break;
	case 0x15e:
	case 0x160:
		*(int*) (slot + 0x20) = 0xf;
		break;
	case 0x174:
	case 0x176:
		*(int*) (slot + 0x20) = 6;
		break;
	case 0x24b:
	case 0x256:
	case 0x266:
		*(int*) extra = 0;
		*(int*) (slot + 0x20) = 0;
		break;
	default:
		break;
	}

	if (*entry == 0x17 || *entry == 0x20 || *entry == 0x25) {
		*(int*) extra = 0;
	}
	return slot;
}
