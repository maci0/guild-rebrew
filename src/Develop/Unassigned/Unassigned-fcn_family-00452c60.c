#include <math.h>

#define GOLDTL_MIN(a, b) ((a) < (b) ? (a) : (b))
#define GOLDTL_MAX(a, b) ((a) > (b) ? (a) : (b))

int __cdecl rand(void);
void __cdecl fcn_004518a0(float* v);

typedef struct fcn_00452c60_Particle {
	float f00;
	float f04;
	float f08;
	float f0c;
	float f10;
	float f14;
	float f18;
	float f1c;
	float f20;
	float f24;
	float f28;
	float f2c;
	unsigned int f30;
	unsigned int f34;
	float f38;
	float f3c;
	float f40;
	float f44;
	float f48;
	char f4c;
	char f4d;
	char f4e;
	char f4f;
	char f50;
	char flags;
	char pad52[2];
} fcn_00452c60_Particle; 

typedef struct fcn_00452c60_Emitter {
	char pad00[0x20];
	int f20;
	int f24;
	fcn_00452c60_Particle* particles;
	char pad2c[0x0c];
	float f38;
	float f3c;
	float f40;
	char pad44[4];
	float f48;
	float f4c;
	float f50;
	float f54;
	float f58;
	float f5c;
	float f60;
	float f64;
	float f68;
	float f6c;
	char pad70[4];
	float f74;
	float f78;
	float f7c;
	float f80;
	float f84;
	float f88;
	float f8c;
	float f90;
	float f94;
	float f98;
	float f9c;
	float fa0;
	float fa4;
	float fa8;
	float fac;
	float fb0;
	float fb4;
	float fb8;
	float fbc;
	float fc0;
	int c4;
	int c8;
	int cc;
	char d0;
	char d1;
	char d2;
	char d3;
	char d4;
	char d5;
	char padD6[2];
	int count;
	void* sub;
	char padE0[4];
	float fe4;
} fcn_00452c60_Emitter;

typedef struct fcn_00452c60_Sub {
	char pad00[0x5c];
	unsigned char n;
} fcn_00452c60_Sub;

#pragma data_seg(".text")
#include <stdlib.h>

#define STRIDE_453470 0x54
#define RAND_UNIT_453470 (*(float*) 0x662a18)
#define TWO_PI_F_453470 (*(float*) 0x6628c8)

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

void __cdecl fcn_004518a0(float* v);

#pragma data_seg(".text")

