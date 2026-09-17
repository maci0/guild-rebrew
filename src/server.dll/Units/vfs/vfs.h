#ifndef VFS_H
#define VFS_H

#include "../../game_common.h"

/* VFS Functions */
extern int __cdecl CloseVfsStream(int handle);

/* Low-level Stream Functions */
extern int __cdecl vfs_GetByte(void* stream);

#endif /* VFS_H */
