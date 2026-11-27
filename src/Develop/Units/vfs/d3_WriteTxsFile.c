#include <string.h>

typedef struct
{
	char b[0x40];
} TXS_TILE_NAME;
// SIZE 0x40

extern struct VFS_DIR* g_6b7fdc;

char* __cdecl d3_AppendVfsAssetPath(char* s, char* sub);
char* __cdecl fcn_0064d1a0(char* s, int c);
void* __cdecl vfs_Tfopen(const char* name, const char* mode, struct VFS_DIR* root);
void __cdecl vfs_WriteInt(void* s, int v);
void __cdecl vfs_WriteCString(void* s, TXS_TILE_NAME* t);
#include "Develop/Units/vfs/vfs.h"

/* ADDRESS: GOLDTL 0x0044b200 */
void __cdecl d3_WriteTxsFile(char* o)
{
	char* p;
	char* dot;
	void* f;
	int y;
	int x;
	char buf[0x100];

	if (o == 0 || *(TXS_TILE_NAME**) (o + 0x200) == 0 || *(int*) (o + 0x1e4) <= 0 || *(int*) (o + 0x1e8) <= 0) {
		return;
	}
	p = d3_AppendVfsAssetPath(o, ".BGF");
	if (p == 0) {
		return;
	}
	strcpy(buf, p);
	dot = fcn_0064d1a0(buf, '.');
	if (dot != 0) {
		*dot = 0;
	}
	strcat(buf, ".TXS");
	f = vfs_Tfopen(buf, "wb", g_6b7fdc);
	if (f == 0) {
		return;
	}
	vfs_WriteInt(f, 0x23f209ae);
	vfs_WriteInt(f, *(int*) (o + 0x1e8));
	vfs_WriteInt(f, *(int*) (o + 0x1e4));
	for (y = 0; y < *(int*) (o + 0x1e8); y++) {
		for (x = 0; x < *(int*) (o + 0x1e4); x++) {
			vfs_WriteCString(f, &(*(TXS_TILE_NAME**) (o + 0x200))[*(int*) (o + 0x1e4) * y + x]);
		}
	}
	CloseVfsStream(f);
}
