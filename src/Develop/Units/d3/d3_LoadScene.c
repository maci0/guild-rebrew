#include "Develop/Units/d3/client_scene_loader.h"
#include "Develop/client_types.h"
#include "Develop/Units/d3/d3_object.h"
#include <string.h>

struct VFS_DIR;

extern struct VFS_DIR* vfs_RootDir;
extern unsigned char g_6b85a4;
extern int d3_SceneRenderLock;
extern VECTOR3 d3_SceneLightingVec;
extern char* d3_ActiveScene;
extern char g_1041d80[];
extern char* g_6b8484;
extern char* d3_CurrentFloor;
extern char* d3_ObjectListHead;
extern char d3_SceneObjectSentinel[];
extern char* d3_InteriorSupermap;
extern int g_6b89b0;

void* __cdecl vfs_Tfopen(const char* name, const char* mode, struct VFS_DIR* root);
int __cdecl CloseVfsStream(void* stream);
int __cdecl vfs_ReadByte(void* stream, void* dst);
char* __cdecl vfs_ReadCString(void* stream, char* dst);
int __cdecl vfs_ReadDword(void* stream, void* dst);
int __cdecl fcn_004011f0(void* stream, void* dst);
void __cdecl vfs_ReadVec3(void* stream, void* dst);
void __cdecl ReportClientMessage(const char* msg);
void __cdecl d3_SetFog(float a, float b, int c);
void __cdecl d3_SetNodePosition(char* object, int* vector);
void __cdecl d3_SetObjectRotation(char* object, int* vector);
char* __cdecl d3_NextVisibleSceneNode(char* object);
void __cdecl d3_DisposeObject(char* object);
void __cdecl d3_RegisterSceneObjectTl(char* object);
void __cdecl d3_SetActiveCamera(char* object);
char* __cdecl d3_CloneObject(char* object);
void __cdecl d3e_ReadSceneEvents(void* stream);
int __cdecl d3_GetSceneVersionSlotCount(unsigned version);
char* __cdecl rd_object(void* stream, char* parent, unsigned int version, unsigned char resources);
char* __cdecl d3_int_io_LoadFloor(void* stream, int version);
void __cdecl d3sm_Rebuild(char* resource, int mode);
char* __cdecl d3sm_CreateMap(int a1, int n, int a3);
void __cdecl gv_Free3Fields(int* slot);
void __cdecl d3_ReloadSceneTextureSurfaces(SCENE_PROGRESS progress);
int __cdecl _strcmpi(const char* a, const char* b);

/* Reader scratch. The reference frame reserves sixteen bytes for it and never
 * touches the fourth float; only x/y/z reach the scene tables. */
typedef struct {
	float x;
	float y;
	float z;
	float w;
} VEC4;

