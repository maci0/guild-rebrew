#include <math.h>

extern int g_104049c;
extern int g_662ea8[];
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
	float t[4];
	int elapsed;
	int i;
	unsigned int c;

	if (count <= 0) {
		return;
	}
	c = count;
	do {
		e = *(char**) p;
		if (e != 0) {
			
			if (*(unsigned char*) (e + 0x5c) > 0 && (*(unsigned char*) (e + 0x5e) & 0xf) > 0) {
				*(int*) (p + 4) = fcn_0045cb10(
				    (int) (e - (char*) g_104049c) / 0x70,
				    (time / g_662ea8[*(unsigned char*) (e + 0x5e) & 0xf]) % *(unsigned char*) (e + 0x5c));
			}
		}
		elapsed = time - *(unsigned int*) (p + 0x150);
		if (elapsed > 0) {
			dt = (float) elapsed;
			*(float*) (p + 0x148) = (float) fmod(dt * *(float*) (p + 0xc) + *(float*) (p + 0x148), 1.0);
			*(float*) (p + 0x14c) = (float) fmod(dt * *(float*) (p + 0x10) + *(float*) (p + 0x14c), 1.0);
			for (i = 0; i < 4; i++) {
				*(float*) (p + 0x138 + i * 4) = (float) fmod(dt * *(float*) (p + 0x18 + i * 4) + *(float*) (p + 0x138 + i * 4), g_662958);
			}
			for (i = 0; i < 0x10; i++) {
				t[0] = (float) sin((double) i + *(float*) (p + 0x138) + cos(g_662cd8 * i) * g_662958);
				t[1] = (float) cos((double) i + *(float*) (p + 0x13c) + sin(g_662cc8 - g_662cd0 * i) * g_662958);
				t[2] = (float) sin((double) i - cos(g_662cc0 * i) * g_662958 + *(float*) (p + 0x140) + g_662cb8);
				t[3] = (float) cos((double) i - sin(g_662cb0 * i + g_662cc8) * g_662958 + *(float*) (p + 0x144) + g_662ad0);
				*(float*) (p + 0x38 + (i >> 2) * 0x40 + (i & 3) * 0x10) = t[0] * *(float*) (p + 0x28);
				*(float*) (p + 0x3c + (i >> 2) * 0x40 + (i & 3) * 0x10) = t[1] * *(float*) (p + 0x2c);
				*(float*) (p + 0x40 + (i >> 2) * 0x40 + (i & 3) * 0x10) = t[2] * *(float*) (p + 0x30);
				*(float*) (p + 0x44 + (i >> 2) * 0x40 + (i & 3) * 0x10) = t[3] * *(float*) (p + 0x34);
			}
			*(int*) (p + 0x150) = time;
		}
		p += 0x158;
	} while (--c);
}
