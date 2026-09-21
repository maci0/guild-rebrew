#include "../../Units/Error/error.h"
#include "../../Units/m_alloc/m_alloc.h"
#include "zlib.h"

#include <stdio.h>
#include <stdlib.h>

int __cdecl deflate(void*, int);  /* zlib deflate — the original calls it directly */
int __cdecl _crt_locked_call4a(void*, int, int, void*);
unsigned int __cdecl vfs_GetByte(int*);
unsigned int __cdecl vfs_FlushStream(int, int);
void __cdecl vfs_WriteUint32LE(int, unsigned int);
int __cdecl vfs_CloseStream(void*);

int __cdecl vfs_ReadUint32BE(int);
int __cdecl vfs_FlushAndClose(int);

/* Reads a single byte from a VFS stream. Advances the read
 * position and returns the byte value, or error on EOF. */

// FUNCTION: GOLDTL 0x419390
// SIZE: 48
// vfs_WriteUint32LE

void __cdecl fcn_004192b0(int, int, int, int);

void __cdecl vfs_WriteUint32LE(int stream, unsigned int value)
{
	if (value == 0)
		return;
	fcn_004192b0(stream, 0, 0, 0);
	*(unsigned int*) (stream + 0x50) = value;
}

/* Destroys a VFS entity (file/directory node). Frees the
 * entity's name string and the entity struct itself. */

