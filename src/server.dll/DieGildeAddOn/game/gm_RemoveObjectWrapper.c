/* gm_RemoveObjectWrapper / gm_RemoveEntityLink.  Split out of spiel62.c:
 * the reference places gm_InitEntityIfValid (0x10017f90) between these
 * two and gm_KillSpieler (0x10017fb0), and order-sources orders whole
 * objects by their first VA, so they cannot share spiel62.c's object.
 * Prelude shared verbatim with spiel62.c. */

#include "../../Units/Error/error.h"
#include "../../Units/m_alloc/m_alloc.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "rebrew_types.h"
#include "rebrew_globals.h"

#pragma intrinsic(memcpy, memset)

int __cdecl gm_EntityAccumulate(void*);
int __cdecl gm_RemoveLinkedNodeById(int*, int);

// FUNCTION: SERVER 0x10017f30
// gm_RemoveObjectWrapper

int __cdecl gm_RemoveObjectWrapper(int entity_record, unsigned int obj_type)
{
	int remove_result;

	remove_result = gm_RemoveObjectByType((void**) (entity_record + 0x5d), obj_type);
	if (remove_result == -2) {
		return -3;
	}
	return 0;
}

/* Removes a link from an entity. Clears a specific entity
 * reference field, breaking the association. */

// FUNCTION: SERVER 0x10017f60
// gm_RemoveEntityLink

void __cdecl gm_RemoveEntityLink(int entity)
{
	int parent_entity;

	parent_entity = (int) gm_EntityAccumulate((void*) entity);
	if (parent_entity != 0) {
		gm_RemoveLinkedNodeById((int*) (parent_entity + 0x5d), *(int*) (entity + 2));
	}
}
