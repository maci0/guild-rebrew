typedef struct
{
	int k;
	int a;
	int b;
} D3_CAM_KEY;
// SIZE 0xc
#include "Develop/Units/d3/d3_object.h"
typedef struct
{
	int pos[3];
	int dir[3];
	D3_CAM_KEY keys[6];
} fcn_00446cd0_Cam;
// SIZE 0x60

extern struct VFS_DIR* g_6b7fdc;
extern char s_6790b0[];
extern int g_6b86d4;
#include "Develop/client_types.h"
extern VECTOR3 g_67bbdc;
extern VECTOR3 g_6b86c4;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern float g_10425fc;
extern float g_104329c;
extern char g_1041d80[];
extern int g_67a370;

void* __cdecl vfs_Tfopen(const char* name, const char* mode, struct VFS_DIR* root);
void __cdecl vfs_WriteInt(void* s, int v);
void __cdecl vfs_WriteInt32(void* s, int v);
void __cdecl vfs_WriteVec3(void* s, int* v);
void __cdecl d3_VisitSceneObjects(int list, int a, int kind, void* fn, void* ctx);
void __cdecl d3_WriteSceneObjectCallback(void);
void __cdecl vfs_WriteByte(void* s, int v);
#include "Develop/Units/vfs/vfs.h"

/* ADDRESS: GOLDTL 0x00446cd0 */
void __cdecl d3_SaveSceneFile(char* name, void* stream)
{
	void* s;
	int i;
	int j;

	s = stream;
	if (s == 0) {
		s = vfs_Tfopen(name, s_6790b0, g_6b7fdc);
		if (s == 0) {
			return;
		}
	}
	g_6b86d4++;
	vfs_WriteInt(s, 0x3a6c00bb);
	vfs_WriteInt32(s, 0);
	vfs_WriteVec3(s, ((int*)&g_67bbdc));
	vfs_WriteVec3(s, ((int*)&g_6b86c4));
	vfs_WriteInt(s, d3_FogColor);
	vfs_WriteInt32(s, (*(int*)&g_10425fc));
	vfs_WriteInt32(s, (*(int*)&g_104329c));
	for (i = 0; i < 7; i++) {
		vfs_WriteVec3(s, (int*)&((D3_SCENE_SLOT*)g_1041d80)[i].a);
		vfs_WriteVec3(s, (int*)&((D3_SCENE_SLOT*)g_1041d80)[i].b);
		for (j = 0; j < 6; j++) {
			vfs_WriteInt(s, ((D3_SCENE_SLOT*)g_1041d80)[i].pal[j].color);
			vfs_WriteInt32(s, *(int*)&((D3_SCENE_SLOT*)g_1041d80)[i].pal[j].f4);
			vfs_WriteInt32(s, *(int*)&((D3_SCENE_SLOT*)g_1041d80)[i].pal[j].f8);
		}
	}
	d3_VisitSceneObjects(g_67a370, 0, 0x18, (void*) d3_WriteSceneObjectCallback, s);
	vfs_WriteByte(s, 0);
	if (stream == 0) {
		CloseVfsStream(s);
	}
	g_6b86d4--;
}
