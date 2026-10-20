#include "client_types.h"

extern unsigned char g_773d75;
extern float g_662910;
extern char g_868080[];

typedef struct F8 {
	int mask;
	int b;
} F8;

void __cdecl fcn_00546190(void*);
void __cdecl fcn_0051af00(char*, int, ...);
int __cdecl gm_RandomMod(int);
int __cdecl fcn_004a5e60(char*, int, F8, int, float, int*);
void __cdecl gm_ResolveEntityById(void**, void**, void**, int);
void __cdecl fcn_00545d40(int, int, char*, int, int, int);
int __cdecl fcn_0050dac0(unsigned short);
void __cdecl fcn_004c51a0(int, int, unsigned char, int);

/* ADDRESS: GOLDTL 0x005505b0 */
void __cdecl fcn_005505b0(int a)
{
	char buf[0x800];
	char msg[0x200];
	F8 f;
	char* p;
	int id;
	int found;
	int n;

	f.mask = 0x400080;
	f.b = 0;
	if (*(int*) (a + 0x70) == -2) {
		fcn_00546190((void*) a);
		return;
	}
	fcn_0051af00(buf, 0x10c2, g_868080 + (unsigned char) g_773d75 * 0x2f4, (gm_RandomMod(3) & 0xffff) + 0x10c4);
	p = (char*) 0x7f4ca2;
	do {
		id = 0;
		if (*(short*) (p - 2) != -1 && *(unsigned char*) (p + 6) >= 2
		    && (*(char*) p == 6 || *(char*) p == 7 || *(char*) p == 5)) {
			if (fcn_004a5e60(p - 2, 4, f, 0, 100.0f, &found)) {
				gm_ResolveEntityById((void**) &id, 0, 0, found);
			}
			if (*(char*) p == 6 || *(char*) p == 7) {
				fcn_00545d40(*(int*) (p + 2), -1, buf, 0x20, 0x601, 0);
			}
			if (id != 0) {
				n = (int) ((double) fcn_0050dac0(*(unsigned short*) (p - 2)) * g_662910);
				n *= (gm_RandomMod(4) & 0xffff) + 2;
				fcn_004c51a0(*(int*) (p + 2), -1, (unsigned char) g_773d75, n);
				if (*(char*) p == 6 || *(char*) p == 7) {
					fcn_0051af00(msg, 0x10c3, id, n);
					fcn_00545d40(*(int*) (p + 2), -1, msg, 0, 0x5ff, 0);
				}
			}
		}
		p += 0x21c;
	} while ((int) p < 0x85a0a2);
	fcn_00546190((void*) a);
}
