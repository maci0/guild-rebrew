// FUNCTION: GOLD 0x005d3500
// FUNCTION: GOLDTL 0x005dfa40

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

extern int g_6b7fdc;

DirList* __cdecl fcn_0042f010(char*, int);

int __cdecl fcn_005dfa40(char* dir, char* ext, FileSlot* out)
{
	int n;
	int i;
	char buf[0x20];
	DirList* list;
	DirEntry* e;
	char* p;

	list = fcn_0042f010(dir, g_6b7fdc);
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
