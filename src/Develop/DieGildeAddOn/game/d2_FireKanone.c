typedef struct { float f00, f04, f08; } CANNON_ROW_588AA0;
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

#include "Develop/DieGildeAddOn/game/game_data.h"
extern float g_662914, g_662c98, g_662a98, g_664450, g_66444c, g_6660f4;
#include "Develop/DieGildeAddOn/game/game_player.h"
extern unsigned char g_slot_table[2];

int __cdecl d2_GetControlValue(int slot);
int __cdecl gm_CanFireCannonShot(char* a0, int a1, int a2, int a3, int* o1, int* o2);
void __cdecl gm_CalcArtillerySpread(char* p, float* o1, float* o2);
float __cdecl gm_GetCannonPowerScale(char* p);
int __cdecl gm_SendCannonVolleys(char* a0, char* a1, unsigned int* a2,
	unsigned int* a3, unsigned int* a4, float a5, int a6, unsigned int a7);
float __cdecl gm_CalcArtilleryVolleyCost(int level, int percent, int count);
int __cdecl d3_SpawnPhysicsParticle(Particle* o, Vec3* pos, Vec3* dir, float speed,
	float b, float a);
int __cdecl d3_PerturbParticleVelocity(float* p, float spread, float* dir, float lift,
	float* up, float scale);
int __cdecl cm_GetCommandStatus(int i);
int __cdecl main_RunFrameLoop(int a, int b);
int __cdecl evt_LoadGfxScript(const char* name);
int __cdecl evt_CallScriptFunction(int h, int a, int b, int c, int d, int e);
int __cdecl sb_PlayPrioritizedVoice(char* bank, const char* name, int prio, int loop,
	int pan, int vol, int a);
void __cdecl d2_ResetKanoneHitTable(void);

