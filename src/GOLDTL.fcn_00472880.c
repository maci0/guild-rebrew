typedef struct VfsEntry {
	char name[0x30];
	int offset;
	void* data;
	int size;
	int kind;
	int refs;
	int flags;
	int stamp;
	int link;
	int pad;
} VfsEntry;
// SIZE 0x54

extern VfsEntry* g_772500;
extern char* g_772524;
extern int g_67d378;
extern int g_67d380;
extern int g_67d384;
extern int g_67d398;
extern int g_1015ea4;

char* __cdecl fcn_00466190(int idx);

// FUNCTION: GOLDTL 0x472880
// SIZE: 115
char* __cdecl fcn_00472880(int idx)
{
	if (g_772500[idx].kind != 7) {
		return 0;
	}
	g_772524 = fcn_00466190(idx);
	g_67d378 = idx;
	g_1015ea4 = *(unsigned short*) (g_772524 + 8);
	if (idx == g_67d398) {
		g_67d380 = 8;
	} else {
		g_67d380 = 4;
		if (idx == g_67d398 + 2) {
			g_67d380 = 8;
		}
	}
	g_67d384 = 2;
	return g_772524;
}
