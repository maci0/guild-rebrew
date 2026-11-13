#include "client_scene_loader.h"
#include "client_types.h"
#include <string.h>
extern void* g_6b7fdc;
extern unsigned char g_6339e4;
extern int g_6b86d4;
extern char* g_67a370;
extern char g_1041d80[];
extern char* g_6338c4;
extern char* g_6b8300;
extern char* g_fc52f0;
extern char g_fc2700[];
void* __cdecl fcn_00430470(const char*, const char*, void*);
int __cdecl fcn_00430aa0(void*);
int __cdecl fcn_00401180(void*, void*);
void __cdecl fcn_004011a0(void*, char*);
int __cdecl fcn_004011d0(void*, void*);
void __cdecl fcn_00401280(void*, void*);
void __cdecl ReportClientMessage(const char*);
void __cdecl fcn_0043a6f0(float, float, int);
void __cdecl fcn_00438b40(char*, int*);
void __cdecl fcn_00438cb0(char*, int*);
void __cdecl fcn_00439c60(char*);
void __cdecl fcn_0043c7a0(char*);
char* __cdecl fcn_0044abb0(void*, char*, unsigned int, unsigned char);
int __cdecl fcn_0044a9e0(unsigned int);
char* __cdecl fcn_0044b920(void*, int);
void __cdecl fcn_0043ea10(void*);
char* __cdecl fcn_00438c30(char*);
char* __cdecl fcn_0043d180(char*);
void __cdecl fcn_0043ca20(char*);
void __cdecl fcn_0045e610(char*, int);
char* __cdecl fcn_0045eea0(int, int, int);
void __cdecl fcn_0045ef50(char*);

/* Reader scratch. The reference frame reserves sixteen bytes for it and never
 * touches the fourth float; only x/y/z reach the scene tables. */
typedef struct {
	float x;
	float y;
	float z;
	float w;
} VEC4;