/* ADDRESS: GOLDTL 0x00448360 */
char __cdecl d3_LoadScene(const char* filename, void* stream, SCENE_PROGRESS progress)
{
	char name[256];
	VEC4 vec;
	float discarded;
	float fog_a;
	float fog_b;
	int version;
	int count;
	int index;
	int rows;
	int color;
	int fog_color;
	char* s;
	char* obj;
	char* clone;
	char* universe;
	unsigned char present;

	g_6b85a4 = 0;
	if (stream != 0) {
		s = (char*) stream;
	} else {
		s = (char*) vfs_Tfopen(filename, "rb", vfs_RootDir);
	}
	if (s == 0) {
		return 0;
	}
	fcn_004011f0(s, &version);
	if ((version & 0xffff0000) != 0x3a6c0000 || version < 0x3a6c0001) {
		if (stream == 0) {
			CloseVfsStream(s);
		}
		return 0;
	}
	d3_SceneRenderLock++;
	if (version >= 0x3a6c000b) {
		vfs_ReadCString(s, name);
		vfs_ReadDword(s, &discarded);
		vfs_ReadVec3(s, &vec);
		d3_SceneAmbientColor.x = vec.x;
		d3_SceneAmbientColor.y = vec.y;
		d3_SceneAmbientColor.z = vec.z;
		if (version >= 0x3a6c00b5) {
			vfs_ReadVec3(s, &vec);
			d3_SceneLightingVec.x = vec.x;
			d3_SceneLightingVec.y = vec.y;
			d3_SceneLightingVec.z = vec.z;
		}
		if (version >= 0x3a6c00b3) {
			/* index doubles as the scene value written below, then as the
			 * row counter of the geometry loop. */
			index = 0;
			if (version >= 0x3a6c00b7) {
				fcn_004011f0(s, &index);
			}
			*(int*) (d3_ActiveScene + 0xb4) = index;
			fcn_004011f0(s, &fog_color);
			vfs_ReadDword(s, &fog_a);
			vfs_ReadDword(s, &fog_b);
			d3_SetFog(fog_a, fog_b, fog_color);
		}
		/* The reference writes the row count into index before the loop
		 * and never reads it back. */
		index = 7;
		for (index = 0; index < 7; index++) {
			((D3_SCENE_SLOT*)g_1041d80)[index].a.x = d3_SceneAmbientColor.x;
			((D3_SCENE_SLOT*)g_1041d80)[index].a.y = d3_SceneAmbientColor.y;
			((D3_SCENE_SLOT*)g_1041d80)[index].a.z = d3_SceneAmbientColor.z;
			*(int*)&((D3_SCENE_SLOT*)g_1041d80)[index].b.x = 0;
			*(int*)&((D3_SCENE_SLOT*)g_1041d80)[index].b.y = 0;
			*(int*)&((D3_SCENE_SLOT*)g_1041d80)[index].b.z = 0;
		}
		if (version >= 0x3a6c00a2) {
			rows = d3_GetSceneVersionSlotCount((unsigned) version);
			index = 0;
			if (rows > 0) {
				do {
					vfs_ReadVec3(s, &vec);
					((D3_SCENE_SLOT*)g_1041d80)[index].a.x = vec.x;
					((D3_SCENE_SLOT*)g_1041d80)[index].a.y = vec.y;
					((D3_SCENE_SLOT*)g_1041d80)[index].a.z = vec.z;
					if (version >= 0x3a6c00b3) {
						if (version >= 0x3a6c00b5) {
							vfs_ReadVec3(s, &vec);
							((D3_SCENE_SLOT*)g_1041d80)[index].b.x = vec.x;
							((D3_SCENE_SLOT*)g_1041d80)[index].b.y = vec.y;
							((D3_SCENE_SLOT*)g_1041d80)[index].b.z = vec.z;
						}
						/* count is the per-row entry counter and later the
						 * object count read after the geometry block. */
						count = 0;
						do {
							fcn_004011f0(s, &color);
							vfs_ReadDword(s, &discarded);
							((D3_SCENE_SLOT*)g_1041d80)[index].pal[count].color = color;
							((D3_SCENE_SLOT*)g_1041d80)[index].pal[count].f4 = discarded;
							vfs_ReadDword(s, &discarded);
							((D3_SCENE_SLOT*)g_1041d80)[index].pal[count].f8 = discarded;
							count = count + 1;
						} while (count < 6);
					}
					index = index + 1;
				} while (index < rows);
			}
		}
		if (g_6b8484 != 0) {
			d3_DisposeObject(g_6b8484);
		}
		fcn_004011f0(s, &count);
		index = 0;
		if (count > 0) {
			do {
				rd_object(s, 0, (unsigned) version, 0);
				if (progress != 0) {
					progress(0, index, count);
				}
				index++;
			} while (index < count);
		}
		vfs_ReadByte(s, &present);
		if (present != 0) {
			d3_CurrentFloor = d3_int_io_LoadFloor(s, version);
		}
		obj = d3_ObjectListHead;
		while (obj != d3_SceneObjectSentinel) {
			if (*(int*) (obj + 0x218) == 3 && _strcmpi(name, obj) == 0) {
				g_6b8484 = obj;
				if ((obj[0x214] & 0x40) != 0) {
					d3_SetNodePosition(obj, (int*) (obj + 0x5c));
					d3_SetObjectRotation(obj, (int*) (obj + 0x90));
				}
				d3_SetActiveCamera(obj);
				break;
			}
			obj = *(char**) (obj + 0x1f4);
		}
		if (version >= 0x3a6c00a7) {
			d3e_ReadSceneEvents(s);
		}
	} else {
		ReportClientMessage("Scene too old... Sorry!");
	}
	if (stream == 0) {
		CloseVfsStream(s);
	}
	if (version < 0x3a6c00b1 && d3_CurrentFloor != 0) {
		obj = d3_ObjectListHead;
		while (obj != d3_SceneObjectSentinel) {
			if (*(int*) (obj + 0x218) == 7) {
				clone = d3_CloneObject(obj);
				clone[0x215] |= 4;
				strcat(clone, "boden");
				d3_RegisterSceneObjectTl(clone);
				break;
			}
			obj = d3_NextVisibleSceneNode(obj);
		}
	}
	if (d3_CurrentFloor == 0) {
		if (d3_InteriorSupermap != 0) {
			d3sm_Rebuild(d3_InteriorSupermap, 0);
		} else {
			d3_InteriorSupermap = d3sm_CreateMap(0, -g_6b89b0, 1);
		}
	} else if (d3_InteriorSupermap != 0) {
		gv_Free3Fields((int*) d3_InteriorSupermap);
		d3_InteriorSupermap = 0;
	}
	universe = d3_ActiveScene;
	if (*(int*) (universe + 0xb4) == 0) {
		*(int*) (universe + 0xb4) = d3_CurrentFloor != 0 ? 128 : 64;
		universe = d3_ActiveScene;
	}
	if (d3_CurrentFloor != 0) {
		*(char**) (universe + 0xac) = d3_CurrentFloor;
	}
	d3_ReloadSceneTextureSurfaces(progress);
	d3_SceneRenderLock--;
	if (filename != 0) {
		strncpy(d3_ActiveScene, filename, 0x7f);
	}
	*(unsigned char*) (d3_ActiveScene + 0x3d4) = 1;
	*(int*) (d3_ActiveScene + 0x3d8) = 0;
	return 1;
}
/* Layout scaffolding: shifts the next source object to its reference
 * VA. 0x90 filler, not reconstruction. Generated by the text lead pass. */
#pragma data_seg(".text")

unsigned char _dpad_6b870c[696];