/* ADDRESS: GOLDTL 0x00452c60 */
unsigned char __cdecl fcn_00452c60(fcn_00452c60_Emitter* e, unsigned int t)
{
	fcn_00452c60_Particle* p;
	int cnt;
	int den;
	int i;
	int lim;
	int age;
	float len;
	float dt;
	float r;
	float lo;
	float hi;
	float v[4];
	float w;

	den = 1;
	if (e->f24 == t)
		return 1;
	w = (float) sqrt(e->f74 * e->f74 + e->f78 * e->f78 + e->f7c * e->f7c);
	len = w;
	if (e->f68 > e->f6c)
		len = -len;
	lim = (e->d4 & 0x80) ? (int) (e->count * e->fb4) : e->count;
	if (e->sub != 0 && ((fcn_00452c60_Sub*) e->sub)->n > 0)
		den = ((fcn_00452c60_Sub*) e->sub)->n;
	e->f38 = 1.0f / e->c4;
	e->f3c = 1.0f / (e->cc - e->c8);
	e->f40 = 1.0f / (float) fabs(e->f6c - e->f68);
	p = e->particles;
	cnt = 0;
	for (i = 0; i < e->count; i++, p++) {
		if (!(p->flags & 1)) {
			if (cnt >= lim)
				continue;
			if ((e->d4 & 0x80) && !(e->d5 & 2))
				continue;
			cnt++;
			p->f10 = (float) rand() * *(float*) 0x662a18 * *(float*) 0x6628c8;
			p->f14 = (float) rand() * *(float*) 0x662a18 * *(float*) 0x6628c8;
			p->f18 = (float) rand() * *(float*) 0x662a18 * *(float*) 0x6628c8;
			p->f1c = (float) rand() * *(float*) 0x662a18 * *(float*) 0x6628c8;
			p->f0c = (float) rand() * *(float*) 0x662a18 * *(float*) 0x6628c8;
			p->f50 = (char) (i % den);
			p->f4e = (char) ((rand() & e->d3) + e->d2);
			p->f4d = (char) ((rand() & e->d3) + e->d1);
			p->f4c = (char) ((rand() & e->d3) + e->d0);
			p->f4f = 0;
			p->f30 = t;
			v[0] = (float) rand() * *(float*) 0x662a18 - *(float*) 0x6628cc;
			v[1] = (float) rand() * *(float*) 0x662a18 - *(float*) 0x6628cc;
			v[2] = (float) rand() * *(float*) 0x662a18 - *(float*) 0x6628cc;
			fcn_004518a0(v);
			if (!(e->d4 & 0x60)) {
				p->f34 = t;
				p->f20 = v[0] * (e->f68 * 1.0f);
				p->f24 = v[1] * (e->f68 * 1.0f);
				p->f28 = v[2] * (e->f68 * 1.0f);
			} else {
				r = (float) rand() * *(float*) 0x662a18;
				p->f34 = (int) ((double) t - e->cc * r);
				lo = GOLDTL_MIN(e->f68, e->f6c);
				hi = GOLDTL_MAX(e->f68, e->f6c);
				r = lo + (hi - lo) * r;
				p->f20 = v[0] * r;
				p->f24 = v[1] * r;
				p->f28 = v[2] * r;
			}
			p->f00 = v[0] * len;
			p->f04 = v[1] * len;
			p->f08 = v[2] * len;
			v[0] = (float) rand() * *(float*) 0x662a18;
			v[1] = (float) rand() * *(float*) 0x662a18;
			v[2] = (float) rand() * *(float*) 0x662a18;
			v[0] *= e->f8c;
			v[1] *= e->f90;
			v[2] *= e->f94;
			p->f00 += v[0];
			p->f04 += v[1];
			p->f08 += v[2];
			v[0] = (float) sin(p->f10);
			v[1] = (float) sin(p->f14);
			v[2] = (float) sin(p->f18);
			v[3] = (float) sin(p->f1c);
			p->f38 = v[0] * e->f48 + p->f20;
			p->f3c = v[1] * e->f4c + p->f24;
			p->f40 = v[2] * e->f50 + p->f28;
			p->f48 = v[3] * e->f54 + e->fe4;
			p->flags = p->flags | 1;
		} else {
			unsigned int d;

			d = t - p->f30;
			dt = (float) d;
			if (dt > 150.0f) {
				p->f34 += t - p->f30;
				dt = 0.0f;
			}
			age = (int) (t - p->f34);
			p->f30 = t;
			if (e->d4 & 0x1f)
				p->f50 = (char) ((age / (e->d4 & 0x1f)) % den);
			p->f10 += dt * e->f58;
			p->f14 += dt * e->f5c;
			p->f18 += dt * e->f60;
			p->f1c += dt * e->f64;
			p->f10 = (float) fmod(p->f10, 6.283185307179586);
			p->f14 = (float) fmod(p->f14, 6.283185307179586);
			p->f18 = (float) fmod(p->f18, 6.283185307179586);
			p->f1c = (float) fmod(p->f1c, 6.283185307179586);
			p->f0c = (float) fmod(p->f0c + dt * e->fbc, 6.283185307179586);
			p->f00 += dt * e->f98;
			p->f04 += dt * e->f9c;
			p->f08 += dt * e->fa0;
			v[0] = e->f80 + p->f00;
			v[1] = e->f84 + p->f04;
			v[2] = e->f88 + p->f08;
			p->f20 += dt * v[0];
			p->f24 += dt * v[1];
			p->f28 += dt * v[2];
			v[0] = (float) sin(p->f10);
			v[1] = (float) sin(p->f14);
			v[2] = (float) sin(p->f18);
			v[3] = (float) sin(p->f1c);
			p->f38 = v[0] * e->f48 + p->f20;
			p->f3c = v[1] * e->f4c + p->f24;
			p->f40 = v[2] * e->f50 + p->f28;
			p->f48 = v[3] * e->f54 + e->fe4;
			p->f44 = (float) sin(p->f0c) * e->fb8 + e->fc0;
			if ((e->fb0 < *(float*) 0x6628a8 && p->f40 < e->fb0) ||
			    (e->fb0 > *(float*) 0x6628a8 && p->f40 > e->fb0)) {
				p->f40 = e->fb0;
				p->f00 *= e->fa4;
				p->f04 *= e->fa8;
				p->f08 *= e->fac;
			}
			if (age < e->c4) {
				p->f4f = (char) GOLDTL_MAX(0.0f, GOLDTL_MIN(255.0f,
					(1.0f - (float) (e->c4 - age) * e->f38) * p->f44));
			} else if (age < e->c8) {
				p->f4f = (char) GOLDTL_MAX(0.0f, GOLDTL_MIN(255.0f,
					p->f44));
			} else if (age < e->cc) {
				r = (float) (e->cc - age) * p->f44;
				p->f4f = (char) GOLDTL_MAX(0.0f, GOLDTL_MIN(255.0f,
					r * e->f3c));
			} else {
				p->flags = p->flags & 0xfe;
				e->f20++;
			}
		}
	}
	if (e->d4 & 0x20)
		e->d4 = e->d4 & 0xdf;
	if (e->d5 & 2)
		e->d5 = e->d5 & 0xfd;
	e->f24 = t;
	return ((e->d5 & 1) && e->f20 >= lim) ? 0 : 1;
}

