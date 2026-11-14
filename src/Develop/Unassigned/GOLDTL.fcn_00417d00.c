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
	unsigned int q;
	char pad24[4];
	char* particles;
	char pad2c[0xac];
	int count;
} Explosion417d00;

extern float g_662a18;
extern float g_662b08;
extern float g_662b0c;

int* __cdecl fcn_004524e0(int n, const char* name, Bytes4 f, float a, char* e, void (__cdecl* cb)(void));
void __cdecl fcn_004526d0(int* s, float* pos);
void __cdecl fcn_00417bf0(void);

/* ADDRESS: GOLDTL 0x00417d00 */
int* __cdecl fcn_00417d00(char* a0, float* pos, int n, float a3, float a4, float a5, float a6, int a7)
{
	Bytes4 f;
	Explosion417d00* s;
	float* v4;
	float v[4];
	float h;
	float inv;
	float rr;

	int count;
	int n6;
	int i;

	memset(&f, 0, sizeof(f));
	f.c |= 1;
	f.a = 0xff;
	s = (Explosion417d00*) fcn_004524e0(n, "Explosion", f, a6, a0, fcn_00417bf0);
	if (s != 0) {
		count = s->count;
		n6 = count / 6;
		inv = 1.0f / (float) count;
		fcn_004526d0((int*) s, pos);
		s->x = a3;
		s->y = a4;
		s->q = a7;
		s->z = a5;
		for (i = 0, v4 = (float*) (s->particles + 0x14); i < s->count; i++, v4 += 0x15) {
			*(unsigned char*) ((char*) v4 + 0x3d) |= 1;
			v[0] = rand() * g_662a18;
			v[1] = rand() * g_662a18;
			v[2] = rand() * g_662a18;
		v[0] = v[0] * (s->y * 0.1f);
		v[1] = v[1] * (s->y * 0.1f);
		v[2] = (s->y * 0.1f) * v[2];
		v[0] = v[0] - s->y * 0.05f;
		v[1] = v[1] - s->y * 0.025f;
		v[2] = v[2] - s->y * 0.05f;
			rr = rand() * g_662b0c;
			h = (float) sin((float) i * inv * g_662b08) * s->y;
			*v4 = h;
			h = (float) sqrt(s->x * s->x - h * h);
			v4[-1] = (float) sin(rr) * h + v[0];

			*v4 = v[1] + *v4;

			v4[1] = (float) cos(rr) * h + v[2];
			if (i % n6 == 0) {
				v4[-1] = v4[-1] * 0.4f;
				*v4 = *v4 * 0.2f;
				v4[1] = v4[1] * 0.4f;
			}
		}
	}
	return (int*) s;
}
