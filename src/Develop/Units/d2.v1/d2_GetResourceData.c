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

void __cdecl d2_Show(int resource_id, int arg);

/* ADDRESS: GOLDTL 0x00466190 */
void* __cdecl d2_GetResourceData(int resource_id)
{
	int original_resource_id;

	g_772568 = 0;
	if (((VfsEntry*)g_772500)[resource_id].flags & 2) {
		resource_id += g_772510;
	}
	if ((((VfsEntry*)g_772500)[resource_id].kind == 5 || ((VfsEntry*)g_772500)[resource_id].kind == 8) && ((VfsEntry*)g_772500)[resource_id].offset == 0) {
		if (((VfsEntry*)g_772500)[((VfsEntry*)g_772500)[resource_id].link].data == 0) {
			d2_Show(((VfsEntry*)g_772500)[resource_id].link, 0);
		}
		original_resource_id = resource_id;
		resource_id = ((VfsEntry*)g_772500)[resource_id].link;
		g_772568 = original_resource_id - resource_id;
	} else if (((VfsEntry*)g_772500)[resource_id].data == 0) {
		d2_Show(resource_id, 0);
	}
	return ((VfsEntry*)g_772500)[resource_id].data;
}
