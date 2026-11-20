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

// SIZE 0x3cc
typedef struct {
	char p0[0xb4];
	int xb4;
	char pb8[0x310];
	int x3c8;
} Cfg;

extern struct VFS_DIR* g_6b7fdc;
extern int g_6b8484;
extern VECTOR3 g_67bbdc;
extern VECTOR3 g_6b86c4;
extern int g_67a370;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern float g_10425fc;
extern float g_104329c;
extern char g_1041d80[];
extern int g_6b8300;

void* __cdecl vfs_Tfopen(const char* name, const char* mode, struct VFS_DIR* root);
void __cdecl fcn_00401360(void*, int);
void __cdecl vfs_WriteCString(void*, int);
void __cdecl fcn_00401260(void*, float);
void __cdecl vfs_WriteVec3(void*, Vec3*);
void __cdecl vfs_WriteByte(void*, char);
void* __cdecl fcn_00437890(void*);
void __cdecl fcn_00446540(void*, void*);
void __cdecl fcn_004469e0(void*, int);
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
		s = vfs_Tfopen(name, "wb", g_6b7fdc);
		if (s == 0) {
			return;
		}
	}
	fcn_00401360(s, 0x3a6c00bb);
	vfs_WriteCString(s, g_6b8484);
	fcn_00401260(s, 0.0f);
	vfs_WriteVec3(s, &g_67bbdc);
	vfs_WriteVec3(s, &g_6b86c4);
	fcn_00401360(s, ((Cfg*)g_67a370)->xb4);
	fcn_00401360(s, d3_FogColor);
	fcn_00401260(s, g_10425fc);
	fcn_00401260(s, g_104329c);
	for (i = 0; i < 7; i++) {
		vfs_WriteVec3(s, (Vec3*)&((D3_SCENE_SLOT*)g_1041d80)[i].a);
		vfs_WriteVec3(s, (Vec3*)&((D3_SCENE_SLOT*)g_1041d80)[i].b);
		for (k = 0; k < 6; k++) {
			fcn_00401360(s, ((D3_SCENE_SLOT*)g_1041d80)[i].pal[k].color);
			fcn_00401260(s, ((D3_SCENE_SLOT*)g_1041d80)[i].pal[k].f4);
			fcn_00401260(s, ((D3_SCENE_SLOT*)g_1041d80)[i].pal[k].f8);
		}
	}
	n = 0;
	for (p = ((void*)d3_ObjectListHead); p != &(*(char*)d3_SceneObjectSentinel); p = fcn_00437890(p)) {
		n++;
	}
	fcn_00401360(s, n);
	for (p = ((void*)d3_ObjectListHead); p != &(*(char*)d3_SceneObjectSentinel); p = fcn_00437890(p)) {
		fcn_00446540(s, p);
	}
	vfs_WriteByte(s, g_6b8300 != 0);
	if (g_6b8300 != 0) {
		fcn_004469e0(s, g_6b8300);
	}
	d3_WriteEventTable(s, ((Cfg*)g_67a370)->x3c8);
	if (stream == 0) {
		CloseVfsStream(s);
	}
}
