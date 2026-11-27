


#include <string.h>

extern int g_10405cc;
typedef struct VFS_DIR VFS_DIR;
extern VFS_DIR* g_6b7fdc;
extern char g_6b89f0[];

int __cdecl vfs_ResolvePath(char*, int, int, char*);

void __cdecl d3_ResolveTexturePath(char* name)
{
	char buf[0x100];

	strcpy(buf, "*");
	strcat(buf, name);
	strcat(buf, ".BMP");
	vfs_ResolvePath(buf, g_10405cc, (int) g_6b7fdc, g_6b89f0);
}
