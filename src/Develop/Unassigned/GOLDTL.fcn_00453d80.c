#include <math.h>
#include <stdlib.h>

#define STRIDE_453D80 0x54
#define RAND_UNIT_453D80 0.000030518f
#define TWO_PI_F_453D80 6.2831855f
#define TWO_PI_D_453D80 6.283185307179586
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

/* Emitter update: integrate every particle slot by the elapsed time, retire
   expired slots, replenish the pool up to the wanted count and write the
   transformed positions. Returns 0 once the slot budget is filled. */
/* ADDRESS: GOLDTL 0x00453d80 */
unsigned char __cdecl d3_StepParticleEmitter(void* emitterArg, unsigned int tick)
{
	char* emitter;
	char* particle;
	int i;
	int cnt;
	int n;
	int wanted;
	int age;
	float dt;
	float fade;
	float r;
	float s1;
	float s2;
	float s3;
	float s4;
	float s[4];
	float t;
	float u;
	float v;
	float w;
	float x;
	float y;
	float z;

	emitter = (char*) emitterArg;
	cnt = 1;
	if (*(int*) (emitter + 0x24) == tick) {
		return 1;
	}
	if (*(unsigned char*) (emitter + 0xd4) & 0x80) {
		wanted = (int) ((float) *(int*) (emitter + 0xd8) * *(float*) (emitter + 0xb4));
	} else {
		wanted = *(int*) (emitter + 0xd8);
	}
	if (*(int*) (emitter + 0xdc) != 0 &&
		*(unsigned char*) (*(int*) (emitter + 0xdc) + 0x5c) > 0) {
		cnt = *(unsigned char*) (*(int*) (emitter + 0xdc) + 0x5c);
	}
	*(float*) (emitter + 0x38) = 1.0f / (float) *(int*) (emitter + 0xc4);
	*(float*) (emitter + 0x3c) = 1.0f /
		(float) (*(int*) (emitter + 0xcc) - *(int*) (emitter + 0xc8));
	particle = *(char**) (emitter + 0x28);
	n = 0;
	i = 0;
	while (i < *(int*) (emitter + 0xd8)) {
		if (!(*(unsigned char*) (particle + 0x51) & 1)) {
			if (n < wanted &&
				(!(*(unsigned char*) (emitter + 0xd4) & 0x80) ||
					*(unsigned char*) (emitter + 0xd5) & 2)) {
				n++;
				*(float*) (particle + 0x10) = TWO_PI_F_453D80 *
					((float) rand() * RAND_UNIT_453D80);
				*(float*) (particle + 0x14) = TWO_PI_F_453D80 *
					((float) rand() * RAND_UNIT_453D80);
				*(float*) (particle + 0x18) = TWO_PI_F_453D80 *
					((float) rand() * RAND_UNIT_453D80);
				*(float*) (particle + 0x1c) = TWO_PI_F_453D80 *
					((float) rand() * RAND_UNIT_453D80);
				*(float*) (particle + 0x0c) = TWO_PI_F_453D80 *
					((float) rand() * RAND_UNIT_453D80);
				*(unsigned char*) (particle + 0x50) = (unsigned char) (i % cnt);
				*(unsigned char*) (particle + 0x4e) = (unsigned char) (rand() &
					*(unsigned char*) (emitter + 0xd3)) +
					*(unsigned char*) (emitter + 0xd2);
				*(unsigned char*) (particle + 0x4d) = (unsigned char) (rand() &
					*(unsigned char*) (emitter + 0xd3)) +
					*(unsigned char*) (emitter + 0xd1);
				*(unsigned char*) (particle + 0x4c) = (unsigned char) (rand() &
					*(unsigned char*) (emitter + 0xd3)) +
					*(unsigned char*) (emitter + 0xd0);
				*(unsigned char*) (particle + 0x4f) = 0;
				*(unsigned int*) (particle + 0x30) = tick;
				s[0] = 2.0f * ((float) rand() * RAND_UNIT_453D80) - 1.0f;
				s[1] = 2.0f * ((float) rand() * RAND_UNIT_453D80) - 1.0f;
				s[2] = 2.0f * ((float) rand() * RAND_UNIT_453D80) - 1.0f;
				*(float*) (particle + 0x20) = s[0] * *(float*) (emitter + 0x68);
				*(float*) (particle + 0x24) = s[1] * *(float*) (emitter + 0x6c);
				*(float*) (particle + 0x28) = s[2] * *(float*) (emitter + 0x70);
				if (*(unsigned char*) (emitter + 0xd4) & 0x40) {
					r = (float) rand() * RAND_UNIT_453D80;
					*(int*) (particle + 0x34) = (int) (
						(float) (unsigned int) tick -
						r * (float) *(int*) (emitter + 0xcc));
				} else {
					*(unsigned int*) (particle + 0x34) = tick;
				}
				*(float*) (particle) = (float) rand() * RAND_UNIT_453D80;
				*(float*) (particle + 4) = (float) rand() * RAND_UNIT_453D80;
				*(float*) (particle + 8) = (float) rand() * RAND_UNIT_453D80;
				*(float*) (particle) *= *(float*) (emitter + 0x8c);
				*(float*) (particle + 4) *= *(float*) (emitter + 0x90);
				*(float*) (particle + 8) *= *(float*) (emitter + 0x94);
				*(unsigned char*) (particle + 0x51) |= 1;
			}
		} else {
			dt = (float) (unsigned int) (tick - *(unsigned int*) (particle + 0x30));
			if (dt > 150.0f) {
				*(unsigned int*) (particle + 0x34) +=
					tick - *(unsigned int*) (particle + 0x30);
				dt = 0.0f;
			}
			*(unsigned int*) (particle + 0x30) = tick;
			if (*(unsigned char*) (emitter + 0xd4) & 0x1f) {
				*(unsigned char*) (particle + 0x50) = (unsigned char) (
					(int) (tick - *(unsigned int*) (particle + 0x34)) /
					(*(unsigned char*) (emitter + 0xd4) & 0x1f) % cnt);
			}
			*(float*) (particle + 0x10) += dt * *(float*) (emitter + 0x58);
			*(float*) (particle + 0x14) += dt * *(float*) (emitter + 0x5c);
			*(float*) (particle + 0x18) += dt * *(float*) (emitter + 0x60);
			*(float*) (particle + 0x1c) += dt * *(float*) (emitter + 0x64);
			t = *(float*) (particle + 0x10) = (float) fmod(*(float*) (particle + 0x10),
				TWO_PI_D_453D80);
			u = *(float*) (particle + 0x14) = (float) fmod(*(float*) (particle + 0x14),
				TWO_PI_D_453D80);
			v = *(float*) (particle + 0x18) = (float) fmod(*(float*) (particle + 0x18),
				TWO_PI_D_453D80);
			w = *(float*) (particle + 0x1c) = (float) fmod(*(float*) (particle + 0x1c),
				TWO_PI_D_453D80);
			*(float*) (particle + 0x0c) = (float) fmod(
				*(float*) (particle + 0x0c) + dt * *(float*) (emitter + 0xbc),
				TWO_PI_D_453D80);
			*(float*) (particle) += dt * *(float*) (emitter + 0x98);
			*(float*) (particle + 4) += dt * *(float*) (emitter + 0x9c);
			*(float*) (particle + 8) += dt * *(float*) (emitter + 0xa0);
			s[0] = *(float*) (emitter + 0x80) + *(float*) (particle);
			s[1] = *(float*) (emitter + 0x84) + *(float*) (particle + 4);
			s[2] = *(float*) (emitter + 0x88) + *(float*) (particle + 8);
			*(float*) (particle + 0x20) += dt * s[0];
			*(float*) (particle + 0x24) += dt * s[1];
			*(float*) (particle + 0x28) += dt * s[2];
			s[0] = (float) sin(t);
			s[1] = (float) sin(u);
			s[2] = (float) sin(v);
			s[3] = (float) sin(w);
			*(float*) (particle + 0x38) = *(float*) (emitter + 0x48) * s[0] +
				*(float*) (particle + 0x20);
			*(float*) (particle + 0x3c) = *(float*) (emitter + 0x4c) * s[1] +
				*(float*) (particle + 0x24);
			*(float*) (particle + 0x40) = *(float*) (emitter + 0x50) * s[2] +
				*(float*) (particle + 0x28);
			*(float*) (particle + 0x48) = *(float*) (emitter + 0x54) * s[3] +
				*(float*) (emitter + 0xe4);
			*(float*) (particle + 0x44) = *(float*) (emitter + 0xb8) *
				(float) sin(*(float*) (particle + 0x0c)) + *(float*) (emitter + 0xc0);
			if ((*(float*) (emitter + 0xb0) < 0.0f &&
					*(float*) (particle + 0x40) < *(float*) (emitter + 0xb0)) ||
				(*(float*) (emitter + 0xb0) > 0.0f &&
					*(float*) (particle + 0x40) > *(float*) (emitter + 0xb0))) {
				*(int*) (particle + 0x40) = *(int*) (emitter + 0xb0);
				*(float*) (particle) *= *(float*) (emitter + 0xa4);
				*(float*) (particle + 4) *= *(float*) (emitter + 0xa8);
				*(float*) (particle + 8) *= *(float*) (emitter + 0xac);
			}
			age = (int) (tick - *(unsigned int*) (particle + 0x34));
			if (age < *(int*) (emitter + 0xc4)) {
				fade = 1.0f - (float) (*(int*) (emitter + 0xc4) - age) *
					*(float*) (emitter + 0x38);
				*(char*) (particle + 0x4f) = (char) MAX(0.0f, MIN(255.0f,
					fade * *(float*) (particle + 0x44)));
			} else if (age < *(int*) (emitter + 0xc8)) {
				*(char*) (particle + 0x4f) = (char) MAX(0.0f, MIN(255.0f,
					*(float*) (particle + 0x44)));
			} else if (age < *(int*) (emitter + 0xcc)) {
				fade = (float) (*(int*) (emitter + 0xcc) - age) *
					*(float*) (emitter + 0x3c);
				*(char*) (particle + 0x4f) = (char) MAX(0.0f, MIN(255.0f,
					fade * *(float*) (particle + 0x44)));
			} else {
				*(unsigned char*) (particle + 0x51) &= 0xfe;
				(*(int*) (emitter + 0x20))++;
			}
		}
		i++;
		particle += STRIDE_453D80;
	}
	if (*(unsigned char*) (emitter + 0xd4) & 0x20) {
		*(unsigned char*) (emitter + 0xd4) &= 0xdf;
	}
	if (*(unsigned char*) (emitter + 0xd5) & 2) {
		*(unsigned char*) (emitter + 0xd5) &= 0xfd;
	}
	*(unsigned int*) (emitter + 0x24) = tick;
	return (*(unsigned char*) (emitter + 0xd5) & 1) &&
		*(int*) (emitter + 0x20) >= wanted ? 0 : 1;
}
/* Layout scaffolding: shifts the next source object to its reference
 * VA. 0x90 filler, not reconstruction. Generated by the text lead pass. */
#pragma data_seg(".text")

