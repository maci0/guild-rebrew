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

extern char* g_772500;
extern signed char g_772510;
extern int g_772568;

void __cdecl d2_Show(int idx, int arg);

/* ADDRESS: GOLDTL 0x00466260 */
int __cdecl fcn_00466260(int idx, void** out, int* out_idx)
{
	int j;

	g_772568 = 0;
	if (((VfsEntry*)g_772500)[idx].flags & 2) {
		idx += g_772510;
	}
	j = idx;
	if ((((VfsEntry*)g_772500)[idx].kind == 5 || ((VfsEntry*)g_772500)[idx].kind == 8) && ((VfsEntry*)g_772500)[idx].offset == 0) {
		if (((VfsEntry*)g_772500)[((VfsEntry*)g_772500)[idx].link].data == 0) {
			d2_Show(((VfsEntry*)g_772500)[idx].link, 0);
		}
		j = ((VfsEntry*)g_772500)[idx].link;
		g_772568 = idx - j;
	} else if (((VfsEntry*)g_772500)[idx].data == 0) {
		d2_Show(idx, 0);
	}
	*out = ((VfsEntry*)g_772500)[j].data;
	*out_idx = idx;
	return 1;
}
