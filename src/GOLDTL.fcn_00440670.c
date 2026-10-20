#include <math.h>

extern int g_104049c;
extern int g_662ea8[];
extern double dbl_1_0;
extern double g_662958;
extern double g_662cd8;
extern double g_662cd0;
extern double g_662cc8;
extern double g_662cc0;
extern double g_662cb8;
extern double g_662cb0;
extern double g_662ad0;

int __cdecl fcn_0045cb10(int, int);

/* ADDRESS: GOLDTL 0x00440670 */
void __cdecl fcn_00440670(unsigned int time, unsigned int count, char* p)
{
	char* e;
	float dt;
	float t1;
	float t2;
	float t3;
	float t4;
	int i;
	unsigned int n;
	unsigned int div;
	int elapsed;

	if (count <= 0) {
		return;
	}
	do {
		e = *(char**) p;
		if (e != 0) {
			n = *(unsigned char*) (e + 0x5c);
			if (n != 0 && (*(unsigned char*) (e + 0x5e) & 0xf) != 0) {
				div = g_662ea8[*(unsigned char*) (e + 0x5e) & 0xf];
				*(int*) (p + 4) = fcn_0045cb10((int) (e - (char*) g_104049c) / 0x70, (time / div) % n);
			}
		}
		elapsed = time - *(unsigned int*) (p + 0x150);
		dt = (float) elapsed;
		if ((int) elapsed > 0) {
			*(float*) (e + 0x148) = (float) fmod(*(float*) (e + 0x148) + dt * *(float*) (e + 0xc), dbl_1_0);
			*(float*) (e + 0x14c) = (float) fmod(*(float*) (e + 0x14c) + dt * *(float*) (e + 0x10), dbl_1_0);
			for (i = 0; i < 4; i++) {
				*(float*) (e + 0x138 + i * 4) = (float) fmod(*(float*) (e + 0x138 + i * 4) + dt * *(float*) (e + 0x18 + i * 4), g_662958);
			}
			for (i = 0; i < 0x10; i++) {
				t1 = (float) sin((double) i + *(float*) (e + 0x138) + cos(g_662cd8 * i) * g_662958);
				t2 = (float) cos((double) i + *(float*) (e + 0x13c) + sin(g_662cc8 - g_662cd0 * i) * g_662958);
				t3 = (float) sin((double) i - cos(g_662cc0 * i) * g_662958 + *(float*) (e + 0x140) + g_662cb8);
				t4 = (float) cos((double) i - sin(g_662cb0 * i + g_662cc8) * g_662958 + *(float*) (e + 0x144) + g_662ad0);
				*(float*) (e + 0x38 + i * 0x10) = t1 * *(float*) (e + 0x28);
				*(float*) (e + 0x3c + i * 0x10) = t2 * *(float*) (e + 0x2c);
				*(float*) (e + 0x40 + i * 0x10) = t3 * *(float*) (e + 0x30);
				*(float*) (e + 0x44 + i * 0x10) = t4 * *(float*) (e + 0x34);
			}
			*(int*) (p + 0x150) = time;
		}
		p += 0x158;
	} while (--count);
}