/* Emitter update, drift variant: spawn random-angle particles aimed along a
   random direction, integrate live slots by the elapsed time, fade and retire
   expired slots. Returns 0 once the slot budget is filled. */
/* ADDRESS: GOLDTL 0x00453470 */
char __cdecl fcn_00453470(void* a1, unsigned int a2)
{
	char* e;
	char* p;
	int n;
	int cnt;
	int i;
	int wanted;
	int age;
	float dt;
	float len;
	float r;
	float t;
	float v[4];

	e = (char*) a1;
	cnt = 1;
	if (*(int*) (e + 0x24) == a2) {
		return 1;
	}
	t = sqrt(*(float*) (e + 0x74) * *(float*) (e + 0x74) +
		*(float*) (e + 0x78) * *(float*) (e + 0x78) +
		*(float*) (e + 0x7c) * *(float*) (e + 0x7c));
	len = (float) t;
	if (*(unsigned char*) (e + 0xd4) & 0x80) {
		wanted = (int) ((float) *(int*) (e + 0xd8) * *(float*) (e + 0xb4));
	} else {
		wanted = *(int*) (e + 0xd8);
	}
	if (*(int*) (e + 0xdc) != 0 &&
		*(unsigned char*) (*(int*) (e + 0xdc) + 0x5c) > 0) {
		cnt = *(unsigned char*) (*(int*) (e + 0xdc) + 0x5c);
	}
	*(float*) (e + 0x38) = 1.0f / (float) *(int*) (e + 0xc4);
	*(float*) (e + 0x3c) = 1.0f /
		(float) (*(int*) (e + 0xcc) - *(int*) (e + 0xc8));
	*(float*) (e + 0x40) = 1.0f / *(float*) (e + 0x70);
	*(float*) (e + 0x44) = *(float*) (e + 0x6c) / *(float*) (e + 0x68);
	p = *(char**) (e + 0x28);
	n = 0;
	for (i = 0; i < *(int*) (e + 0xd8); i++, p += STRIDE_453470) {
		if (!(*(unsigned char*) (p + 0x51) & 1)) {
			if (n >= wanted) {
				continue;
			}
			if (*(unsigned char*) (e + 0xd4) & 0x80 &&
				!(*(unsigned char*) (e + 0xd5) & 2)) {
				continue;
			}
			n++;
			*(float*) (p + 0x10) = (float) rand() * RAND_UNIT_453470 *
				TWO_PI_F_453470;
			*(float*) (p + 0x14) = (float) rand() * RAND_UNIT_453470 *
				TWO_PI_F_453470;
			*(float*) (p + 0x18) = (float) rand() * RAND_UNIT_453470 *
				TWO_PI_F_453470;
			*(float*) (p + 0x1c) = (float) rand() * RAND_UNIT_453470 *
				TWO_PI_F_453470;
			*(float*) (p + 0x0c) = (float) rand() * RAND_UNIT_453470 *
				TWO_PI_F_453470;
			*(unsigned char*) (p + 0x50) = (unsigned char) (i % cnt);
			*(unsigned char*) (p + 0x4e) = (unsigned char) (rand() &
				*(unsigned char*) (e + 0xd3)) +
				*(unsigned char*) (e + 0xd2);
			*(unsigned char*) (p + 0x4d) = (unsigned char) (rand() &
				*(unsigned char*) (e + 0xd3)) +
				*(unsigned char*) (e + 0xd1);
			*(unsigned char*) (p + 0x4c) = (unsigned char) (rand() &
				*(unsigned char*) (e + 0xd3)) +
				*(unsigned char*) (e + 0xd0);
			*(unsigned char*) (p + 0x4f) = 0;
			*(unsigned int*) (p + 0x30) = a2;
			v[0] = (float) rand() * RAND_UNIT_453470 - *(float*) 0x6628cc;
			v[1] = (float) rand() * RAND_UNIT_453470 - *(float*) 0x6628cc;
			v[2] = 0.0f;
			fcn_004518a0(v);
			if (!(*(unsigned char*) (e + 0xd4) & 0x60)) {
				*(unsigned int*) (p + 0x34) = a2;
				r = (float) rand() * RAND_UNIT_453470 *
					*(float*) (e + 0x68);
				*(float*) (p + 0x20) = v[0] * r;
				*(float*) (p + 0x24) = v[1] * r;
				*(float*) (p + 0x28) = v[2] * r;
				if (*(float*) (e + 0x68) != *(float*) 0x6628a8) {
					r = r * *(float*) (e + 0x44);
				} else {
					*(float*) (p + 0x20) = 0.0f;
					*(float*) (p + 0x24) = 0.0f;
					*(float*) (p + 0x28) = 0.0f;
					r = (float) rand() * RAND_UNIT_453470 *
						*(float*) (e + 0x6c);
				}
				v[0] = v[0] * r;
				v[1] = v[1] * r;
				v[2] = *(float*) (e + 0x70);
				v[0] -= *(float*) (p + 0x20);
				v[1] -= *(float*) (p + 0x24);
				v[2] -= *(float*) (p + 0x28);
				fcn_004518a0(v);
			} else {
				if (*(float*) (e + 0x68) != *(float*) 0x6628a8) {
					r = (float) rand() * RAND_UNIT_453470 *
						*(float*) (e + 0x68);
					*(float*) (p + 0x20) = v[0] * r;
					*(float*) (p + 0x24) = v[1] * r;
					*(float*) (p + 0x28) = v[2] * r;
					r = r * *(float*) (e + 0x44);
				} else {
					*(float*) (p + 0x20) = 0.0f;
					*(float*) (p + 0x24) = 0.0f;
					*(float*) (p + 0x28) = 0.0f;
					r = (float) rand() * RAND_UNIT_453470 *
						*(float*) (e + 0x6c);
				}
				v[0] = v[0] * r;
				v[1] = v[1] * r;
				v[2] = *(float*) (e + 0x70);
				v[0] -= *(float*) (p + 0x20);
				v[1] -= *(float*) (p + 0x24);
				v[2] -= *(float*) (p + 0x28);
				fcn_004518a0(v);
				r = (float) rand() * RAND_UNIT_453470;
				*(int*) (p + 0x34) = (int) ((double) a2 -
					(float) *(int*) (e + 0xcc) * r);
				r = r * *(float*) (e + 0x70);
				*(float*) (p + 0x20) += v[0] * r;
				*(float*) (p + 0x24) += v[1] * r;
				*(float*) (p + 0x28) += v[2] * r;
			}
			*(float*) (p) = v[0] * len;
			*(float*) (p + 4) = v[1] * len;
			*(float*) (p + 8) = v[2] * len;
			v[0] = (float) rand() * RAND_UNIT_453470;
			v[1] = (float) rand() * RAND_UNIT_453470;
			v[2] = (float) rand() * RAND_UNIT_453470;
			v[0] *= *(float*) (e + 0x8c);
			v[1] *= *(float*) (e + 0x90);
			v[2] *= *(float*) (e + 0x94);
			*(float*) (p) += v[0];
			*(float*) (p + 4) += v[1];
			*(float*) (p + 8) += v[2];
			v[0] = (float) sin(*(float*) (p + 0x10));
			v[1] = (float) sin(*(float*) (p + 0x14));
			v[2] = (float) sin(*(float*) (p + 0x18));
			v[3] = (float) sin(*(float*) (p + 0x1c));
			*(float*) (p + 0x38) = v[0] * *(float*) (e + 0x48) +
				*(float*) (p + 0x20);
			*(float*) (p + 0x3c) = v[1] * *(float*) (e + 0x4c) +
				*(float*) (p + 0x24);
			*(float*) (p + 0x40) = v[2] * *(float*) (e + 0x50) +
				*(float*) (p + 0x28);
			*(float*) (p + 0x48) = v[3] * *(float*) (e + 0x54) +
				*(float*) (e + 0xe4);
			*(unsigned char*) (p + 0x51) |= 1;
		} else {
			unsigned int d;

			d = a2 - *(unsigned int*) (p + 0x30);
			dt = (float) d;
			if (dt > 150.0f) {
				*(unsigned int*) (p + 0x34) +=
					a2 - *(unsigned int*) (p + 0x30);
				dt = 0.0f;
			}
			age = (int) (a2 - *(unsigned int*) (p + 0x34));
			*(unsigned int*) (p + 0x30) = a2;
			if (*(unsigned char*) (e + 0xd4) & 0x1f) {
				*(unsigned char*) (p + 0x50) = (unsigned char) (
					(age / (*(unsigned char*) (e + 0xd4) & 0x1f)) %
					cnt);
			}
			*(float*) (p + 0x10) += dt * *(float*) (e + 0x58);
			*(float*) (p + 0x14) += dt * *(float*) (e + 0x5c);
			*(float*) (p + 0x18) += dt * *(float*) (e + 0x60);
			*(float*) (p + 0x1c) += dt * *(float*) (e + 0x64);
			*(float*) (p + 0x10) = (float) fmod(*(float*) (p + 0x10),
				*(double*) 0x662958);
			*(float*) (p + 0x14) = (float) fmod(*(float*) (p + 0x14),
				*(double*) 0x662958);
			*(float*) (p + 0x18) = (float) fmod(*(float*) (p + 0x18),
				*(double*) 0x662958);
			*(float*) (p + 0x1c) = (float) fmod(*(float*) (p + 0x1c),
				*(double*) 0x662958);
			*(float*) (p + 0x0c) = (float) fmod(
				*(float*) (p + 0x0c) + dt * *(float*) (e + 0xbc),
				*(double*) 0x662958);
			*(float*) (p) += dt * *(float*) (e + 0x98);
			*(float*) (p + 4) += dt * *(float*) (e + 0x9c);
			*(float*) (p + 8) += dt * *(float*) (e + 0xa0);
			v[0] = *(float*) (e + 0x80) + *(float*) (p);
			v[1] = *(float*) (e + 0x84) + *(float*) (p + 4);
			v[2] = *(float*) (e + 0x88) + *(float*) (p + 8);
			*(float*) (p + 0x20) += dt * v[0];
			*(float*) (p + 0x24) += dt * v[1];
			*(float*) (p + 0x28) += dt * v[2];
			v[0] = (float) sin(*(float*) (p + 0x10));
			v[1] = (float) sin(*(float*) (p + 0x14));
			v[2] = (float) sin(*(float*) (p + 0x18));
			v[3] = (float) sin(*(float*) (p + 0x1c));
			*(float*) (p + 0x38) = v[0] * *(float*) (e + 0x48) +
				*(float*) (p + 0x20);
			*(float*) (p + 0x3c) = v[1] * *(float*) (e + 0x4c) +
				*(float*) (p + 0x24);
			*(float*) (p + 0x40) = v[2] * *(float*) (e + 0x50) +
				*(float*) (p + 0x28);
			*(float*) (p + 0x48) = v[3] * *(float*) (e + 0x54) +
				*(float*) (e + 0xe4);
			*(float*) (p + 0x44) = *(float*) (e + 0xb8) *
				(float) sin(*(float*) (p + 0x0c)) +
				*(float*) (e + 0xc0);
			if ((*(float*) (e + 0xb0) < 0.0f &&
					*(float*) (p + 0x40) < *(float*) (e + 0xb0)) ||
				(*(float*) (e + 0xb0) > 0.0f &&
					*(float*) (p + 0x40) > *(float*) (e + 0xb0))) {
				*(int*) (p + 0x40) = *(int*) (e + 0xb0);
				*(float*) (p) *= *(float*) (e + 0xa4);
				*(float*) (p + 4) *= *(float*) (e + 0xa8);
				*(float*) (p + 8) *= *(float*) (e + 0xac);
			}
			if (age < *(int*) (e + 0xc4)) {
				*(char*) (p + 0x4f) = (char) MAX(0.0f, MIN(255.0f,
					(1.0f - (float) (*(int*) (e + 0xc4) - age) *
					*(float*) (e + 0x38)) * *(float*) (p + 0x44)));
			} else if (age < *(int*) (e + 0xc8)) {
				*(char*) (p + 0x4f) = (char) MAX(0.0f, MIN(255.0f,
					*(float*) (p + 0x44)));
			} else if (age < *(int*) (e + 0xcc)) {
				*(char*) (p + 0x4f) = (char) MAX(0.0f, MIN(255.0f,
					(float) (*(int*) (e + 0xcc) - age) *
					*(float*) (p + 0x44) * *(float*) (e + 0x3c)));
			} else {
				*(unsigned char*) (p + 0x51) &= 0xfe;
				(*(int*) (e + 0x20))++;
			}
		}
	}
	if (*(unsigned char*) (e + 0xd4) & 0x20) {
		*(unsigned char*) (e + 0xd4) &= 0xdf;
	}
	if (*(unsigned char*) (e + 0xd5) & 2) {
		*(unsigned char*) (e + 0xd5) &= 0xfd;
	}
	*(unsigned int*) (e + 0x24) = a2;
	return !((*(unsigned char*) (e + 0xd5) & 1) &&
		*(int*) (e + 0x20) >= wanted);
}
