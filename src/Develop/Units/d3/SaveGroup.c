typedef struct {
	char pad_000[0x1fc];
	void* kinder;
} ITEM_448a00;

struct VFS_DIR;

extern struct VFS_DIR* g_6b7fdc;
extern char s_6790b0[];

void* __cdecl vfs_Tfopen(void*, char*, struct VFS_DIR*);
int __cdecl CloseVfsStream(void*);
void __cdecl vfs_WriteInt(int, int);
void __cdecl d3_WriteSceneNodeTree(int, ITEM_448a00*);
void __cdecl ReportClientMessage(const char*);
void __cdecl d3_AttachSceneNode(ITEM_448a00*, ITEM_448a00*);
void __cdecl d3_UnlinkObject(ITEM_448a00*);

/* ADDRESS: GOLDTL 0x00448a00 */
void __cdecl SaveGroup(void* name, int count, ITEM_448a00** list)
{
	void* cont;
	ITEM_448a00* p;
	int i;
	char found;
	void* kinder;

	if (count <= 0)
		return;
	found = 0;
	for (i = 0; i < count; i++) {
		p = list[i];
		if (found != 0) {
			if (kinder != p->kinder) {
				ReportClientMessage((char*) 0x67ac48);
				return;
			}
		} else {
			kinder = p->kinder;
			found = 1;
		}
	}
	if (kinder == 0) {
		cont = vfs_Tfopen(name, s_6790b0, g_6b7fdc);
		vfs_WriteInt((int) cont, 0x3a6c00bb);
		vfs_WriteInt((int) cont, count);
		for (i = 0; i < count; i++)
			d3_WriteSceneNodeTree((int) cont, list[i]);
		CloseVfsStream(cont);
		return;
	}
	for (i = 0; i < count; i++) {
		d3_UnlinkObject(list[i]);
		d3_AttachSceneNode((ITEM_448a00*) kinder, list[i]);
	}
	cont = vfs_Tfopen(name, s_6790b0, g_6b7fdc);
	vfs_WriteInt((int) cont, 0x3a6c00bb);
	vfs_WriteInt((int) cont, 1);
	d3_WriteSceneNodeTree((int) cont, list[0]);
	CloseVfsStream(cont);
}
