#ifndef VFS_H
#define VFS_H

#include "../../game_common.h"

/* VFS Functions */
extern int __cdecl OpenVfsStream(char* path, char* mode, int param3);
extern int __cdecl CloseVfsStream(int handle);
extern unsigned int __cdecl ReadVfsData(void* outBuffer, int elementSize, int elementCount, void* streamCtx);
extern int __cdecl ReadVfsCompressed(int handle, void* buffer, int size);

/* Low-level Stream Functions */
extern int __cdecl vfs_CloseStream(void* stream);
extern int __cdecl vfs_FlushStream(void* stream);
extern int __cdecl vfs_GetByte(void* stream);

#endif /* VFS_H */
