// FUNCTION: GOLD 0x591250
// FUNCTION: GOLDTL 0x00599f90

#include <string.h>

typedef struct
{
	int x0;
	int x4;
	int x8;
	int xc;
	int x10;
	char pad14[0x38];
	int x4c;
} Query;
// SIZE 0x50

extern char g_14cf950;
extern int g_14ce8d8;
extern int g_67d370;
extern int g_6a2590;
extern int g_6a2594;
extern char g_7746f4;
extern unsigned char* g_7746c8;
extern char* g_7746c4;
extern unsigned short g_774970;

unsigned char* __cdecl fcn_005bdc30(int, Query*, int, int, int);
int __cdecl gm_CheckEntityType(unsigned char*);
void __cdecl fcn_00526920(unsigned char*, int, char*);
unsigned char __cdecl fcn_00506380(int, unsigned char*, int, int);
void __cdecl fcn_0052cbb0(unsigned char*);

void __cdecl fcn_00599f90(void)
{
	Query q;
	unsigned char* e;

	if (g_14cf950 != 0x32) {
		if (g_14ce8d8 == 0) {
			return;
		}
		if (g_67d370 != g_6a2590 && g_67d370 != g_6a2594) {
			return;
		}
	}
	memset(&q, 0, sizeof(q));
	q.x10 = 0;
	q.x8 = 0;
	q.x4c = 0x71f;
	e = fcn_005bdc30(1, &q, 0, 0, 0);
	if (e == 0 || g_7746f4 != 0) {
		return;
	}
	if ((*(int*)&g_7746c8) != 0) {
		if (gm_CheckEntityType(e) && *e == 0x47) {
			fcn_00526920(e, 0xfd, "");
			return;
		}
		fcn_00526920(e, -1, "");
		return;
	}
	if (gm_CheckEntityType(e) && *e == 0x47) {
		if (fcn_00506380(g_774970, e, 0, 0) & 1) {
			fcn_00526920(e, 0xfd, "");
		}
		return;
	}
	if ((*(int*)&g_7746c8) == 0 && (*(int*)&g_7746c4) == 0) {
		fcn_0052cbb0(e);
		return;
	}
	fcn_00526920(e, *(unsigned short*) (e + 0x29), "");
}
