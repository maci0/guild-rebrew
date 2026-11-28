#include "Develop/Units/d3/client_scene_loader.h"
#include "Develop/client_types.h"
#include <string.h>
extern void* vfs_RootDir;
extern unsigned char g_6339e4;
extern int d3_SceneRenderLock;
extern char* d3_ActiveScene;
extern char g_1041d80[];
extern char* g_6338c4;
extern char* d3_CurrentFloor;
extern char* g_fc52f0;
extern char d3_SceneRootSentinel[];
void* __cdecl vfs_Tfopen(const char*, const char*, void*);
int __cdecl CloseVfsStream(void*);
int __cdecl vfs_ReadByte(void*, void*);
void __cdecl vfs_ReadCString(void*, char*);
int __cdecl vfs_ReadDword(void*, void*);
void __cdecl vfs_ReadVec3(void*, void*);
void __cdecl ReportClientMessage(const char*);
void __cdecl fcn_0043a6f0(float, float, int);
void __cdecl d3_SetNodePosition(char*, int*);
void __cdecl d3_SetObjectRotation(char*, int*);
void __cdecl d3_SetActiveCamera(char*);
void __cdecl d3_DisposeObject(char*);
char* __cdecl fcn_0044abb0(void*, char*, unsigned int, unsigned char);
int __cdecl d3_GetScenePresetCount(unsigned int);
char* __cdecl d3_int_io_LoadFloor(void*, int);
void __cdecl d3e_ReadSceneEvents(void*);
char* __cdecl d3_GetNextSceneNode(char*);
char* __cdecl d3_DuplicateObject(char*);
void __cdecl d3_RegisterSceneObject(char*);
void __cdecl d3sm_Build(char*, int);
char* __cdecl d3sm_Create(int, int, int);
void __cdecl d3sm_Destroy(char*);

/* Reader scratch. The reference frame reserves sixteen bytes for it and never
 * touches the fourth float; only x/y/z reach the scene tables. */
typedef struct {
	float x;
	float y;
	float z;
	float w;
} VEC4;

