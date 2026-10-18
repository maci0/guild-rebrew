#ifndef VFS_H
#define VFS_H

#include "../../game_common.h"

/* VFS Functions */
extern int __cdecl CloseVfsStream(void* stream);
extern void* __cdecl vfs_OpenStream(unsigned char* buf, unsigned int size, char* mode_flags);
struct VFS_DIR;
extern void* __cdecl vfs_Tfopen(char* path, char* mode, struct VFS_DIR* root);

/* Low-level Stream Functions */
extern int __cdecl vfs_GetByte(void* stream);

#endif /* VFS_H */
