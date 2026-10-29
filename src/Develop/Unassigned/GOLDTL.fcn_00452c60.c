#include <math.h>

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
} fcn_00452c60_Particle; /* SIZE 0x54 */

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

/* ADDRESS: GOLDTL 0x00452c60 */
int __cdecl fcn_00452c60(fcn_00452c60_Emitter* e, unsigned int t)
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

	den = 1;
	if (e->f24 == t)
		return 1;
	len = (float) sqrt(e->f74 * e->f74 + e->f78 * e->f78 + e->f7c * e->f7c);
	if (e->f68 > e->f6c)
		len = -len;
	lim = e->d4 < 0 ? (int) (e->count * e->fb4) : e->count;
	if (e->sub != 0 && ((fcn_00452c60_Sub*) e->sub)->n > 0)
		den = ((fcn_00452c60_Sub*) e->sub)->n;
	e->f38 = *(float*) 0x6628a0 / e->c4;
	e->f3c = *(float*) 0x6628a0 / (e->cc - e->c8);
	e->f40 = *(float*) 0x6628a0 / (float) fabs(e->f6c - e->f68);
	p = e->particles;
	cnt = 0;
	for (i = 0; i < e->count; i++, p++) {
		if (!(p->flags & 1)) {
			if (cnt >= lim)
				continue;
			if (e->d4 < 0 && !(e->d5 & 2))
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
			p->f4f = 0;
			p->f4c = (char) ((rand() & e->d3) + e->d0);
			p->f30 = t;
			v[0] = (float) rand() * *(float*) 0x662a18 - *(float*) 0x6628cc;
			v[1] = (float) rand() * *(float*) 0x662a18 - *(float*) 0x6628cc;
			v[2] = (float) rand() * *(float*) 0x662a18 - *(float*) 0x6628cc;
			fcn_004518a0(v);
			if (!(e->d4 & 0x60)) {
				p->f34 = t;
				r = e->f68;
			} else {
				r = (float) rand() * *(float*) 0x662a18;
				p->f34 = (int) ((double) t - e->cc * r);
				lo = e->f68 < e->f6c ? e->f68 : e->f6c;
				hi = e->f68 <= e->f6c ? e->f6c : e->f68;
				r = lo + (hi - lo) * r;
			}
			p->f20 = v[0] * r;
			p->f24 = v[1] * r;
			p->f28 = v[2] * r;
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
			if (dt > *(float*) 0x662d98) {
				p->f34 += d;
				dt = *(float*) 0x6628a8;
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
				r = (*(float*) 0x6628a0 - (float) (e->c4 - age) * e->f38) * p->f44;
				if (r > *(float*) 0x6628a4)
					r = *(float*) 0x6628a4;
				if (r < *(float*) 0x6628a8)
					r = *(float*) 0x6628a8;
				p->f4f = (char) r;
			} else if (age < e->c8) {
				r = p->f44;
				if (r > *(float*) 0x6628a4)
					r = *(float*) 0x6628a4;
				if (r < *(float*) 0x6628a8)
					r = *(float*) 0x6628a8;
				p->f4f = (char) r;
			} else if (age < e->cc) {
				r = (float) (e->cc - age) * p->f44 * e->f3c;
				if (r > *(float*) 0x6628a4)
					r = *(float*) 0x6628a4;
				if (r < *(float*) 0x6628a8)
					r = *(float*) 0x6628a8;
				p->f4f = (char) r;
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
	if ((e->d5 & 1) && e->f20 >= den)
		return 0;
	return 1;
}
/* Layout scaffolding: shifts the next source object to its reference
 * VA. 0x90 filler, not reconstruction. Generated by the text lead pass. */
#pragma data_seg(".text")

