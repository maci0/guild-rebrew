#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct VfsEntry {
	char name[0x30];
	int offset;
	void* data;
	int size;
	int kind;
	int refs;
	unsigned char flags;
	char pad45[3];
	int stamp;
	int parent;
	short w50;
	short w52;
} VfsEntry;
// SIZE 0x54

extern char* d2_FileObjTable;
extern int g_772504;
extern int g_67d8c8;

int __cdecl d2_GetResourceKind(char* p);
int __cdecl d2_GetBankEntry(char* p, int i);
int __cdecl d2_Show(int idx, char* path);

/* Loads one entry from the named resource file into the shared entry table,
 * appending one sub-entry per sub-resource for the multi-part kinds. */
/* ADDRESS: GOLDTL 0x00473400 */
int __cdecl d2_LoadResourceFile(char* path, char* name)
{
	int size;
	FILE* f;
	char* buf;
	int index;
	int save;
	int i;

	f = fopen(path, (char*) 0x6750e8);
	fseek(f, 0, 2);
	size = ftell(f);
	buf = (char*) malloc(size);
	fseek(f, 0, 0);
	fread(buf, size, 1, f);
	save = index = g_772504;
	((VfsEntry*) d2_FileObjTable)[index].kind = d2_GetResourceKind(buf) & 0xff;
	i = ((VfsEntry*) d2_FileObjTable)[index].kind;
	if (i == 1 || i == 5 || i == 4 || i == 8) {
		char* p;
		p = (char*) d2_GetBankEntry(buf, 0);
		((VfsEntry*) d2_FileObjTable)[index].w50 = *(short*) (p + 2);
		((VfsEntry*) d2_FileObjTable)[index].w52 = *(short*) (p + 6);
		((VfsEntry*) d2_FileObjTable)[index].parent = index;
	}
	if (i == 0x11) {
		((VfsEntry*) d2_FileObjTable)[index].w50 = *(short*) (buf + 0xc);
		((VfsEntry*) d2_FileObjTable)[index].w52 = *(short*) (buf + 0xe);
	}
	((VfsEntry*) d2_FileObjTable)[index].size = size;
	strcpy(((VfsEntry*) d2_FileObjTable)[index].name, name);
	((VfsEntry*) d2_FileObjTable)[index].flags |= 1;
	((VfsEntry*) d2_FileObjTable)[index].flags &= 0xfd;
	i = ((VfsEntry*) d2_FileObjTable)[index].kind;
	if (i == 5 || i == 8) {
		for (i = 0; i < (int) *(unsigned short*) (buf + 4) - 1; ) {
			char* p;
			index++;
			i++;
			((VfsEntry*) d2_FileObjTable)[index].offset = 0;
			*(int*) ((VfsEntry*) d2_FileObjTable)[index].name = g_67d8c8;
			p = (char*) d2_GetBankEntry(buf, i);
			((VfsEntry*) d2_FileObjTable)[index].w50 = *(short*) (p + 2);
			((VfsEntry*) d2_FileObjTable)[index].w52 = *(short*) (p + 6);
			((VfsEntry*) d2_FileObjTable)[index].kind = ((VfsEntry*) d2_FileObjTable)[save].kind;
			((VfsEntry*) d2_FileObjTable)[index].parent = save;
		}
	}
	free(buf);
	fclose(f);
	g_772504 = index;
	return d2_Show(save, path);
}
unsigned char _dpad_770ae8[6680];
#if defined(REBREW_SERVER) || defined(REBREW_GOLD)
unsigned char _dpad_6b89e4[4];
#endif
