#include <math.h>
#include <stdlib.h>

#define STRIDE_453470 0x54
#define RAND_UNIT_453470 (*(float*) 0x662a18)
#define TWO_PI_F_453470 (*(float*) 0x6628c8)

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

void __cdecl fcn_004518a0(float* v);

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
/* Layout scaffolding: shifts the next source object to its reference
 * VA. 0x90 filler, not reconstruction. Generated by the text lead pass. */
#pragma data_seg(".text")

