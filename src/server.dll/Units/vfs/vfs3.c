#include "../../Units/Error/error.h"
#include "../../Units/m_alloc/m_alloc.h"
#include "zlib.h"

#include <stdio.h>
#include <stdlib.h>

int* __cdecl vfs_GetErrnoPtr(void);
int __cdecl vfs_WriteBufferLocked(void*, int, int, int);
void __cdecl free(void*);
int __cdecl vfs_FreeGameSubobject(void*);
int __cdecl vfs_CleanupSubobject(void*);
int __cdecl vfs_CompressBlock(void*, int);
int __cdecl vfs_LockedFwrite(void*, int, int, void*);
unsigned int __cdecl vfs_GetByte(int*);
unsigned int __cdecl vfs_FlushStream(int, int);
void __cdecl vfs_WriteUint32LE(int, unsigned int);
int __cdecl vfs_CloseStream(void*);
void __cdecl vfs_EntityCleanup(char*);

void __cdecl vfs_StreamClose(int);
extern unsigned int __cdecl crc32(unsigned int crc, unsigned char* buf, unsigned int len);
void __cdecl vfs_FreeSubobj(void*);
int __cdecl vfs_CleanupObject(char*);
int __cdecl vfs_DestroyEntity(char*);
int __cdecl vfs_ReadUint32BE(int);
int __cdecl vfs_FlushAndClose(int);

int __cdecl ReadVfsCompressed(int, int, unsigned int);

/* Reads a single byte from a VFS stream. Advances the read
 * position and returns the byte value, or error on EOF. */

// FUNCTION: SERVER 0x10008A50
// vfs_DestroyEntity

int __cdecl vfs_DestroyEntity(char* entity)
{
	if (!entity) {
		return -102;
	}
	if (*(int*) (entity + 0x7c)) {
		vfs_EntityCleanup(entity);
	}
	vfs_StreamClose(*(int*) entity);
	free(entity);
	return 0;
}

/* Reads compressed (zlib) data from a VFS stream. Decompresses
 * into the output buffer up to the requested byte count. */