/* ADDRESS: GOLD 0x0044be60 */
char __cdecl fcn_0044be60(const char* filename, void* stream, SCENE_PROGRESS progress)
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
		s = (char*) fcn_00430470(filename, "rb", g_6b7fdc);
	}
	if (s == 0) {
		return 0;
	}
	fcn_004011d0(s, &version);
	if ((version & 0xffff0000) != 0x3a6c0000 || version < 0x3a6c0001) {
		if (stream == 0) {
			fcn_00430aa0(s);
		}
		return 0;
	}
	g_6b86d4++;
	if (version >= 0x3a6c000b) {
		fcn_004011a0(s, name);
		fcn_004011d0(s, &discarded);
		fcn_00401280(s, &vec);
		*(float*) 0x5fcc74 = discarded;
		g_67bbdc.x = vec.x;
		g_67bbdc.y = vec.y;
		g_67bbdc.z = vec.z;
		if (version >= 0x3a6c00b5) {
			fcn_00401280(s, &vec);
			(*(float*) 0x633b1c) = vec.x;
			(*(float*) 0x633b20) = vec.y;
			(*(float*) 0x633b24) = vec.z;
		}
		if (version >= 0x3a6c00b3) {
			/* index doubles as the scene value written below, then as the
			 * row counter of the geometry loop. */
			index = 0;
			if (version >= 0x3a6c00b7) {
				fcn_004011d0(s, &index);
			}
			*(int*) (g_67a370 + 0xb4) = index;
			fcn_004011d0(s, &fog_color);
			fcn_004011d0(s, &fog_a);
			fcn_004011d0(s, &fog_b);
			fcn_0043a6f0(fog_a, fog_b, fog_color);
		}
		/* The reference writes the row count into index before the loop
		 * and never reads it back. */
		index = 7;
		for (index = 0; index < 7; index++) {
			*(float*) (g_1041d80 + index * 0x60) = g_67bbdc.x;
			*(float*) (g_1041d80 + index * 0x60 + 4) = g_67bbdc.y;
			*(float*) (g_1041d80 + index * 0x60 + 8) = g_67bbdc.z;
			*(int*) (g_1041d80 + index * 0x60 + 0xc) = 0;
			*(int*) (g_1041d80 + index * 0x60 + 0x10) = 0;
			*(int*) (g_1041d80 + index * 0x60 + 0x14) = 0;
		}
		if (version >= 0x3a6c00a2) {
			rows = fcn_0044a9e0((unsigned) version);
			index = 0;
			if (rows > 0) {
				do {
					fcn_00401280(s, &vec);
					*(float*) (g_1041d80 + index * 0x60) = vec.x;
					*(float*) (g_1041d80 + index * 0x60 + 4) = vec.y;
					*(float*) (g_1041d80 + index * 0x60 + 8) = vec.z;
					if (version >= 0x3a6c00b3) {
						if (version >= 0x3a6c00b5) {
							fcn_00401280(s, &vec);
							*(float*) (g_1041d80 + index * 0x60 + 0xc) = vec.x;
							*(float*) (g_1041d80 + index * 0x60 + 0x10) = vec.y;
							*(float*) (g_1041d80 + index * 0x60 + 0x14) = vec.z;
						}
						/* count is the per-row entry counter and later the
						 * object count read after the geometry block. */
						count = 0;
						do {
							fcn_004011d0(s, &color);
							fcn_004011d0(s, &discarded);
							*(int*) (g_1041d80 + 0x18 + (count + index * 8) * 12) = color;
							*(float*) (g_1041d80 + 0x1c + (count + index * 8) * 12) = discarded;
							fcn_004011d0(s, &discarded);
							*(float*) (g_1041d80 + 0x20 + (count + index * 8) * 12) = discarded;
							count = count + 1;
						} while (count < 6);
					}
					index = index + 1;
				} while (index < rows);
			}
		}
		if (g_6338c4 != 0) {
			fcn_0043c7a0(g_6338c4);
		}
		fcn_004011d0(s, &count);
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
		fcn_00401180(s, &present);
		if (present != 0) {
			g_6b8300 = fcn_0044b920(s, version);
		}
		obj = g_fc52f0;
		while (obj != g_fc2700) {
			if (*(int*) (obj + 0x218) == 3 && _strcmpi(name, obj) == 0) {
				g_6338c4 = obj;
				if ((obj[0x211] & 1) != 0) {
					fcn_00438b40(obj, (int*) (obj + 0x5c));
					fcn_00438cb0(obj, (int*) (obj + 0x90));
				}
				fcn_00439c60(obj);
				break;
			}
			obj = *(char**) (obj + 0x1f0);
		}
		if (version >= 0x3a6c00a7) {
			fcn_0043ea10(s);
		}
	} else {
		ReportClientMessage("Scene too old... Sorry!");
	}
	if (stream == 0) {
		fcn_00430aa0(s);
	}
	if (version < 0x3a6c00b1 && g_6b8300 != 0) {
		obj = g_fc52f0;
		while (obj != g_fc2700) {
			if (*(int*) (obj + 0x218) == 7) {
				clone = fcn_0043d180(obj);
				clone[0x211] |= 0x10;
				strcat(clone, "boden");
				fcn_0043ca20(clone);
				break;
			}
			obj = fcn_00438c30(obj);
		}
	}
	if (g_6b8300 == 0) {
		if ((*(char**) 0x633df8) != 0) {
			fcn_0045e610((*(char**) 0x633df8), 0);
		} else {
			(*(char**) 0x633df8) = fcn_0045eea0(0, -(*(int*) 0x633dcc), 1);
		}
	} else if ((*(char**) 0x633df8) != 0) {
		fcn_0045ef50((*(char**) 0x633df8));
		(*(char**) 0x633df8) = 0;
	}
	universe = g_67a370;
	if (*(int*) (universe + 0xb4) == 0) {
		*(int*) (universe + 0xb4) = g_6b8300 != 0 ? 128 : 64;
		universe = g_67a370;
	}
	if (g_6b8300 != 0) {
		*(char**) (universe + 0xac) = g_6b8300;
	}
	fcn_00461080(0, progress);
	g_6b86d4--;
	if (filename != 0) {
		strncpy(g_67a370, filename, 0x7f);
	}
	*(unsigned char*) (g_67a370 + 0x3d4) = 1;
	*(int*) (g_67a370 + 0x3d8) = 0;
	return 1;
}
