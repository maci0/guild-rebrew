// SIZE 0xc
#include "client_types.h"
typedef Vec3_67bbdc Vec3;

// SIZE 0xc
typedef Pal_1041d20 Pal;

// SIZE 0x60
typedef struct {
	Vec3 a;
	Vec3 b;
	Pal pal[6];
} Slot;

// SIZE 0x3dc
typedef struct {
	unsigned char b0;
	char p1[0x7f];
	int x80;
	int x84;
	char p88[0x34c];
	unsigned char b3d4;
	unsigned char b3d5;
	char p3d6[6];
} Level;

// SIZE 0x3cc
typedef struct {
	char p0[0x3c8];
	int x3c8;
} Cfg;

extern char* g_1043254;
extern char g_1042340[];
extern char* g_1042538;
extern char g_1043060;
extern char* g_1040c74;
extern char g_1040640[];
extern int g_6b8300;
extern int g_6b89c0;
extern int g_67a370;
extern Vec3_67bbdc g_6b86c4;
extern Vec3_67bbdc g_67bbdc;
extern Pal_1041d20 g_1041d20[6];
extern char g_1041d80[];
extern int g_6b8484;
extern char* g_6b8480;
extern char* g_6b847c;
extern char* g_6b8478;
extern int g_6b8058;
extern int g_67a37c;
extern int g_67a380;
extern int g_6b8010;
extern char g_10432c0[];

void __cdecl fcn_004398d0(void*);
void __cdecl fcn_00452420(void*);
void __cdecl fcn_0043bcf0(int);
void __cdecl fcn_00459b40(int);
void __cdecl m_FreeTracked(int);
void __cdecl fcn_00444040(void);

/* ADDRESS: GOLDTL 0x00442e30 */

void __cdecl fcn_00442e30(void)
{
	int i;
	char* d;
	int n;

	while ((*(void**)&g_1043254) != &(*(char*)g_1042340)) {
		fcn_004398d0((*(void**)&g_1043254));
	}
	while (((void*)g_1040c74) != &(*(char*)g_1040640)) {
		fcn_00452420(((void*)g_1040c74));
	}
	if (g_6b8300 != 0) {
		fcn_0043bcf0(g_6b8300);
		g_6b8300 = 0;
	}
	if (g_6b89c0 != 0) {
		fcn_00459b40(g_6b89c0);
		g_6b89c0 = 0;
	}
	if (((Cfg*)g_67a370)->x3c8 != 0) {
		m_FreeTracked(((Cfg*)g_67a370)->x3c8);
		((Cfg*)g_67a370)->x3c8 = 0;
	}
	(*(void**)&g_1043254) = &(*(char*)g_1042340);
	(*(void**)&g_1042538) = &g_1043060;
	g_6b86c4.x = 0.0f;
	g_6b86c4.y = 0.0f;
	g_6b86c4.z = 0.0f;
	g_67bbdc.x = 200.0f;
	g_67bbdc.y = 200.0f;
	g_67bbdc.z = 200.0f;
	for (i = 0; i < 6; i++) {
		g_1041d20[i].color = 0;
		g_1041d20[i].f8 = 0.0f;
		g_1041d20[i].f4 = 0.0f;
	}
	n = 0x48;
	for (i = 0; i < 7; i++) {
		((Slot*)g_1041d80)[i].a.x = g_67bbdc.x;
		((Slot*)g_1041d80)[i].a.y = g_67bbdc.y;
		((Slot*)g_1041d80)[i].a.z = g_67bbdc.z;
		((Slot*)g_1041d80)[i].b.x = g_6b86c4.x;
		((Slot*)g_1041d80)[i].b.y = g_6b86c4.y;
		((Slot*)g_1041d80)[i].b.z = g_6b86c4.z;
		d = (char*) ((Slot*)g_1041d80)[i].pal;
		/*
		 * TODO: replace this inline-asm copy with proper C once a spelling is
		 * found; no msvc6 C memcpy form emits the prelude
		 * (docs/codegen-walls.md section 6b).
		 */
		__asm {
			mov edi, d
			mov esi, offset g_1041d20
			mov ebx, n
			lea ecx, [edi+edi*2]
			and ecx, 3
			sub ebx, ecx
			jle short L1
			rep movsb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep movsd
		L1:
			add ecx, ebx
			rep movsb
		}
	}
	g_6b8484 = 0;
	(*(int*)&g_6b8480) = 0;
	(*(int*)&g_6b847c) = 0;
	(*(int*)&g_6b8478) = 0;
	fcn_00444040();
	g_6b8058 = 0;
	g_67a37c = 4;
	g_67a380 = 0xf;
	((Level*)g_10432c0)[g_6b8010].x84 = 0;
	((Level*)g_10432c0)[g_6b8010].x80 = 0;
	((Level*)g_10432c0)[g_6b8010].b3d5 = 0;
	((Level*)g_10432c0)[g_6b8010].b3d4 = 0;
	((Level*)g_10432c0)[g_6b8010].b0 = 0;
}
