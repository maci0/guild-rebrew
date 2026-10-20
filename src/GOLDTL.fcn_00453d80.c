#include <math.h>
#include <stdlib.h>

#define STRIDE_453D80 0x54
#define RAND_UNIT_453D80 0.000030518f
#define TWO_PI_F_453D80 6.2831855f
#define TWO_PI_D_453D80 6.283185307179586

/* ADDRESS: GOLDTL 0x00453d80 */
/* Emitter update: integrate every particle slot by the elapsed time, retire
   expired slots, replenish the pool up to the wanted count and write the
   transformed positions. Returns 0 once the slot budget is filled. */
int __cdecl fcn_00453d80(void* a1, unsigned int a2)
{
	char* e;
	char* p;
	int i;
	int n;
	int cnt;
	int wanted;
	int age;
	float dt;
	float fade;
	float t;
	float u;
	float v;
	float w;
	float x;
	float y;
	float z;

	e = (char*) a1;
	cnt = 1;
	if (*(int*) (e + 0x24) == a2) {
		return 1;
	}
	if (*(signed char*) (e + 0xd4) < 0) {
		wanted = (int) ((float) *(int*) (e + 0xd8) * *(float*) (e + 0xb4));
	} else {
		wanted = *(int*) (e + 0xd8);
	}
	if (*(int*) (e + 0xdc) != 0 &&
		*(signed char*) (*(int*) (e + 0xdc) + 0x5c) > 0) {
		cnt = *(unsigned char*) (*(int*) (e + 0xdc) + 0x5c);
	}
	*(float*) (e + 0x38) = 1.0f / (float) *(int*) (e + 0xc4);
	*(float*) (e + 0x3c) = 1.0f /
		(float) (*(int*) (e + 0xcc) - *(int*) (e + 0xc8));
	p = *(char**) (e + 0x28);
	n = 0;
	i = 0;
	while (i < *(int*) (e + 0xd8)) {
		if (!(*(unsigned char*) (p + 0x51) & 1)) {
			if (n < wanted &&
				(*(signed char*) (e + 0xd4) >= 0 ||
					*(unsigned char*) (e + 0xd5) & 2)) {
				n++;
				*(float*) (p + 0x10) = (float) rand() * RAND_UNIT_453D80 *
					TWO_PI_F_453D80;
				*(float*) (p + 0x14) = (float) rand() * RAND_UNIT_453D80 *
					TWO_PI_F_453D80;
				*(float*) (p + 0x18) = (float) rand() * RAND_UNIT_453D80 *
					TWO_PI_F_453D80;
				*(float*) (p + 0x1c) = (float) rand() * RAND_UNIT_453D80 *
					TWO_PI_F_453D80;
				*(unsigned char*) (p + 0x50) = (unsigned char) (i % cnt);
				*(float*) (p + 0x0c) = (float) rand() * RAND_UNIT_453D80 *
					TWO_PI_F_453D80;
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
				t = (float) rand() * RAND_UNIT_453D80 * 2.0f - 1.0f;
				u = (float) rand() * RAND_UNIT_453D80 * 2.0f - 1.0f;
				v = (float) rand() * RAND_UNIT_453D80 * 2.0f - 1.0f;
				*(float*) (p + 0x20) = t * *(float*) (e + 0x68);
				*(float*) (p + 0x24) = u * *(float*) (e + 0x6c);
				*(float*) (p + 0x28) = v * *(float*) (e + 0x70);
				if (*(unsigned char*) (e + 0xd4) & 0x40) {
					*(int*) (p + 0x34) = (int) ((float) (unsigned int) a2 -
						(float) rand() * RAND_UNIT_453D80 *
							(float) *(int*) (e + 0xcc));
				} else {
					*(unsigned int*) (p + 0x34) = a2;
				}
				*(float*) (p) = (float) rand() * RAND_UNIT_453D80;
				*(float*) (p + 4) = (float) rand() * RAND_UNIT_453D80;
				*(float*) (p + 8) = (float) rand() * RAND_UNIT_453D80;
				*(float*) (p) *= *(float*) (e + 0x8c);
				*(float*) (p + 4) *= *(float*) (e + 0x90);
				*(float*) (p + 8) *= *(float*) (e + 0x94);
				*(unsigned char*) (p + 0x51) |= 1;
			}
		} else {
			dt = (float) (unsigned int) (a2 - *(unsigned int*) (p + 0x30));
			if (dt > 150.0f) {
				*(unsigned int*) (p + 0x34) +=
					a2 - *(unsigned int*) (p + 0x30);
				dt = 0.0f;
			}
			*(unsigned int*) (p + 0x30) = a2;
			if (*(unsigned char*) (e + 0xd4) & 0x1f) {
				*(unsigned char*) (p + 0x50) = (unsigned char) (
					(int) (a2 - *(unsigned int*) (p + 0x34)) /
					(*(unsigned char*) (e + 0xd4) & 0x1f) % cnt);
			}
			*(float*) (p + 0x10) += dt * *(float*) (e + 0x58);
			*(float*) (p + 0x14) += dt * *(float*) (e + 0x5c);
			*(float*) (p + 0x18) += dt * *(float*) (e + 0x60);
			*(float*) (p + 0x1c) += dt * *(float*) (e + 0x64);
			t = *(float*) (p + 0x10) = (float) fmod(*(float*) (p + 0x10),
				TWO_PI_D_453D80);
			u = *(float*) (p + 0x14) = (float) fmod(*(float*) (p + 0x14),
				TWO_PI_D_453D80);
			v = *(float*) (p + 0x18) = (float) fmod(*(float*) (p + 0x18),
				TWO_PI_D_453D80);
			w = *(float*) (p + 0x1c) = (float) fmod(*(float*) (p + 0x1c),
				TWO_PI_D_453D80);
			*(float*) (p + 0x0c) = (float) fmod(
				*(float*) (p + 0x0c) + dt * *(float*) (e + 0xbc),
				TWO_PI_D_453D80);
			*(float*) (p) += dt * *(float*) (e + 0x98);
			*(float*) (p + 4) += dt * *(float*) (e + 0x9c);
			*(float*) (p + 8) += dt * *(float*) (e + 0xa0);
			x = *(float*) (e + 0x80) + *(float*) (p);
			y = *(float*) (e + 0x84) + *(float*) (p + 4);
			z = *(float*) (e + 0x88) + *(float*) (p + 8);
			*(float*) (p + 0x20) += dt * x;
			*(float*) (p + 0x24) += dt * y;
			*(float*) (p + 0x28) += dt * z;
			*(float*) (p + 0x38) = *(float*) (e + 0x48) * (float) sin(t) +
				*(float*) (p + 0x20);
			*(float*) (p + 0x3c) = *(float*) (e + 0x4c) * (float) sin(u) +
				*(float*) (p + 0x24);
			*(float*) (p + 0x40) = *(float*) (e + 0x50) * (float) sin(v) +
				*(float*) (p + 0x28);
			*(float*) (p + 0x48) = *(float*) (e + 0x54) * (float) sin(w) +
				*(float*) (e + 0xe4);
			*(float*) (p + 0x44) = *(float*) (e + 0xb8) *
				(float) sin(*(float*) (p + 0x0c)) + *(float*) (e + 0xc0);
			if ((*(float*) (e + 0xb0) < 0.0f &&
					*(float*) (p + 0x40) < *(float*) (e + 0xb0)) ||
				(*(float*) (e + 0xb0) > 0.0f &&
					*(float*) (p + 0x40) > *(float*) (e + 0xb0))) {
				*(int*) (p + 0x40) = *(int*) (e + 0xb0);
				*(float*) (p) *= *(float*) (e + 0xa4);
				*(float*) (p + 4) *= *(float*) (e + 0xa8);
				*(float*) (p + 8) *= *(float*) (e + 0xac);
			}
			age = (int) (a2 - *(unsigned int*) (p + 0x34));
			if (age < *(int*) (e + 0xc4)) {
				fade = 1.0f - (float) (*(int*) (e + 0xc4) - age) *
					*(float*) (e + 0x38);
				t = fade * *(float*) (p + 0x44);
				*(char*) (p + 0x4f) = (char) (t > 255.0f ? 255.0f :
					(t > 0.0f ? t : 0.0f));
			} else if (age < *(int*) (e + 0xc8)) {
				t = *(float*) (p + 0x44);
				*(char*) (p + 0x4f) = (char) (t > 255.0f ? 255.0f :
					(t > 0.0f ? t : 0.0f));
			} else if (age < *(int*) (e + 0xcc)) {
				fade = (float) (*(int*) (e + 0xcc) - age) *
					*(float*) (e + 0x3c);
				t = fade * *(float*) (p + 0x44);
				*(char*) (p + 0x4f) = (char) (t > 255.0f ? 255.0f :
					(t > 0.0f ? t : 0.0f));
			} else {
				*(unsigned char*) (p + 0x51) &= 0xfe;
				(*(int*) (e + 0x20))++;
			}
		}
		i++;
		p += STRIDE_453D80;
	}
	if (*(unsigned char*) (e + 0xd4) & 0x20) {
		*(unsigned char*) (e + 0xd4) &= 0xdf;
	}
	if (*(unsigned char*) (e + 0xd5) & 2) {
		*(unsigned char*) (e + 0xd5) &= 0xfd;
	}
	*(unsigned int*) (e + 0x24) = a2;
	if (*(unsigned char*) (e + 0xd5) & 1) {
		if (*(int*) (e + 0x20) >= cnt) {
			return 0;
		}
	}
	return 1;
}
