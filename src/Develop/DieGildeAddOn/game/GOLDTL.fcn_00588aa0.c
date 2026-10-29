typedef struct {
	float x;
	float y;
	float z;
} Vec3;

typedef struct {
	float x;
	float y;
	float z;
	float w;
} Vec4;

/* 0x68 bytes; layout shared with fcn_005e8e80's particle record. */
typedef struct {
	Vec4 cur;       /* 0x00 */
	Vec4 start;     /* 0x10 */
	Vec3 pos;       /* 0x20 */
	float pad2c;    /* 0x2c */
	Vec3 origin;    /* 0x30 */
	float pad3c;    /* 0x3c */
	Vec4 color;     /* 0x40 */
	float area;     /* 0x50 */
	float mass;     /* 0x54 */
	int pad58;      /* 0x58 */
	int active;     /* 0x5c */
	int time;       /* 0x60 */
	int age;        /* 0x64 */
} Particle;

/* Client object that drives one cannon explosion. */
typedef struct {
	Vec3 pos;         /* 0x00 */
	float pad0c[6];
	Vec3 dir1;        /* 0x24 */
	float pad30;
	Vec3 dir2;        /* 0x34 */
	float pad40;
	Vec3 dir3;        /* 0x44 */
	float pad50[15];
	int frame0;       /* 0x8c */
	int frame1;       /* 0x90 */
	int frame2;       /* 0x94 */
	float pad98[2];
	int mode;         /* 0xa0 */
	float pada4[3];
	int slot0;        /* 0xb0 */
	int slot1;        /* 0xb4 */
} Emitter;

extern float g_662910;
extern unsigned short g_774970;
#include "GOLDTL.fcn_00588aa0_gconf.h"

int __cdecl fcn_00471f80(int slot);
int __cdecl fcn_004f0ff0(char* a0, int a1, int a2, int a3, int* o1, int* o2);
void __cdecl fcn_004f11c0(char* p, float* o1, float* o2);
float __cdecl fcn_004f1290(char* p);
int __cdecl fcn_004f0a30(char* a0, char* a1, unsigned int* a2,
	unsigned int* a3, unsigned int* a4, float a5, int a6, unsigned int a7);
float __cdecl fcn_004f0eb0(int level, int percent, int count);
int __cdecl fcn_005e8e80(Particle* o, Vec3* pos, Vec3* dir, float speed,
	float b, float a);
int __cdecl fcn_005e8fe0(float* p, float spread, float* dir, float lift,
	float* up, float scale);
int __cdecl fcn_004c4450(int i);
int __cdecl fcn_005373e0(int a, int b);
int __cdecl fcn_00426fd0(const char* name);
int __cdecl fcn_00428340(int h, int a, int b, int c, int d, int e);
int __cdecl fcn_004235b0(char* bank, const char* name, int prio, int loop,
	int pan, int vol, int a);
void __cdecl fcn_00589390(void);

