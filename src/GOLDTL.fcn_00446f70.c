// SIZE 0xc
#include "client_types.h"
typedef VECTOR3 Vec3;

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

extern int g_6b7fdc;
extern int g_6b8484;
extern VECTOR3 g_67bbdc;
extern VECTOR3 g_6b86c4;
extern int g_67a370;
extern int g_6b805c;
extern float g_10425fc;
extern float g_104329c;
extern char g_1041d80[];
extern char* g_1043254;
extern char g_1042340[];
extern int g_6b8300;

void* __cdecl fcn_0042ff50(const char*, const char*, int);
void __cdecl fcn_00401360(void*, int);
void __cdecl fcn_00401230(void*, int);
void __cdecl fcn_00401260(void*, float);
void __cdecl fcn_004012f0(void*, Vec3*);
void __cdecl fcn_00401210(void*, char);
void* __cdecl fcn_00437890(void*);
void __cdecl fcn_00446540(void*, void*);
void __cdecl fcn_004469e0(void*, int);
void __cdecl fcn_0043b740(void*, int);
void __cdecl CloseVfsStream(void*);

/* ADDRESS: GOLDTL 0x00446f70 */

void __cdecl fcn_00446f70(const char* name, void* stream)
{
	void* s;
	void* p;
	int n;
	int i;
	int k;

	s = stream;
	if (s == 0) {
		s = fcn_0042ff50(name, "wb", g_6b7fdc);
		if (s == 0) {
			return;
		}
	}
	fcn_00401360(s, 0x3a6c00bb);
	fcn_00401230(s, g_6b8484);
	fcn_00401260(s, 0.0f);
	fcn_004012f0(s, &g_67bbdc);
	fcn_004012f0(s, &g_6b86c4);
	fcn_00401360(s, ((Cfg*)g_67a370)->xb4);
	fcn_00401360(s, g_6b805c);
	fcn_00401260(s, g_10425fc);
	fcn_00401260(s, g_104329c);
	for (i = 0; i < 7; i++) {
		fcn_004012f0(s, &((Slot*)g_1041d80)[i].a);
		fcn_004012f0(s, &((Slot*)g_1041d80)[i].b);
		for (k = 0; k < 6; k++) {
			fcn_00401360(s, ((Slot*)g_1041d80)[i].pal[k].color);
			fcn_00401260(s, ((Slot*)g_1041d80)[i].pal[k].f4);
			fcn_00401260(s, ((Slot*)g_1041d80)[i].pal[k].f8);
		}
	}
	n = 0;
	for (p = ((void*)g_1043254); p != &(*(char*)g_1042340); p = fcn_00437890(p)) {
		n++;
	}
	fcn_00401360(s, n);
	for (p = ((void*)g_1043254); p != &(*(char*)g_1042340); p = fcn_00437890(p)) {
		fcn_00446540(s, p);
	}
	fcn_00401210(s, g_6b8300 != 0);
	if (g_6b8300 != 0) {
		fcn_004469e0(s, g_6b8300);
	}
	fcn_0043b740(s, ((Cfg*)g_67a370)->x3c8);
	if (stream == 0) {
		CloseVfsStream(s);
	}
}