/* ADDRESS: GOLDTL 0x00588aa0 */
int __cdecl d2_FireKanone(Emitter* emitter, char* building)
{
	Particle p0;
	Particle p1;
	Particle p2;
	Vec3 pos0; Vec3 dir1; Vec3 dir2; Vec3 dir3;
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
	slot0 = d2_GetControlValue(emitter->slot0);
	slot1 = d2_GetControlValue(emitter->slot1);
	if (!gm_CanFireCannonShot((char*) (g_slot_table + (unsigned int) g_774970 * 0x21c),
			slot0, slot1, emitter->mode + 1, &o1, &o2)) {
		return 0;
	}
	gm_CalcArtillerySpread(building, &spread, &scale);
	k = gm_GetCannonPowerScale(building);
	b = ((CANNON_ROW_588AA0*)0x665288)[slot0].f08;
	speed = (k * ((CANNON_ROW_588AA0*)0x665288)[slot0].f04
			- ((CANNON_ROW_588AA0*)0x665288)[slot0].f00)
		* ((float) slot1 * 0.01f)
		+ ((CANNON_ROW_588AA0*)0x665288)[slot0].f00;
	d2_ResetKanoneHitTable();
	dir1 = emitter->dir1; dir2 = emitter->dir2; dir3 = emitter->dir3;
	if (emitter->mode == 0) {
		pos0.x = dir1.x * 50.0f; pos0.y = dir1.y * 50.0f; pos0.z = dir1.z * 50.0f;
		pos0.x += emitter->pos.x; pos0.y += emitter->pos.y;
		pos0.z += emitter->pos.z;
		d3_SpawnPhysicsParticle(&p0, &pos0, &emitter->dir1, speed, b, 7874.0f);
		d3_PerturbParticleVelocity((float*) &p0, spread, &emitter->dir2, spread, &emitter->dir3,
			scale);
		h = gm_SendCannonVolleys(building,
			(char*) (g_slot_table + (unsigned int) g_774970 * 0x21c),
			(unsigned int*) &p0, 0, 0,
			gm_CalcArtilleryVolleyCost(slot0, slot1, 1), o1, (unsigned int) o2);
		sel = 1;
	} else if (emitter->mode == 1) {
		px = dir1.x * 40.0f + emitter->pos.x;
		py = dir1.y * 40.0f + emitter->pos.y;
		pz = dir1.z * 40.0f + emitter->pos.z;
		pos1.x = dir2.x * 5.0f + px;
		pos1.y = dir2.y * 5.0f + py;
		pos1.z = dir2.z * 5.0f + pz;
		pos0.x = dir2.x * (-5.0f) + px;
		pos0.y = dir2.y * (-5.0f) + py;
		pos0.z = dir2.z * (-5.0f) + pz;
		d3_SpawnPhysicsParticle(&p1, &pos1, &emitter->dir1, speed, b, 7874.0f);
		d3_SpawnPhysicsParticle(&p0, &pos0, &emitter->dir1, speed, b, 7874.0f);
		d3_PerturbParticleVelocity((float*) &p1, spread, &emitter->dir2, spread, &emitter->dir3,
			scale);
		d3_PerturbParticleVelocity((float*) &p0, spread, &emitter->dir2, spread, &emitter->dir3,
			scale);
		h = gm_SendCannonVolleys(building,
			(char*) (g_slot_table + (unsigned int) g_774970 * 0x21c),
			(unsigned int*) &p1, (unsigned int*) &p0, 0,
			gm_CalcArtilleryVolleyCost(slot0, slot1, 1), o1, (unsigned int) o2);
		sel = 2;
		dx = -5;
		dy = 0;
		ey = 40;
	} else if (emitter->mode == 2) {
		px = dir1.x * 40.0f + emitter->pos.x;
		py = dir1.y * 40.0f + emitter->pos.y;
		pz = dir1.z * 40.0f + emitter->pos.z;
		pos2.x = dir2.x * 5.0f
			+ dir3.x * (-3.0f) + px;
		pos2.y = dir2.y * 5.0f
			+ dir3.y * (-3.0f) + py;
		pos2.z = dir2.z * 5.0f
			+ dir3.z * (-3.0f) + pz;
		pos1.x = dir3.x * 5.0f + px;
		pos1.y = dir3.y * 5.0f + py;
		pos1.z = dir3.z * 5.0f + pz;
		pos0.x = dir2.x * (-5.0f)
			+ dir3.x * (-3.0f) + px;
		pos0.y = dir2.y * (-5.0f)
			+ dir3.y * (-3.0f) + py;
		pos0.z = dir2.z * (-5.0f)
			+ dir3.z * (-3.0f) + pz;
		d3_SpawnPhysicsParticle(&p2, &pos2, &emitter->dir1, speed, b, 7874.0f);
		d3_SpawnPhysicsParticle(&p0, &pos0, &emitter->dir1, speed, b, 7874.0f);
		d3_SpawnPhysicsParticle(&p1, &pos1, &emitter->dir1, speed, b, 7874.0f);
		d3_PerturbParticleVelocity((float*) &p2, spread, &emitter->dir2, spread, &emitter->dir3,
			scale);
		d3_PerturbParticleVelocity((float*) &p0, spread, &emitter->dir2, spread, &emitter->dir3,
			scale);
		d3_PerturbParticleVelocity((float*) &p1, spread, &emitter->dir2, spread, &emitter->dir3,
			scale);
		h = gm_SendCannonVolleys(building,
			(char*) (g_slot_table + (unsigned int) g_774970 * 0x21c),
			(unsigned int*) &p2, (unsigned int*) &p0, (unsigned int*) &p1,
			gm_CalcArtilleryVolleyCost(slot0, slot1, 1), o1, (unsigned int) o2);
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
		while (!cm_GetCommandStatus(h)) {
			main_RunFrameLoop(0, 0x20007);
		}
	}
	if (sel == 0) {
		return 0;
	}
	if (sel == 3) {
		h = evt_LoadGfxScript("LOCATIONS\\DOMIZIL\\KANONE1.esc");
		h2 = evt_LoadGfxScript("LOCATIONS\\DOMIZIL\\KANONE1.esc");
		h3 = evt_LoadGfxScript("LOCATIONS\\DOMIZIL\\KANONE1.esc");
		evt_CallScriptFunction(h, 4, 5, dy, 40, emitter->frame2);
		evt_CallScriptFunction(h2, 4, dx, dy, ey, emitter->frame2);
		evt_CallScriptFunction(h3, 4, 0, ex, ez, emitter->frame2);
		return sb_PlayPrioritizedVoice(0, "Explosion", 1, 1, 0x3f, 0x7f, 0);
	}
	if (sel == 2) {
		h = evt_LoadGfxScript("LOCATIONS\\DOMIZIL\\KANONE1.esc");
		h2 = evt_LoadGfxScript("LOCATIONS\\DOMIZIL\\KANONE1.esc");
		evt_CallScriptFunction(h, 4, 5, 0, 40, emitter->frame1);
		evt_CallScriptFunction(h2, 4, dx, dy, ey, emitter->frame1);
		return sb_PlayPrioritizedVoice(0, "Explosion", 2, 1, 0x3f, 0x7f, 0);
	}
	h = evt_LoadGfxScript("LOCATIONS\\DOMIZIL\\KANONE1.esc");
	evt_CallScriptFunction(h, 4, 0, 0, 50, emitter->frame0);
	return sb_PlayPrioritizedVoice(0, "Explosion", 3, 1, 0x3f, 0x7f, 0);
}
