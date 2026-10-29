#include "client_scene_loader.h"
#include "client_types.h"

#include <string.h>

struct VFS_DIR;

extern struct VFS_DIR* g_6b7fdc;
extern unsigned char g_6b85a4;
extern int g_6b86d4;
extern VECTOR3 g_6b86c4;
extern char* g_67a370;
extern char g_1041d80[];
extern char* g_6b8484;
extern char* g_6b8300;
extern char* g_1043254;
extern char g_1042340[];
extern char* g_6b89e4;
extern int g_6b89b0;

void* __cdecl vfs_Tfopen(const char* name, const char* mode, struct VFS_DIR* root);
int __cdecl CloseVfsStream(void* stream);
int __cdecl fcn_00401180(void* stream, void* dst);
char* __cdecl fcn_004011a0(void* stream, char* dst);
int __cdecl fcn_004011d0(void* stream, void* dst);
int __cdecl fcn_004011f0(void* stream, void* dst);
void __cdecl fcn_00401280(void* stream, void* dst);
void __cdecl fcn_0041d9e0(const char* msg);
void __cdecl fcn_00438920(float a, float b, int c);
void __cdecl fcn_00438b40(char* object, int* vector);
void __cdecl fcn_00438cb0(char* object, int* vector);
char* __cdecl fcn_00437890(char* object);
void __cdecl d3_DisposeObject(char* object);
void __cdecl fcn_00439aa0(char* object);
void __cdecl fcn_00439c60(char* object);
char* __cdecl fcn_0043a140(char* object);
void __cdecl fcn_0043b850(void* stream);
int __cdecl fcn_00446ca0(unsigned version);
char* __cdecl rd_object(void* stream, char* parent, unsigned int version, unsigned char resources);
char* __cdecl fcn_00447e30(void* stream, int version);
void __cdecl fcn_0045b290(char* resource, int mode);
char* __cdecl fcn_0045b700(int a1, int n, int a3);
void __cdecl gv_Free3Fields(int* slot);
void __cdecl fcn_0045cfa0(SCENE_PROGRESS progress);
int __cdecl _strcmpi(const char* a, const char* b);

