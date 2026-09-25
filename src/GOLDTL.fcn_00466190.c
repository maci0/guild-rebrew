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
extern signed char g_772510;
extern int g_772568;

void __cdecl fcn_004659c0(int idx, int arg);

// FUNCTION: GOLD 0x004690a0
// SIZE: 204
// FUNCTION: GOLDTL 0x466190
// SIZE: 204
void* __cdecl fcn_00466190(int idx)
{
	int j;

	g_772568 = 0;
	if (g_772500[idx].flags & 2) {
		idx += g_772510;
	}
	if ((g_772500[idx].kind == 5 || g_772500[idx].kind == 8) && g_772500[idx].offset == 0) {
		if (g_772500[g_772500[idx].link].data == 0) {
			fcn_004659c0(g_772500[idx].link, 0);
		}
		j = idx;
		idx = g_772500[idx].link;
		g_772568 = j - idx;
	} else if (g_772500[idx].data == 0) {
		fcn_004659c0(idx, 0);
	}
	return g_772500[idx].data;
}
