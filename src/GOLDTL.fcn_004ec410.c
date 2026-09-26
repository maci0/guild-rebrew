// FUNCTION: GOLD 0x004ea690
// SIZE: 272
// FUNCTION: GOLDTL 0x004ec410
// SIZE: 272

#include <stdio.h>

// SIZE 0x18
typedef struct {
	char a;
	int b;
	char c;
	int d;
	char e;
	int f;
} Rec;

#include "client_types.h"
extern Rec18_68da68 g_9a9220[42];
extern char g_68de60[];

int __cdecl fcn_00430910(void* p, int size, int n, void* file);

int __cdecl fcn_004ec410(void* file)
{
	int ver;
	char buf[256];
	int i;

	ver = 0x2a;
	if (file == 0) {
		return 0;
	}
	if (!fcn_00430910(&ver, 4, 1, file)) {
		return 0;
	}
	sprintf(buf, g_68de60, ver);
	for (i = 0; i < 42; i++) {
		if (!fcn_00430910(&((Rec*)g_9a9220)[i].a, 1, 1, file)) {
			return 0;
		}
		if (!fcn_00430910(&((Rec*)g_9a9220)[i].b, 4, 1, file)) {
			return 0;
		}
		if (!fcn_00430910(&((Rec*)g_9a9220)[i].c, 1, 1, file)) {
			return 0;
		}
		if (!fcn_00430910(&((Rec*)g_9a9220)[i].d, 4, 1, file)) {
			return 0;
		}
		if (!fcn_00430910(&((Rec*)g_9a9220)[i].e, 1, 1, file)) {
			return 0;
		}
		if (!fcn_00430910(&((Rec*)g_9a9220)[i].f, 4, 1, file)) {
			return 0;
		}
	}
	return 1;
}