/* ADDRESS: GOLDTL 0x00448360 */
char __cdecl fcn_00448360(const char* filename, void* stream, SCENE_PROGRESS progress)
{
	char name[256];
	VECTOR3 vec;
	float discarded;
	float fog_a;
	float fog_b;
	int version;
	int count;
	int index;
	int rows;
	int color;
	int dim;
	int k;
	char* s;
	char* obj;
	char* clone;
	char* row;
	char* slot;
	char* universe;
	unsigned char present;

	g_6b85a4 = 0;
	if (stream != 0) {
		s = (char*) stream;
	} else {
		s = (char*) vfs_Tfopen(filename, "rb", g_6b7fdc);
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
	g_6b86d4++;
	if (version >= 0x3a6c000b) {
		fcn_004011a0(s, name);
		fcn_004011d0(s, &discarded);
		fcn_00401280(s, &vec);
		g_67bbdc.z = vec.z;
		g_67bbdc.x = vec.x;
		g_67bbdc.y = vec.y;
		if (version >= 0x3a6c00b5) {
			fcn_00401280(s, &vec);
			g_6b86c4.y = vec.y;
			g_6b86c4.x = vec.x;
			g_6b86c4.z = vec.z;
		}
		if (version >= 0x3a6c00b3) {
			dim = 0;
			if (version >= 0x3a6c00b7) {
				fcn_004011f0(s, &dim);
			}
			*(int*) (g_67a370 + 0xb4) = dim;
			fcn_004011f0(s, &color);
			fcn_004011d0(s, &fog_a);
			fcn_004011d0(s, &fog_b);
			fcn_00438920(fog_a, fog_b, color);
		}
		row = g_1041d80 + 4;
		do {
			*(float*) (row - 4) = g_67bbdc.x;
			*(float*) row = g_67bbdc.y;
			*(float*) (row + 4) = g_67bbdc.z;
			*(int*) (row + 8) = 0;
			*(int*) (row + 0xc) = 0;
			*(int*) (row + 0x10) = 0;
			row += 0x60;
		} while (row < g_1041d80 + 0x2a4);
		if (version >= 0x3a6c00a2) {
			rows = fcn_00446ca0((unsigned) version);
			index = 0;
			if (rows > 0) {
				do {
					fcn_00401280(s, &vec);
					row = g_1041d80 + index * 0x60;
					*(float*) row = vec.x;
					*(float*) (row + 4) = vec.y;
					*(float*) (row + 8) = vec.z;
					if (version >= 0x3a6c00b3) {
						if (version >= 0x3a6c00b5) {
							fcn_00401280(s, &vec);
							*(float*) (row + 0xc) = vec.x;
							*(float*) (row + 0x10) = vec.y;
							*(float*) (row + 0x14) = vec.z;
						}
						k = 0;
						do {
							fcn_004011f0(s, &color);
							fcn_004011d0(s, &fog_a);
							slot = g_1041d80 + 0x18 + (k + index * 8) * 12;
							*(int*) slot = color;
							*(float*) (slot + 4) = fog_a;
							fcn_004011d0(s, &fog_b);
							*(float*) (slot + 8) = fog_b;
							k = k + 1;
						} while (k < 6);
					}
					index = index + 1;
				} while (index < rows);
			}
		}
		if (g_6b8484 != 0) {
			d3_DisposeObject(g_6b8484);
		}
		fcn_004011f0(s, &count);
		if (count > 0) {
			index = 0;
			do {
				rd_object(s, 0, (unsigned) version, 0);
				if (progress != 0) {
					progress(0, index, count);
				}
				index++;
			} while (index < count);
		}
		fcn_00401180(s, &present);
		if (present != 0) {
			g_6b8300 = fcn_00447e30(s, version);
		}
		obj = g_1043254;
		while (obj != g_1042340) {
			if (*(int*) (obj + 0x218) == 3 && _strcmpi(name, obj) == 0) {
				g_6b8484 = obj;
				if ((obj[0x214] & 0x40) != 0) {
					fcn_00438b40(obj, (int*) (obj + 0x5c));
					fcn_00438cb0(obj, (int*) (obj + 0x90));
				}
				fcn_00439c60(obj);
				break;
			}
			obj = *(char**) (obj + 0x1f4);
		}
		if (version >= 0x3a6c00a7) {
			fcn_0043b850(s);
		}
	} else {
		fcn_0041d9e0("Scene too old... Sorry!");
	}
	if (stream == 0) {
		CloseVfsStream(s);
	}
	if (version < 0x3a6c00b1 && g_6b8300 != 0) {
		obj = g_1043254;
		while (obj != g_1042340) {
			if (*(int*) (obj + 0x218) == 7) {
				clone = fcn_0043a140(obj);
				clone[0x215] |= 4;
				strcat(clone, "boden");
				fcn_00439aa0(clone);
				break;
			}
			obj = fcn_00437890(obj);
		}
	}
	if (g_6b8300 == 0) {
		if (g_6b89e4 != 0) {
			fcn_0045b290(g_6b89e4, 0);
		} else {
			g_6b89e4 = fcn_0045b700(0, -g_6b89b0, 1);
		}
	} else if (g_6b89e4 != 0) {
		gv_Free3Fields((int*) g_6b89e4);
		g_6b89e4 = 0;
	}
	universe = g_67a370;
	if (*(int*) (universe + 0xb4) == 0) {
		*(int*) (universe + 0xb4) = g_6b8300 != 0 ? 128 : 64;
		universe = g_67a370;
	}
	if (g_6b8300 != 0) {
		*(char**) (universe + 0xac) = g_6b8300;
	}
	fcn_0045cfa0(progress);
	g_6b86d4--;
	if (filename != 0) {
		strncpy(g_67a370, filename, 0x7f);
	}
	*(unsigned char*) (g_67a370 + 0x3d4) = 1;
	*(int*) (g_67a370 + 0x3d8) = 0;
	return 1;
}
/* Layout scaffolding: shifts the next source object to its reference
 * VA. 0x90 filler, not reconstruction. Generated by the text lead pass. */
#pragma data_seg(".text")

unsigned char _dpad_6b870c[728];
