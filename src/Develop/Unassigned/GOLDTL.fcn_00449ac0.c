


#include <string.h>

#include "Develop/DieGildeAddOn/game/game_data.h"
typedef struct VFS_DIR VFS_DIR;
extern VFS_DIR* g_6b7fdc;
extern char g_6b85c0[];

int __cdecl vfs_ResolvePath(char*, int, int, char*);

void __cdecl d3_AppendVfsAssetPath(char* a, char* b)
{
	char buf[0x100];

	strcpy(buf, "*");
	strcat(buf, a);
	strcat(buf, b);
	vfs_ResolvePath(buf, g_1041d08, (int) g_6b7fdc, g_6b85c0);
}