/* ADDRESS: GOLDTL 0x00588aa0 */
int __cdecl fcn_00588aa0(Emitter* a0, char* a1)
{
	Particle p0;
	Particle p1;
	Particle p2;
	Vec3 pos0;
	Vec3 pos1;
	Vec3 pos2;
	float spread;
	float scale;
	float k;
	float speed;
	float b;
	float px;
	float py;
	float pz;
	int slot0;
	int slot1;
	int o1;
	int o2;
	int h;
	int h2;
	int h3;
	int sel;
	int dx;
	int dy;
	int ex;
	int ey;
	int ez;

	dx = 0;
	dy = 0;
	ex = 0;
	ey = 0;
	ez = 0;
	slot0 = fcn_00471f80(a0->slot0);
	slot1 = fcn_00471f80(a0->slot1);
	if (!fcn_004f0ff0((char*) (g_slot_table + (unsigned int) g_774970 * 0x21c),
			slot0, slot1, a0->mode + 1, &o1, &o2)) {
		return 0;
	}
	fcn_004f11c0(a1, &spread, &scale);
	k = fcn_004f1290(a1);
	b = ((float*) 0x665288)[slot0 * 3 + 2];
	speed = (float) slot1 * g_662910
		* (k * ((float*) 0x665288)[slot0 * 3 + 1]
			- ((float*) 0x665288)[slot0 * 3])
		+ ((float*) 0x665288)[slot0 * 3];
	fcn_00589390();
	if (a0->mode == 0) {
		pos0.x = a0->dir1.x * *(float*) 0x662914 + a0->pos.x;
		pos0.y = a0->dir1.y * *(float*) 0x662914 + a0->pos.y;
		pos0.z = a0->dir1.z * *(float*) 0x662914 + a0->pos.z;
		fcn_005e8e80(&p0, &pos0, &a0->dir1, speed, b, *(float*) 0x6660f4);
		fcn_005e8fe0((float*) &p0, spread, &a0->dir2, spread, &a0->dir3,
			scale);
		h = fcn_004f0a30(a1,
			(char*) (g_slot_table + (unsigned int) g_774970 * 0x21c),
			(unsigned int*) &p0, 0, 0,
			fcn_004f0eb0(slot0, slot1, 1), o1, (unsigned int) o2);
		sel = 1;
	} else if (a0->mode == 1) {
		px = a0->dir1.x * *(float*) 0x662c98 + a0->pos.x;
		py = a0->dir1.y * *(float*) 0x662c98 + a0->pos.y;
		pz = a0->dir1.z * *(float*) 0x662c98 + a0->pos.z;
		pos1.x = a0->dir2.x * *(float*) 0x662a98 + px;
		pos1.y = a0->dir2.y * *(float*) 0x662a98 + py;
		pos1.z = a0->dir2.z * *(float*) 0x662a98 + pz;
		pos0.x = a0->dir2.x * *(float*) 0x664450 + px;
		pos0.y = a0->dir2.y * *(float*) 0x664450 + py;
		pos0.z = a0->dir2.z * *(float*) 0x664450 + pz;
		fcn_005e8e80(&p1, &pos1, &a0->dir1, speed, b, *(float*) 0x6660f4);
		fcn_005e8e80(&p0, &pos0, &a0->dir1, speed, b, *(float*) 0x6660f4);
		fcn_005e8fe0((float*) &p1, spread, &a0->dir2, spread, &a0->dir3,
			scale);
		fcn_005e8fe0((float*) &p0, spread, &a0->dir2, spread, &a0->dir3,
			scale);
		h = fcn_004f0a30(a1,
			(char*) (g_slot_table + (unsigned int) g_774970 * 0x21c),
			(unsigned int*) &p1, (unsigned int*) &p0, 0,
			fcn_004f0eb0(slot0, slot1, 1), o1, (unsigned int) o2);
		sel = 2;
		dx = -5;
		dy = 0;
		ey = 40;
	} else if (a0->mode == 2) {
		px = a0->dir1.x * *(float*) 0x662c98 + a0->pos.x;
		py = a0->dir1.y * *(float*) 0x662c98 + a0->pos.y;
		pz = a0->dir1.z * *(float*) 0x662c98 + a0->pos.z;
		pos2.x = a0->dir2.x * *(float*) 0x662a98
			+ a0->dir3.x * *(float*) 0x66444c + px;
		pos2.y = a0->dir2.y * *(float*) 0x662a98
			+ a0->dir3.y * *(float*) 0x66444c + py;
		pos2.z = a0->dir2.z * *(float*) 0x662a98
			+ a0->dir3.z * *(float*) 0x66444c + pz;
		pos0.x = a0->dir2.x * *(float*) 0x664450
			+ a0->dir3.x * *(float*) 0x66444c + px;
		pos0.y = a0->dir2.y * *(float*) 0x664450
			+ a0->dir3.y * *(float*) 0x66444c + py;
		pos0.z = a0->dir2.z * *(float*) 0x664450
			+ a0->dir3.z * *(float*) 0x66444c + pz;
		pos1.x = a0->dir3.x * *(float*) 0x662a98 + px;
		pos1.y = a0->dir3.y * *(float*) 0x662a98 + py;
		pos1.z = a0->dir3.z * *(float*) 0x662a98 + pz;
		fcn_005e8e80(&p2, &pos2, &a0->dir1, speed, b, *(float*) 0x6660f4);
		fcn_005e8e80(&p0, &pos0, &a0->dir1, speed, b, *(float*) 0x6660f4);
		fcn_005e8e80(&p1, &pos1, &a0->dir1, speed, b, *(float*) 0x6660f4);
		fcn_005e8fe0((float*) &p2, spread, &a0->dir2, spread, &a0->dir3,
			scale);
		fcn_005e8fe0((float*) &p0, spread, &a0->dir2, spread, &a0->dir3,
			scale);
		fcn_005e8fe0((float*) &p1, spread, &a0->dir2, spread, &a0->dir3,
			scale);
		h = fcn_004f0a30(a1,
			(char*) (g_slot_table + (unsigned int) g_774970 * 0x21c),
			(unsigned int*) &p2, (unsigned int*) &p0, (unsigned int*) &p1,
			fcn_004f0eb0(slot0, slot1, 1), o1, (unsigned int) o2);
		sel = 3;
		dx = -5;
		dy = -3;
		ex = 5;
		ey = 40;
		ez = 40;
	} else {
		return 0;
	}
	if (h != -1) {
		while (!fcn_004c4450(h)) {
			fcn_005373e0(0, 0x20007);
		}
	}
	if (sel == 3) {
		h = fcn_00426fd0("LOCATIONS\\DOMIZIL\\KANONE1.esc");
		h2 = fcn_00426fd0("LOCATIONS\\DOMIZIL\\KANONE1.esc");
		h3 = fcn_00426fd0("LOCATIONS\\DOMIZIL\\KANONE1.esc");
		fcn_00428340(h, 4, 5, 0, 40, a0->frame2);
		fcn_00428340(h2, 4, dx, dy, ey, a0->frame2);
		fcn_00428340(h3, 4, 0, ex, ez, a0->frame2);
		return fcn_004235b0(0, "Explosion", 1, 1, 0x3f, 0x7f, 0);
	}
	if (sel == 2) {
		h = fcn_00426fd0("LOCATIONS\\DOMIZIL\\KANONE1.esc");
		h2 = fcn_00426fd0("LOCATIONS\\DOMIZIL\\KANONE1.esc");
		fcn_00428340(h, 4, 5, 0, 40, a0->frame1);
		fcn_00428340(h2, 4, dx, dy, ey, a0->frame1);
		return fcn_004235b0(0, "Explosion", 2, 1, 0x3f, 0x7f, 0);
	}
	if (sel != 0) {
		h = fcn_00426fd0("LOCATIONS\\DOMIZIL\\KANONE1.esc");
		fcn_00428340(h, 4, 0, 0, 50, a0->frame0);
		return fcn_004235b0(0, "Explosion", 3, 1, 0x3f, 0x7f, 0);
	}
	return 0;
}
