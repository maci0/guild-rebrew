// SIZE 0xc
#include "client_types.h"
typedef VECTOR3 Vec3;
#include "Develop/Units/d3/d3_object.h"
// SIZE 0xc
typedef struct {
	int color;
	float f4;
	float f8;
} Pal;

// SIZE 0x60
typedef struct {
	Vec3 a;
	Vec3 b;
	Pal pal[6];
} Slot;

extern struct VFS_DIR* g_6b7fdc;
extern VECTOR3 g_67bbdc;
extern VECTOR3 g_6b86c4;
extern char g_1041d80[];

void* __cdecl vfs_Tfopen(const char* name, const char* mode, struct VFS_DIR* root);
int __cdecl fcn_004011f0(void* stream, void* dst);
int __cdecl fcn_004011d0(void* stream, void* dst);
void __cdecl vfs_ReadVec3(void* stream, void* dst);
int __cdecl vfs_ReadByte(void* stream, void* dst);
int __cdecl d3_GetSceneVersionSlotCount(int);
void __cdecl d3_SetFog(float, float, int);
void __cdecl rd_object(void*, int, int, int);
#include "Develop/Units/vfs/vfs.h"


/* ADDRESS: GOLDTL 0x00446df0 */
void __cdecl d3_LoadSceneHeaderAndObjects(const char* name, void* stream)
{
	void* s;
	int ver;
	float f;
	float g;
	int color;
	int col;
	int n;
	int i;
	int k;
	char more;

	if (stream != 0) {
		s = stream;
	} else {
		s = vfs_Tfopen(name, "rb", g_6b7fdc);
	}
	if (s == 0) {
		return;
	}
	fcn_004011f0(s, &ver);
	if ((ver & 0xffff0000) == 0x3a6c0000 && ver >= 0x3a6c00b9) {
		n = d3_GetSceneVersionSlotCount(ver);
		fcn_004011d0(s, &f);
		vfs_ReadVec3(s, &g_67bbdc);
		vfs_ReadVec3(s, &g_6b86c4);
		fcn_004011f0(s, &color);
		fcn_004011d0(s, &f);
		fcn_004011d0(s, &g);
		d3_SetFog(f, g, color);
		for (i = 0; i < n; i++) {
			vfs_ReadVec3(s, &((D3_SCENE_SLOT*)g_1041d80)[i].a);
			vfs_ReadVec3(s, &((D3_SCENE_SLOT*)g_1041d80)[i].b);
			for (k = 0; k < 6; k++) {
				fcn_004011f0(s, &col);
				((D3_SCENE_SLOT*)g_1041d80)[i].pal[k].color = col;
				fcn_004011d0(s, &((D3_SCENE_SLOT*)g_1041d80)[i].pal[k].f4);
				fcn_004011d0(s, &((D3_SCENE_SLOT*)g_1041d80)[i].pal[k].f8);
			}
		}
		vfs_ReadByte(s, &more);
		while (more) {
			rd_object(s, 0, ver, 0);
			vfs_ReadByte(s, &more);
		}
	}
	if (stream == 0) {
		CloseVfsStream(s);
	}
}
