#include "../../Units/Error/error.h"
#include "../../Units/m_alloc/m_alloc.h"
#include "zlib.h"

#include <stdio.h>
#include <stdlib.h>

void __cdecl free(void*);
int __cdecl vfs_CleanupObject(char*);
int __cdecl vfs_DestroyEntity(char*);

/* Reads a single byte from a VFS stream. Advances the read
 * position and returns the byte value, or error on EOF. */

// FUNCTION: GOLDTL 0x464a30
// SIZE: 64
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

