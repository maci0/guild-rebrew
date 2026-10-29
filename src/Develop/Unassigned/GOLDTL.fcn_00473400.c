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

extern char* g_772500;
extern int g_772504;
extern int g_67d8c8;

int __cdecl fcn_00473360(char* p);
int __cdecl fcn_0047b620(char* p, int i);
int __cdecl d2_Show(int idx, char* path);

/* Loads one entry from the named resource file into the shared entry table,
 * appending one sub-entry per sub-resource for the multi-part kinds. */
/* ADDRESS: GOLDTL 0x00473400 */
int __cdecl fcn_00473400(char* path, char* name)
{
	int size;
	FILE* f;
	char* buf;
	char* p;
	int kind;
	int index;
	int save;
	int i;

	f = fopen(path, (char*) 0x6750e8);
	fseek(f, 0, 2);
	size = ftell(f);
	buf = (char*) malloc(size);
	fseek(f, 0, 0);
	fread(buf, size, 1, f);
	index = g_772504;
	((VfsEntry*) g_772500)[index].kind = fcn_00473360(buf) & 0xff;
	kind = ((VfsEntry*) g_772500)[index].kind;
	if (kind == 1 || kind == 5 || kind == 4 || kind == 8) {
		p = (char*) fcn_0047b620(buf, 0);
		((VfsEntry*) g_772500)[index].w50 = *(short*) (p + 2);
		((VfsEntry*) g_772500)[index].w52 = *(short*) (p + 6);
		((VfsEntry*) g_772500)[index].parent = index;
	}
	if (kind == 0x11) {
		((VfsEntry*) g_772500)[index].w50 = *(short*) (buf + 0xc);
		((VfsEntry*) g_772500)[index].w52 = *(short*) (buf + 0xe);
	}
	((VfsEntry*) g_772500)[index].size = size;
	strcpy(((VfsEntry*) g_772500)[index].name, name);
	((VfsEntry*) g_772500)[index].flags |= 1;
	((VfsEntry*) g_772500)[index].flags &= 0xfd;
	save = index;
	if (kind == 5 || kind == 8) {
		for (i = 1; i < *(unsigned short*) (buf + 4) - 1; i++) {
			index++;
			((VfsEntry*) g_772500)[index].offset = 0;
			*(int*) ((VfsEntry*) g_772500)[index].name = g_67d8c8;
			p = (char*) fcn_0047b620(buf, i);
			((VfsEntry*) g_772500)[index].w50 = *(short*) (p + 2);
			((VfsEntry*) g_772500)[index].w52 = *(short*) (p + 6);
			((VfsEntry*) g_772500)[index].kind = ((VfsEntry*) g_772500)[save].kind;
			((VfsEntry*) g_772500)[index].parent = save;
		}
	}
	free(buf);
	fclose(f);
	g_772504 = index;
	return d2_Show(save, path);
}
unsigned char _dpad_770ae8[6680];
unsigned char _dpad_6b89e4[760604];
