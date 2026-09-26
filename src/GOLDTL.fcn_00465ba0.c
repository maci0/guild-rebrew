#include <stdio.h>

typedef struct VfsEntry {
	char name[0x30];
	int offset;
	void* data;
	int size;
	int kind;
	int refs;
	int flags;
	int stamp;
	char pad[8];
} VfsEntry;
// SIZE 0x54

extern char* g_772500;
extern signed char g_772510;
extern FILE* g_772564;
extern char g_102d040[];
extern char s_67d410[];
extern char s_6750e8[];

char* __cdecl fcn_0041db70(int size, const char* tag);

// FUNCTION: GOLDTL 0x465ba0
// SIZE: 180
char* __cdecl fcn_00465ba0(int idx, const char* path)
{
	char* buf;

	if (((VfsEntry*)g_772500)[idx].flags & 2) {
		idx += g_772510;
	}
	buf = fcn_0041db70(((VfsEntry*)g_772500)[idx].size, s_67d410);
	if (path) {
		g_772564 = fopen(path, s_6750e8);
	} else {
		g_772564 = fopen(g_102d040, s_6750e8);
	}
	if (g_772564 == 0) {
		return 0;
	}
	fseek(g_772564, ((VfsEntry*)g_772500)[idx].offset, SEEK_SET);
	fread(buf, ((VfsEntry*)g_772500)[idx].size, 1, g_772564);
	fclose(g_772564);
	return buf;
}
