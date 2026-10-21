/* Initialises an "Explosion" particle system: stores the caller's position
 * and origin values, then seeds and transforms every particle in the ring. */

#include <stdlib.h>
#include <string.h>
#include <math.h>

/* SIZE 0x4 */
typedef struct {
	unsigned char a;
	unsigned char b;
	unsigned char c;
	unsigned char d;
} Bytes4;

/* SIZE 0xdc */
typedef struct {
	float x;
	float y;
	float z;
	char pad0c[0x14];
	float q;
	char pad24[4];
	char* particles;
	char pad2c[0xac];
	int count;
} Explosion417d00;

extern float g_6628a0;
extern float g_6628d8;
extern float g_6629d0;
extern float g_662a18;
extern float g_662a3c;
extern float g_662a74;
extern float g_662b08;
extern float g_662b0c;
extern float g_662b10;

int* __cdecl fcn_004524e0(int n, const char* name, Bytes4 f, int a, char* e, void (__cdecl* cb)(void));
void __cdecl fcn_004526d0(int* s, float* pos);
void __cdecl fcn_00417bf0(void);

/* ADDRESS: GOLDTL 0x00417d00 */
int* __cdecl fcn_00417d00(char* a0, float* pos, int n, float a3, float a4, float a5, int a6, float a7)
{
	Bytes4 f;
	Explosion417d00* s;
	float* v4;
	float v[4];
	float h;
	float inv;
	float rr;
	float c;
	int count;
	int n6;
	int i;

	memset(&f, 0, sizeof(f));
	f.c |= 1;
	f.a = 0xff;
	s = (Explosion417d00*) fcn_004524e0(n, "Explosion", f, a6, a0, fcn_00417bf0);
	if (s == 0) {
		return (int*) s;
	}
	count = s->count;
	n6 = count / 6;
	inv = g_6628a0 / (float) count;
	fcn_004526d0((int*) s, pos);
	s->x = a3;
	s->y = a4;
	s->z = a5;
	s->q = a7;
	for (i = 0; i < s->count; i++) {
		v4 = (float*) (s->particles + 0x14 + i * 0x54);
		*(unsigned char*) ((char*) v4 + 0x3d) |= 1;
		v[1] = rand() * g_662a18;
		v[2] = rand() * g_662a18;
		v[3] = rand() * g_662a18;
		v[1] = v[1] * (s->y * g_662a3c) - (s->y * g_662b10);
		v[2] = v[2] * (s->y * g_662a3c) - (s->y * g_662a74);
		v[3] = (s->y * g_662a3c) * v[3] - (s->y * g_662b10);
		rr = rand() * g_662b0c;
		h = (float) sin((float) i * inv * g_662b08) * s->y;
		*v4 = h;
		h = (float) sqrt(s->x * s->x - h * h);
		c = (float) sin(rr) * h + v[1];
		v4[-1] = c;
		v[2] = v[2] + *v4;
		*v4 = v[2];
		v4[1] = (float) cos(rr) * h + v[3];
		if (i % n6 == 0) {
			v4[-1] = c * g_6628d8;
			*v4 = v[2] * g_6629d0;
			v4[1] = v4[1] * g_6628d8;
		}
	}
	return (int*) s;
}
