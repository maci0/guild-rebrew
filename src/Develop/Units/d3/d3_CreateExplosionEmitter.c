#include <math.h>
#include <stdlib.h>

typedef struct {
	unsigned char a;
	unsigned char b;
	unsigned char c;
	unsigned char d;
} Bytes4;

typedef struct {
	float x;
	float y;
	float z;
	char pad0[0x14];
	int q;
	int pad1;
	char* particles;
	char pad2[0xac];
	int count;
} Explosion417d00;


int* __cdecl d3_CreateParticleSystem(int a0, char* a1, Bytes4 a2, float a3, char* a4, void (__cdecl* a5)(void));
void __cdecl d3_SetEffectPosition(int* a0, float* a1);
void __cdecl d3_UpdateExplosionParticles(void);

/* ADDRESS: GOLDTL 0x00417d00 */
/* ADDRESS: GOLDDE 0x00415b00 */
int* __cdecl d3_CreateExplosionEmitter(char* a0, float* pos, int n, float a3, float a4, float a5, float a6, int a7)
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
	s = (Explosion417d00*) d3_CreateParticleSystem(n, "Explosion", f, a6, a0, d3_UpdateExplosionParticles);
	if (s != 0) {
		count = s->count;
		n6 = count / 6;
		inv = 1.0f / (float) count;
		d3_SetEffectPosition((int*) s, pos);
		s->x = a3;
		s->y = a4;
		s->z = a5;
		s->q = a7;
		i = 0;
		if (s->count > 0) {
			v4 = (float*) (s->particles + 0x14);
			do {
				*(unsigned char*) ((char*) v4 + 0x3d) |= 1;
				v[0] = rand() * 3.0518509447574615e-05f;
				v[1] = rand() * 3.0518509447574615e-05f;
				v[2] = rand() * 3.0518509447574615e-05f;
				v[0] = v[0] * (s->y * 0.1f);
				v[1] = v[1] * (s->y * 0.1f);
				v[2] = (s->y * 0.1f) * v[2];
				v[0] = v[0] - s->y * 0.05f;
				v[1] = v[1] - s->y * 0.025f;
				v[2] = v[2] - s->y * 0.05f;
				rr = rand() * 1.9175345e-4f;
				h = (float) sin(((float) i * inv) * 1.5707964f) * s->y;
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
				i++;
				v4 += 0x15;
			} while (i < s->count);
		}
	}
	return (int*) s;
}
