#include "../../Units/Error/error.h"
#include "../../Units/m_alloc/m_alloc.h"
#include "zlib.h"

#include <stdio.h>
#include <stdlib.h>

void __cdecl free(void*);
int __cdecl vfs_CleanupObject(char*);
int __cdecl vfs_DestroyEntity(char*);

// FUNCTION: GOLD 0x00467c10
// SIZE: 64
// FUNCTION: GOLDTL 0x464a30
// SIZE: 64
// FUNCTION: SERVER 0x10008A50

// vfs_DestroyEntity

int __cdecl vfs_DestroyEntity(char* entity)
{
	if (!entity) {
		return -102;
	}
	if (*(int*) (entity + 0x7c)) {
		vfs_CleanupObject(entity);
	}
	fclose((FILE*) *(int*) entity);
	free(entity);
	return 0;
}

/* Reads compressed (zlib) data from a VFS stream. Decompresses
 * into the output buffer up to the requested byte count. */

