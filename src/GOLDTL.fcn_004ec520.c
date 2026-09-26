// FUNCTION: GOLD 0x004ea7a0
// SIZE: 320
// FUNCTION: GOLDTL 0x004ec520
// SIZE: 320

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
extern char g_68de84[];

void __cdecl srv_LogWinsockError(void);
int __cdecl ls_ReadVfsDataChecked(void* p, int size, int n, void* file);

int __cdecl fcn_004ec520(void* file, int version)
{
	int cnt;
	char buf[256];
	unsigned int n;
	unsigned int i;

	n = version >= 0x10051 ? 0x2a : 0x25;
	srv_LogWinsockError();
	if (file == 0) {
		return 0;
	}
	if (!ls_ReadVfsDataChecked(&cnt, 4, 1, file)) {
		return 0;
	}
	if (cnt != n) {
		sprintf(buf, g_68de84, cnt, 0x2a);
		return 0;
	}
	for (i = 0; i < n; i++) {
		if (!ls_ReadVfsDataChecked(&((Rec*)g_9a9220)[i].a, 1, 1, file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(&((Rec*)g_9a9220)[i].b, 4, 1, file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(&((Rec*)g_9a9220)[i].c, 1, 1, file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(&((Rec*)g_9a9220)[i].d, 4, 1, file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(&((Rec*)g_9a9220)[i].e, 1, 1, file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(&((Rec*)g_9a9220)[i].f, 4, 1, file)) {
			return 0;
		}
	}
	return 1;
}
