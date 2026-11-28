// SIZE 0xc
#include "Develop/client_types.h"
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

// SIZE 0x3cc
typedef struct {
	char p0[0xb4];
	int xb4;
	char pb8[0x310];
	int x3c8;
} Cfg;

extern struct VFS_DIR* vfs_RootDir;
extern int g_6b8484;
extern VECTOR3 d3_SceneAmbientColor;
extern VECTOR3 d3_SceneLightingVec;
extern int d3_ActiveScene;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern float g_10425fc;
extern float g_104329c;
extern char g_1041d80[];
extern int d3_CurrentFloor;

void* __cdecl vfs_Tfopen(const char* name, const char* mode, struct VFS_DIR* root);
void __cdecl vfs_WriteInt(void*, int);
void __cdecl vfs_WriteCString(void*, int);
void __cdecl vfs_WriteInt32(void*, float);
void __cdecl vfs_WriteVec3(void*, Vec3*);
void __cdecl vfs_WriteByte(void*, char);
void* __cdecl d3_NextVisibleSceneNode(void*);
void __cdecl d3_WriteSceneNodeTree(void*, void*);
void __cdecl d3_SaveFloor(void*, int);
void __cdecl d3_WriteEventTable(void*, int);
#include "Develop/Units/vfs/vfs.h"


/* ADDRESS: GOLDTL 0x00446f70 */
void __cdecl d3_SaveScene(const char* name, void* stream)
{
	void* s;
	void* p;
	int n;
	int i;
	int k;

	s = stream;
	if (s == 0) {
		s = vfs_Tfopen(name, "wb", vfs_RootDir);
		if (s == 0) {
			return;
		}
	}
	vfs_WriteInt(s, 0x3a6c00bb);
	vfs_WriteCString(s, g_6b8484);
	vfs_WriteInt32(s, 0.0f);
	vfs_WriteVec3(s, &d3_SceneAmbientColor);
	vfs_WriteVec3(s, &d3_SceneLightingVec);
	vfs_WriteInt(s, ((Cfg*)d3_ActiveScene)->xb4);
	vfs_WriteInt(s, d3_FogColor);
	vfs_WriteInt32(s, g_10425fc);
	vfs_WriteInt32(s, g_104329c);
	for (i = 0; i < 7; i++) {
		vfs_WriteVec3(s, (Vec3*)&((D3_SCENE_SLOT*)g_1041d80)[i].a);
		vfs_WriteVec3(s, (Vec3*)&((D3_SCENE_SLOT*)g_1041d80)[i].b);
		for (k = 0; k < 6; k++) {
			vfs_WriteInt(s, ((D3_SCENE_SLOT*)g_1041d80)[i].pal[k].color);
			vfs_WriteInt32(s, ((D3_SCENE_SLOT*)g_1041d80)[i].pal[k].f4);
			vfs_WriteInt32(s, ((D3_SCENE_SLOT*)g_1041d80)[i].pal[k].f8);
		}
	}
	n = 0;
	for (p = ((void*)d3_ObjectListHead); p != &(*(char*)d3_SceneObjectSentinel); p = d3_NextVisibleSceneNode(p)) {
		n++;
	}
	vfs_WriteInt(s, n);
	for (p = ((void*)d3_ObjectListHead); p != &(*(char*)d3_SceneObjectSentinel); p = d3_NextVisibleSceneNode(p)) {
		d3_WriteSceneNodeTree(s, p);
	}
	vfs_WriteByte(s, d3_CurrentFloor != 0);
	if (d3_CurrentFloor != 0) {
		d3_SaveFloor(s, d3_CurrentFloor);
	}
	d3_WriteEventTable(s, ((Cfg*)d3_ActiveScene)->x3c8);
	if (stream == 0) {
		CloseVfsStream(s);
	}
}
