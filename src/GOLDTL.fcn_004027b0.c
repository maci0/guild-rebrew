#include <string.h>

typedef struct {
	unsigned char b0 : 1;
	unsigned char b1 : 1;
	unsigned char b2 : 1;
	unsigned char b3 : 1;
	unsigned char b4 : 1;
	unsigned char b5 : 1;
	unsigned char b6 : 1;
	unsigned char b7 : 1;
} Bits8_4027b0;
// SIZE 0x1

typedef struct {
	unsigned char id;
	unsigned char b;
	Bits8_4027b0 f;
	unsigned char d;
} Key4_4027b0;
// SIZE 0x4

typedef struct {
	char* obj;
	char fade_in;
	char pad5[3];
	int start;
} Fade_4027b0;
// SIZE 0xc

extern int g_1551f40[0x30];
extern int g_6b5c24;

void __cdecl fcn_0043a3f0(char* node, char* m, Key4_4027b0 k);
void __cdecl fcn_00402a00(char* obj, int shown);

/* ADDRESS: GOLD 0x004022e0 */
/* ADDRESS: GOLDTL 0x004027b0 */

/* Steps every running fade: writes the alpha key and ends the fade at 0 or 255. */
void __cdecl fcn_004027b0(void)
{
	char* obj;
	float t;
	float a;
	Key4_4027b0 k;
	int i;

	for (i = 0; i < 16; i++) {
		obj = ((Fade_4027b0*)g_1551f40)[i].obj;
		if (obj != 0) {
			t = ((float) g_6b5c24 - ((Fade_4027b0*)g_1551f40)[i].start) * 0.02f;
			if (!((Fade_4027b0*)g_1551f40)[i].fade_in) {
				t = 1.0f - t;
			}
			if (!(t > 0.0f)) {
				t = 0.0f;
			} else if (!(t < 1.0f)) {
				t = 1.0f;
			}
			a = t * 255.0f;
			memset(&k, 0, sizeof(k));
			k.f.b0 = 0;
			k.id = (unsigned char) a;
			if (a != 255.0f && a != 0.0f) {
				fcn_0043a3f0(*(char**) (obj + 0x34), *(char**) (*(char**) (obj + 0x34) + 0x1cc), k);
				if (*(char***) (obj + 0x124) != 0) {
					fcn_0043a3f0(**(char***) (obj + 0x124), *(char**) (*(char**) (obj + 0x34) + 0x1cc), k);
				}
			}
			if (a == 0.0f || a == 255.0f) {
				*(short*) (obj + 0x8c) &= ~0x40;
				k.id = 0xff;
				fcn_0043a3f0(*(char**) (obj + 0x34), *(char**) (*(char**) (obj + 0x34) + 0x1cc), k);
				if (*(char***) (obj + 0x124) != 0) {
					fcn_0043a3f0(**(char***) (obj + 0x124), *(char**) (**(char***) (obj + 0x124) + 0x1cc), k);
				}
				if (a == 0.0f) {
					fcn_00402a00(obj, 0);
				} else if (a == 255.0f) {
					fcn_00402a00(obj, 1);
				}
				((Fade_4027b0*)g_1551f40)[i].obj = 0;
			}
		}
	}
}
