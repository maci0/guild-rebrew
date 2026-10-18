#include "client_scene_loader.h"
#include "client_types.h"
#include "Develop/Units/d3/d3_object.h"

#include <string.h>

int __cdecl fcn_00401180(void* stream, void* dst);
char* __cdecl fcn_004011a0(void* stream, char* dst);
int __cdecl fcn_004011d0(void* stream, void* dst);
void __cdecl fcn_00401240(void* stream, void* dst);
void __cdecl fcn_0041d9e0(const char* msg);
void* __cdecl fcn_00430470(const char* filename, const char* mode, int vfs);
void __cdecl fcn_00430aa0(void* stream);
void __cdecl fcn_00438b40(char* object, int* vector);
char* __cdecl fcn_00438c30(char* object);
void __cdecl fcn_00438cb0(char* object, int* vector);
void __cdecl fcn_00439c60(char* object);
void __cdecl fcn_0043a6f0(float a, float b, int color);
void __cdecl fcn_0043c7a0(char* object);
char* __cdecl fcn_0043d180(char* object);
void __cdecl fcn_0043ea10(void* stream);
int __cdecl fcn_00446ca0(unsigned version);
char* __cdecl fcn_0044b920(void* stream, unsigned version);
void __cdecl fcn_0045e610(int shadow, int mode);
int __cdecl fcn_0045eea0(int a, int b, int c);
void __cdecl fcn_0045ef50(int shadow);
void __cdecl fcn_00461080(int selector, SCENE_PROGRESS progress);
char* __cdecl rd_object(void* stream, char* parent, unsigned int version, unsigned char resources);
int __cdecl _strcmpi(const char* a, const char* b);

/* Integer catalog views. g_6b8300 is the terrain pointer; the header still says int. */
extern int g_67a370;
extern int g_6b86d4;
extern char* g_6b8300;

