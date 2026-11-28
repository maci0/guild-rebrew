


#include <stdio.h>
#include <string.h>

// SIZE 0x18
typedef struct {
	char* name;
	int pad[5];
} DirEntry;

typedef struct {
	char pad[0x100];
	int count;
	DirEntry* items;
} DirList;

// SIZE 0x210
typedef struct {
	char pad[9];
	char name[0x100];
	char path[0x107];
} FileSlot;

typedef struct VFS_DIR VFS_DIR;
extern VFS_DIR* vfs_RootDir;

DirList* __cdecl vfs_FindPathNode(char*, int);

/* ADDRESS: GOLDDE 0x005c0fd0 */
int __cdecl vfs_ListFilesByExtension(char* dir, char* ext, FileSlot* out)
{
	int n;
	int i;
	char buf[0x20];
	DirList* list;
	DirEntry* e;
	char* p;

	list = vfs_FindPathNode(dir, (int) vfs_RootDir);
	if (list == 0) {
		return 0;
	}
	n = 0;
	for (i = 0; i < list->count; i++) {
		e = &list->items[i];
		p = strrchr(e->name, '.');
		if (p != 0) {
			strncpy(buf, p, 0x20);
		}
		if (_strcmpi(buf, ext) == 0) {
			strcpy(out->name, e->name);
			sprintf(out->path, "%s/%s", dir, e->name);
			p = strrchr(out->name, '.');
			if (p != 0) {
				*p = 0;
			}
			n++;
			out++;
		}
	}
	return n;
}
