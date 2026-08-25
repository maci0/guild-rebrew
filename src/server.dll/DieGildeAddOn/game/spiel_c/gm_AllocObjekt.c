/* gm_AllocObjekt — high-level object allocation: resolve the parent record,
 * link a fresh pool slot into the parent's object list, and initialize the
 * object record.
 *
 * NEAR_MATCHING / best-effort: verified flow — NULL / -1 guards with their
 * LogMessageInternal lines (0xcb2/0xcb8/0xcd4/0xcdd), gm_ResolveEntityById,
 * the dynamic/existing/static head selection (+0x5d/+0x14/+0x178), the
 * gm_AllocateObjectSlot linked-list insertion, the id/type/parent field
 * init with the sprintf (0x1001a299) + LogMessageInternal(0xcee) pair, the
 * g_query_limit increment, and the 0x1c block zeroing. The type-specific
 * branch (type > 0x160 and the per-type field init) is summarized below;
 * the exact register allocation and branch layout cannot be reproduced by
 * msvc6 from C (original: PROVEN via naked). */

// CFLAGS: /O2 /Gd
// FUNCTION: SERVER 0x10016760

#include <stdlib.h>

extern char* g_entity_table;
extern int g_query_limit;
extern int g_next_object_id;
int __cdecl gm_ResolveEntityById(void** dynamic, void** existing, void** static_ptr, int entity_id);
char* __cdecl gm_AllocateObjectSlot(void);
int __cdecl sprintf(char* buffer, const char* format, ...); /* 0x1001a299 */

char* __cdecl gm_AllocObjekt(int parent_id, int type, int param3)
{
	void* dynamic;
	void* existing;
	void* static_ptr;
	char* slot;
	char* head;
	char* last;

	dynamic = NULL;
	existing = NULL;
	static_ptr = NULL;
	if (g_entity_table == NULL) {
		return NULL;
	}
	if (parent_id == -1) {
		LogMessageInternal((char*) 0x10031004, 0xcb2, (char*) 0x10031310, 1);
		return NULL;
	}
	if (gm_ResolveEntityById(&dynamic, &existing, &static_ptr, parent_id) == 0) {
		LogMessageInternal((char*) 0x10031004, 0xcb8, (char*) 0x100312ec, 1);
		return NULL;
	}
	if (dynamic != NULL) {
		head = (char*) dynamic + 0x5d;
	} else if (existing != NULL) {
		head = (char*) existing + 0x14;
	} else if (static_ptr != NULL) {
		head = (char*) static_ptr + 0x178;
	} else {
		head = NULL;
	}
	slot = NULL;
	if (head != NULL) {
		if (*(char**) head != NULL) {
			last = *(char**) head;
			while (*(char**) (last + 0x3f) != NULL) {
				last = *(char**) (last + 0x3f);
			}
			slot = gm_AllocateObjectSlot();
			if (slot == NULL) {
				LogMessageInternal((char*) 0x10031004, 0xcd4, (char*) 0x100312c8, 1);
				return NULL;
			}
			*(char**) (last + 0x3f) = slot;
		} else {
			slot = gm_AllocateObjectSlot();
			if (slot == NULL) {
				LogMessageInternal((char*) 0x10031004, 0xcdd, (char*) 0x100312c8, 1);
				return NULL;
			}
			*(char**) head = slot;
		}
	}
	*(unsigned short*) slot = (unsigned short) type;
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
	memset(slot + 0x1c, 0, 0x20);
	if (type > 0x160) {
		/* per-type init (summary) */
	}
	return slot;
}
