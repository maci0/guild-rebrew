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

extern float g_662b08;
extern float g_662b0c;

int* __cdecl fcn_004524e0(int a0, char* a1, Bytes4 a2, float a3, char* a4, void (__cdecl* a5)(void));
void __cdecl fcn_004526d0(int* a0, float* a1);
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
				rr = rand() * g_662b0c;
				h = (float) sin(((float) i * inv) * g_662b08) * s->y;
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
