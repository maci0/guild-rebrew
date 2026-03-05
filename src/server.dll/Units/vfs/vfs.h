#ifndef VFS_H
#define VFS_H

#include "../../game_common.h"

/* VFS Functions */
extern int __cdecl OpenVfsStream(char* path, int mode);
extern int __cdecl CloseVfsStream(int handle);
extern int __cdecl ReadVfsData(int handle, void* buffer, int size);
extern int __cdecl ReadVfsCompressed(int handle, void* buffer, int size);

/* Low-level Stream Functions */
extern int __cdecl vfs_CloseStream(void* stream);
extern int __cdecl vfs_FlushStream(void* stream);
extern int __cdecl vfs_GetByte(void* stream);

#endif /* VFS_H */
