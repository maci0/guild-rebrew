#include <string.h>

typedef struct
{
	char b[0x40];
} fcn_0044b200_Tile;
// SIZE 0x40

extern struct VFS_DIR* g_6b7fdc;

char* __cdecl fcn_00449ac0(char* s, char* sub);
char* __cdecl fcn_0064d1a0(char* s, int c);
void* __cdecl vfs_Tfopen(const char* name, const char* mode, struct VFS_DIR* root);
void __cdecl fcn_00401360(void* s, int v);
void __cdecl fcn_00401230(void* s, fcn_0044b200_Tile* t);
#include "Develop/Units/vfs/vfs.h"

/* ADDRESS: GOLDTL 0x0044b200 */
void __cdecl fcn_0044b200(char* o)
{
	char* p;
	char* dot;
	void* f;
	int y;
	int x;
	char buf[0x100];

	if (o == 0 || *(fcn_0044b200_Tile**) (o + 0x200) == 0 || *(int*) (o + 0x1e4) <= 0 || *(int*) (o + 0x1e8) <= 0) {
		return;
	}
	p = fcn_00449ac0(o, ".BGF");
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
	fcn_00401360(f, 0x23f209ae);
	fcn_00401360(f, *(int*) (o + 0x1e8));
	fcn_00401360(f, *(int*) (o + 0x1e4));
	for (y = 0; y < *(int*) (o + 0x1e8); y++) {
		for (x = 0; x < *(int*) (o + 0x1e4); x++) {
			fcn_00401230(f, &(*(fcn_0044b200_Tile**) (o + 0x200))[*(int*) (o + 0x1e4) * y + x]);
		}
	}
	CloseVfsStream(f);
}