/* ADDRESS: GOLD 0x0044be60 */
char __cdecl d3_LoadSceneStream(const char* filename, void* stream, SCENE_PROGRESS progress)
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

	g_6339e4 = 0;
	if (stream != 0) {
		s = (char*) stream;
	} else {
		s = (char*) vfs_Tfopen(filename, "rb", vfs_RootDir);
	}
	if (s == 0) {
		return 0;
	}
	vfs_ReadDword(s, &version);
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
		*(float*) 0x5fcc74 = discarded;
		d3_SceneAmbientColor.x = vec.x;
		d3_SceneAmbientColor.y = vec.y;
		d3_SceneAmbientColor.z = vec.z;
		if (version >= 0x3a6c00b5) {
			vfs_ReadVec3(s, &vec);
			(*(float*) 0x633b1c) = vec.x;
			(*(float*) 0x633b20) = vec.y;
			(*(float*) 0x633b24) = vec.z;
		}
		if (version >= 0x3a6c00b3) {
			/* index doubles as the scene value written below, then as the
			 * row counter of the geometry loop. */
			index = 0;
			if (version >= 0x3a6c00b7) {
				vfs_ReadDword(s, &index);
			}
			*(int*) (d3_ActiveScene + 0xb4) = index;
			vfs_ReadDword(s, &fog_color);
			vfs_ReadDword(s, &fog_a);
			vfs_ReadDword(s, &fog_b);
			fcn_0043a6f0(fog_a, fog_b, fog_color);
		}
		/* The reference writes the row count into index before the loop
		 * and never reads it back. */
		index = 7;
		for (index = 0; index < 7; index++) {
			*(float*) (g_1041d80 + index * 0x60) = d3_SceneAmbientColor.x;
			*(float*) (g_1041d80 + index * 0x60 + 4) = d3_SceneAmbientColor.y;
			*(float*) (g_1041d80 + index * 0x60 + 8) = d3_SceneAmbientColor.z;
			*(int*) (g_1041d80 + index * 0x60 + 0xc) = 0;
			*(int*) (g_1041d80 + index * 0x60 + 0x10) = 0;
			*(int*) (g_1041d80 + index * 0x60 + 0x14) = 0;
		}
		if (version >= 0x3a6c00a2) {
			rows = d3_GetScenePresetCount((unsigned) version);
			index = 0;
			if (rows > 0) {
				do {
					vfs_ReadVec3(s, &vec);
					*(float*) (g_1041d80 + index * 0x60) = vec.x;
					*(float*) (g_1041d80 + index * 0x60 + 4) = vec.y;
					*(float*) (g_1041d80 + index * 0x60 + 8) = vec.z;
					if (version >= 0x3a6c00b3) {
						if (version >= 0x3a6c00b5) {
							vfs_ReadVec3(s, &vec);
							*(float*) (g_1041d80 + index * 0x60 + 0xc) = vec.x;
							*(float*) (g_1041d80 + index * 0x60 + 0x10) = vec.y;
							*(float*) (g_1041d80 + index * 0x60 + 0x14) = vec.z;
						}
						/* count is the per-row entry counter and later the
						 * object count read after the geometry block. */
						count = 0;
						do {
							vfs_ReadDword(s, &color);
							vfs_ReadDword(s, &discarded);
							*(int*) (g_1041d80 + 0x18 + (count + index * 8) * 12) = color;
							*(float*) (g_1041d80 + 0x1c + (count + index * 8) * 12) = discarded;
							vfs_ReadDword(s, &discarded);
							*(float*) (g_1041d80 + 0x20 + (count + index * 8) * 12) = discarded;
							count = count + 1;
						} while (count < 6);
					}
					index = index + 1;
				} while (index < rows);
			}
		}
		if (g_6338c4 != 0) {
			d3_DisposeObject(g_6338c4);
		}
		vfs_ReadDword(s, &count);
		index = 0;
		if (count > 0) {
			do {
				fcn_0044abb0(s, 0, (unsigned) version, 0);
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
		obj = g_fc52f0;
		while (obj != d3_SceneRootSentinel) {
			if (*(int*) (obj + 0x218) == 3 && _strcmpi(name, obj) == 0) {
				g_6338c4 = obj;
				if ((obj[0x211] & 1) != 0) {
					d3_SetNodePosition(obj, (int*) (obj + 0x5c));
					d3_SetObjectRotation(obj, (int*) (obj + 0x90));
				}
				d3_SetActiveCamera(obj);
				break;
			}
			obj = *(char**) (obj + 0x1f0);
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
		obj = g_fc52f0;
		while (obj != d3_SceneRootSentinel) {
			if (*(int*) (obj + 0x218) == 7) {
				clone = d3_DuplicateObject(obj);
				clone[0x211] |= 0x10;
				strcat(clone, "boden");
				d3_RegisterSceneObject(clone);
				break;
			}
			obj = d3_GetNextSceneNode(obj);
		}
	}
	if (d3_CurrentFloor == 0) {
		clone = *(char**) 0x633df8;
		if (clone != 0) {
			d3sm_Build(clone, 0);
		} else {
			(*(char**) 0x633df8) = d3sm_Create(0, -(*(int*) 0x633dcc), 1);
		}
	} else {
		clone = *(char**) 0x633df8;
		if (clone != 0) {
			d3sm_Destroy(clone);
			(*(char**) 0x633df8) = 0;
		}
	}
	universe = d3_ActiveScene;
	if (*(int*) (universe + 0xb4) == 0) {
		*(int*) (universe + 0xb4) = d3_CurrentFloor != 0 ? 128 : 64;
		universe = d3_ActiveScene;
	}
	if (d3_CurrentFloor != 0) {
		*(char**) (universe + 0xac) = d3_CurrentFloor;
	}
	d3_ReloadAllTextures(0, progress);
	d3_SceneRenderLock--;
	if (filename != 0) {
		strncpy(d3_ActiveScene, filename, 0x7f);
	}
	*(unsigned char*) (d3_ActiveScene + 0x3d4) = 1;
	*(int*) (d3_ActiveScene + 0x3d8) = 0;
	return 1;
}
