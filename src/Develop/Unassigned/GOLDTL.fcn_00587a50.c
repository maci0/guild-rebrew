#include <math.h>

/* The effect node's world matrix sits at 0x18c; the three terms of each
   rotated component pick one matrix column out of it. */
struct node98 {
	char pad0[0x18c];
	float m[16];
};

extern float g_662d40[3];

extern void __cdecl fcn_00438cb0(void*, float*);
extern void __cdecl fcn_00438b40(void*, float*);
extern void __cdecl fcn_004518a0(float*);
extern float __cdecl fcn_004514d0(int, int);
extern void* __cdecl fcn_005e8850(void);
extern void __stdcall fcn_005ebbb9(float*, float*);
extern int __cdecl fcn_00471f80(int);
extern void __cdecl fcn_00587f40(char*);

/* ADDRESS: GOLDTL 0x00587a50 */
void __cdecl fcn_00587a50(char* o)
{
	float f;
	float d1;
	float z;
	int iv;
	float u;
	float s;
	float v[8];
	float m[16];
	void* c;
	int i;

	v[4] = 0.0f;
	v[5] = *(float*) (o + 0x14);
	v[6] = 0.0f;
	fcn_00438cb0(*(void**) (o + 0x98), v + 4);

	v[4] = *(float*) (o + 0x10);
	v[5] = 0.0f;
	v[6] = 0.0f;
	for (i = 0; i < 3; i++) {
		fcn_00438cb0(*(void**) (o + 0x8c + i * 4), v + 4);
	}

	v[4] = 0.0f;
	v[5] = 0.0f;
	v[6] = 0.0f;
	v[7] = 0.0f;

	c = fcn_005e8850();
	fcn_005ebbb9(m, ((struct node98*) *(void**) (o + 0x98))->m);
	v[2] = 0.0f;
	v[4] = 0.0f;
	v[3] = fcn_004514d0((int) g_662d40, (int) c) + 1.5707964f -
	       *(float*) (o + 0x14);
	fcn_00438cb0(*(void**) (o + 0x9c), v + 2);

	if (*(int*) (o + 0x7c) == 0) {
		fcn_00587f40(o);
	}

	v[0] = g_662d40[0] * ((struct node98*) *(void**) (o + 0x98))->m[0] +
	       g_662d40[1] * ((struct node98*) *(void**) (o + 0x98))->m[4] +
	       g_662d40[2] * ((struct node98*) *(void**) (o + 0x98))->m[8];
	v[1] = g_662d40[0] * ((struct node98*) *(void**) (o + 0x98))->m[1] +
	       g_662d40[1] * ((struct node98*) *(void**) (o + 0x98))->m[5] +
	       g_662d40[2] * ((struct node98*) *(void**) (o + 0x98))->m[9];
	v[2] = g_662d40[0] * ((struct node98*) *(void**) (o + 0x98))->m[2] +
	       g_662d40[1] * ((struct node98*) *(void**) (o + 0x98))->m[6] +
	       g_662d40[2] * ((struct node98*) *(void**) (o + 0x98))->m[10];
	fcn_004518a0(v);

	v[4] = *(float*) o - v[0] * 30.0f;
	v[5] = *(float*) (o + 4) - v[1] * 30.0f + 20.0f;
	v[6] = *(float*) (o + 8) - v[2] * 30.0f;
	v[0] = *(float*) (o + 0x10);
	v[1] = *(float*) (o + 0x14);
	v[2] = *(float*) (o + 0x18);

	d1 = (v[0] - -0.6108652f) / (0.7853982f - -0.6108652f);
	f = (v[0] - -0.2617994f) / (0.7853982f - -0.2617994f);
	iv = fcn_00471f80(*(int*) (o + 0xb4));
	u = (float) iv * 0.01f;
	s = (0.5f - 0.25f * u) * f * *(float*) (o + 0x20) + d1;
	s = s * 30.0f + v[5];
	u = 1.0f - *(float*) (o + 0x20);
	u = 0.3f * (float) sqrt(u) + 0.7f * u;
	u = u + (float) iv * 0.01f * *(float*) (o + 0x20) * 0.5f;
	v[0] = u * 0.6108652f * f + -0.6108652f;
	z = *(float*) (o + 0x2c);
	u = (float) iv * 0.01f * f * 0.5f + 1.0f;
	u = (u * 1450.0f * f + 50.0f) * *(float*) (o + 0x20);

	v[5] = u * *(float*) (o + 0x28) + s;
	v[4] = v[4] + u * *(float*) (o + 0x24);
	v[6] = v[6] + u * z;
	fcn_00438b40((void*) 0x6b8014, v + 4);
	fcn_00438cb0((void*) 0x6b8014, v);

	if (*(int*) (o + 0x7c) == 0) {
		fcn_00587f40(o);
		if (*(int*) (o + 0x7c) == 0) {
			goto tail;
		}
	}
	if (*(unsigned int*) (o + 0x78) + 0x54 > *(unsigned int*) (o + 0x6c)) {
		if (*(unsigned int*) (o + 0x78) + 4 > *(unsigned int*) (o + 0x6c)) {
			f = (float) (unsigned int) (*(unsigned int*) (o + 0x6c) -
						    *(unsigned int*) (o + 0x78)) *
			    0.25f;
		} else {
			u = 1.0f - (float) (unsigned int) (*(unsigned int*) (o + 0x6c) -
							   *(unsigned int*) (o + 0x78) - 4) *
					0.0125f;
			f = u * u;
		}
		v[1] = 0.0f;
		v[0] = *(float*) (o + 0x24);
		v[2] = *(float*) (o + 0x2c);
		fcn_004518a0(v);
		u = 1.0f;
		if (*(float*) (o + 0x10) > 0.0f) {
			u = 1.0f - *(float*) (o + 0x10) / 0.7853982f;
		}
		u = u * f * 50.0f;
		v[0] = *(float*) o - u * v[0];
		v[1] = *(float*) (o + 4) - u * v[1];
		v[2] = *(float*) (o + 8) - u * v[2];
		fcn_00438b40(*(void**) (o + 0x98), v);
		v[4] = -70.0f + u * g_662d40[0];
		v[5] = -50.0f + u * g_662d40[1];
		v[6] = 120.0f + u * g_662d40[2];
		fcn_00438b40(*(void**) (o + 0x9c), v + 4);
		return;
	}
	*(int*) (o + 0x7c) = 0;
	*(int*) (o + 0x78) = 0;
	fcn_00438b40(*(void**) (o + 0x9c), (float*) 0x665f28);
tail:
	fcn_00438b40(*(void**) (o + 0x98), (float*) o);
}
