#include <math.h>


typedef struct {
	int o;
	int d;
	int x;
	int z;
} Ent4cf6b0;

extern int g_67a370;
extern int g_6b8300;
extern int g_772e9c;
extern int g_772ec4;

int __cdecl gm_LookupWeaponSpec(int a1);
int __cdecl fcn_00418000(int a1, float* v, int n, float f1, float f2,
    float f3, float f4, float f5, float f6, float* out, int a11, int a12,
    int a13);
int* __cdecl d3_SpawnRockDebrisEffect(int a1, float* pos, int n, float f1, float f2,
    float f3, float f4, float f5, float f6, float f7, float f8, int a12);
int __cdecl fcn_00417d00(int a1, float* v, int n, float f1, float f2,
    float f3, float f4, int a8);
int __cdecl sb_PlayVoice(char* bank, const char* name, int loop, int pan,
    int vol, int a, int b);
void __cdecl d3_GridPointToWorld(int g, int x, int z, float* out);
unsigned int __cdecl cut_RandMod(unsigned int n);
void __cdecl d3_ScheduleActionTimer(int a1, int a2, int a3);
int __cdecl fcn_004d4790(char* e);
int __cdecl ch_QueuePlayAnimation(char* e, const char* name, int param);
void __cdecl d3_DestroyObject(int p);
int __cdecl d3_BuildFloorGeometry(int m);
int __cdecl d3_UpdateFloorLighting(int m);

/* ADDRESS: GOLDTL 0x004cf6b0 */
int __cdecl fcn_004cf6b0(void)
{
	int count;
	int obj;
	float d;
	int world;
	int dmg;
	int dmg2;
	int n;
	int map;
	char* e;
	int other;
	Ent4cf6b0* p;
	int* q;
	float position[4];
	float v7[4];
	unsigned char color[4];

	world = *(int*) (((char*) g_67a370) + 0xb0);
	count = 0;
	obj = gm_LookupWeaponSpec(0x176);
	p = (Ent4cf6b0*) 0x9b9ec0;
	do {
		int p0;
		p0 = p->o;
		if (p0 != 0) {
			count++;
			if ((*(unsigned char*) (p->d + 0x2d) & 0x20) != 0) {
				position[0] = -243.0f;
				position[1] = -90.0f;
				position[2] = 190.0f;
				*(int*) &position[3] = 0;
				v7[0] = -50.0f;
				v7[1] = 0.0f;
				v7[2] = 38.0f;
				*(int*) &v7[3] = 0;
				position[0] = *(float*) (p0 + 0x4c);
				position[1] = *(float*) (p0 + 0x50);
				position[2] = *(float*) (p0 + 0x54);
				color[2] = 0xc0;
				color[1] = 0xc0;
				color[0] = 0xc0;
				color[3] = 0x3f;
				fcn_00418000(0, position, 0x1e, 15.0f, 50.0f, 100.0f, 150.0f,
				    140.0f, 35.0f, v7, 0x190, 6, *(int*) color);
				d3_SpawnRockDebrisEffect(0, position, 0x1e, 5.0f, 2.5f, 1.0f, 3.0f, -3.0f,
				    4.0f, 7.0f, 8.0f, *(int*) color);
				fcn_00417d00(0, position, 0x1e, 70.0f, 50.0f, 20.0f, 60.0f,
				    0x3c);
				map = g_6b8300;
				n = p->x + p->z * *(int*) map;
				if (*(unsigned char*) (n + *(int*) (map + 0x14)) != 0) {
					*(unsigned char*) (n + *(int*) (map + 0x10)) += 0xfb;
					*(unsigned char*) (p->z * *(int*) g_6b8300 + *(int*) (g_6b8300 + 0x14) + p->x) = 0;
					d3_BuildFloorGeometry(g_6b8300);
					d3_UpdateFloorLighting(g_6b8300);
				}
				sb_PlayVoice((char*) g_772ec4, "Explosion_s", 1, 0x3f,
				    0x7f, 0, 0);
				q = (int*) 0x7e4260;
				do {
					e = (char*) *q;
					if (e != 0) {
						other = *(int*) (e + 0x184);
						if (e[8] != 0) {
							d3_GridPointToWorld(world, p->x, p->z, position);
							position[0] -= *(float*) (*(int*) (other + 0x34) + 0x4c);
							position[1] -= *(float*) (*(int*) (other + 0x34) + 0x50);
							position[2] -= *(float*) (*(int*) (other + 0x34) + 0x54);
							d = (float) sqrt(position[2] * position[2] + position[1] * position[1] + position[0] * position[0]);
							if (d < 100.0f) {
								n = (int) cut_RandMod((unsigned int) ((unsigned char) ((char*) obj)[6] - (unsigned char) ((char*) obj)[5]));
								dmg = (int) ((double) (unsigned int) (n + (unsigned char) ((char*) obj)[5]) * (*(float*) (e + 0x1c) * 0.01));
								dmg2 = (int) ((double) dmg * (1.0 - d * 0.01f));
								*(int*) (*(char**) q + 0x24) -= dmg2;
								if (*(int*) (*(char**) q + 0x16c) == g_772e9c) {
									d3_ScheduleActionTimer(*q, dmg2, 1);
								} else {
									d3_ScheduleActionTimer(*q, dmg2, 2);
								}
								if (!fcn_004d4790(e)) {
									ch_QueuePlayAnimation((char*) other, "kampf/arm_greifen", 1);
								}
							}
						}
					}
					q++;
				} while ((int) q < 0x7e42e0);
				d3_DestroyObject(p->o);
				p->o = 0;
			}
		}
		p++;
	} while ((int) p < 0x9ba0c0);
	return count;
}