/* ADDRESS: GOLD 0x0044be60 */
char __cdecl fcn_0044be60(const char* filename, void* stream, SCENE_PROGRESS progress)
{
	int version;
	int index;
	int count;
	int scalar;
	int sample;
	int color;
	int vec[3];
	float fog_a;
	float fog_b;
	char terrain;
	char name[256];
	int cursor;
	int rows;
	int off;
	void* opened;
	void* active;
	char* node;
	char* clone;
	char* uni;

	*(unsigned char*) 0x6339e4 = 0;
	opened = stream;
	if (opened != 0) {
		active = opened;
	} else {
		active = fcn_00430470(filename, "rb", *(int*) 0x6333fc);
	}
	if (active != 0) {
		fcn_004011d0(active, &version);
		if ((version & 0xffff0000) == 0x3a6c0000) {
			if (version >= 0x3a6c0001) {
	g_6b86d4++;
	if (version >= 0x3a6c000b) {
		fcn_004011a0(active, name);
		fcn_004011d0(active, &scalar);
		fcn_00401240(active, vec);
		*(int*) ((char*) &g_67bbdc + 4) = vec[1];
		*(int*) 0x5fcc74 = scalar;
		*(int*) &g_67bbdc.x = vec[0];
		*(int*) ((char*) &g_67bbdc + 8) = vec[2];
		if (version >= 0x3a6c00b5) {
			fcn_00401240(active, vec);
			*(int*) 0x633b1c = vec[0];
			*(int*) 0x633b20 = vec[1];
			*(int*) 0x633b24 = vec[2];
		}
		if (version >= 0x3a6c00b3) {
			index = 0;
			if (version >= 0x3a6c00b7) {
				fcn_004011d0(active, &index);
			}
			uni = (char*) g_67a370;
			*(int*) (uni + 0xb4) = index;
			fcn_004011d0(active, &color);
			fcn_004011d0(active, &fog_a);
			fcn_004011d0(active, &fog_b);
			fcn_0043a6f0(fog_a, fog_b, color);
		}
		index = 7;
		cursor = 0xfba9c4;
		do {
			*(int*) (cursor - 4) = *(int*) &g_67bbdc.x;
			*(int*) cursor = *(int*) ((char*) &g_67bbdc + 4);
			*(int*) (cursor + 4) = *(int*) ((char*) &g_67bbdc + 8);
			*(int*) (cursor + 8) = 0;
			*(int*) (cursor + 0xc) = 0;
			*(int*) (cursor + 0x10) = 0;
			cursor += 0x60;
		} while (cursor < 0xfbac64);
		if (version >= 0x3a6c00a2) {
			rows = fcn_00446ca0((unsigned) version);
			index = 0;
			if (rows > 0) {
				do {
					fcn_00401240(active, vec);
					off = index * 0x60;
					*(int*) (0xfba9c0 + off) = vec[0];
					*(int*) (0xfba9c4 + off) = vec[1];
					*(int*) (0xfba9c8 + off) = vec[2];
					if (version >= 0x3a6c00b3) {
						if (version >= 0x3a6c00b5) {
							fcn_00401240(active, vec);
							off = index * 0x60;
							*(int*) (0xfba9cc + off) = vec[0];
							*(int*) (0xfba9d0 + off) = vec[1];
							*(int*) (0xfba9d4 + off) = vec[2];
						}
						count = 0;
						do {
							fcn_004011d0(active, &sample);
							fcn_004011d0(active, &scalar);
							off = (index * 8 + count) * 12;
							*(int*) (0xfba9d8 + off) = sample;
							*(int*) (0xfba9dc + off) = scalar;
							fcn_004011d0(active, &scalar);
							*(float*) (0xfba9e0 + (index * 8 + count) * 12) = *(float*) &scalar;
							count++;
						} while (count < 6);
					}
					index++;
				} while (index < rows);
			}
		}
		node = *(char**) 0x6338c4;
		if (node != 0) {
			fcn_0043c7a0(node);
		}
		fcn_004011d0(active, &count);
		index = 0;
		if (count > 0) {
			do {
				rd_object(active, 0, (unsigned int) version, 0);
				if (progress != 0) {
					progress(0, index, count);
				}
				index++;
			} while (index < count);
		}
		fcn_00401180(active, &terrain);
		if (terrain != 0) {
			g_6b8300 = fcn_0044b920(active, (unsigned) version);
		}
		node = *(char**) 0xfc52f0;
		if (node != (char*) 0xfc2700) {
			do {
				if (*(int*) (node + 0x218) == 3 && _strcmpi(name, node) == 0) {
					*(char**) 0x6338c4 = node;
					if ((node[0x211] & 1) != 0) {
						fcn_00438b40(node, (int*) (node + 0x5c));
						fcn_00438cb0(node, (int*) (node + 0x90));
					}
					fcn_00439c60(node);
					break;
				}
				node = *(char**) (node + 0x1f0);
			} while (node != (char*) 0xfc2700);
		}
		if (version >= 0x3a6c00a7) {
			fcn_0043ea10(active);
		}
	} else {
		fcn_0041d9e0("Scene too old... Sorry!");
	}
	if (opened == 0) {
		fcn_00430aa0(active);
	}
	if (version < 0x3a6c00b1 && g_6b8300 != 0) {
		node = *(char**) 0xfc52f0;
		while (node != (char*) 0xfc2700) {
			if (*(int*) (node + 0x218) == 7) {
				clone = fcn_0043d180(node);
				clone[0x211] |= 0x10;
				strcat(clone, "boden");
				fcn_0043ca20(clone);
				break;
			}
			node = fcn_00438c30(node);
		}
	}
	if (g_6b8300 == 0) {
		if (*(int*) 0x633df8 != 0) {
			fcn_0045e610(*(int*) 0x633df8, 0);
		} else {
			*(int*) 0x633df8 = fcn_0045eea0(0, -*(int*) 0x633dcc, 1);
		}
	} else if (*(int*) 0x633df8 != 0) {
		fcn_0045ef50(*(int*) 0x633df8);
		*(int*) 0x633df8 = 0;
	}
	uni = (char*) g_67a370;
	if (*(int*) (uni + 0xb4) == 0) {
		*(int*) (uni + 0xb4) = g_6b8300 != 0 ? 0x80 : 0x40;
		uni = (char*) g_67a370;
	}
	if (g_6b8300 != 0) {
		*(char**) (uni + 0xac) = g_6b8300;
	}
	fcn_00461080(0, progress);
	g_6b86d4--;
	if (filename != 0) {
		strncpy((char*) g_67a370, filename, 0x7f);
	}
	uni = (char*) g_67a370;
	uni[0x3d4] = 1;
	*(int*) ((char*) g_67a370 + 0x3d8) = 0;
	return 1;
			} else if (opened == 0) {
				fcn_00430aa0(active);
			}
		} else if (opened == 0) {
			fcn_00430aa0(active);
		}
	}
	return 0;
}
