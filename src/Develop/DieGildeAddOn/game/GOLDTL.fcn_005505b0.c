#include "client_types.h"

extern unsigned char g_773d75;
extern float g_662910;
extern char g_868080[];






void __cdecl fcn_00546190(void*);
void __cdecl io_FormatTextBuffer(char*, int, ...);
int __cdecl gm_RandomMod(int);
int __cdecl fcn_004a5e60(unsigned short*, int, int, int, float, float, int*);
void __cdecl gm_ResolveEntityById(void**, void**, void**, int);
void __cdecl fcn_00545d40(int, int, char*, int, int, int);
int __cdecl gm_WalkEntityChain(unsigned short);
void __cdecl fcn_004c51a0(int, int, unsigned char, int);

/* ADDRESS: GOLDTL 0x005505b0 */
void __cdecl fcn_005505b0(int a)
{
	char buf[0x800];
	char msg[0x200];

	char* p;
	int id;
	int found;
	int n;



	if (*(int*) (a + 0x70) == -2) {
		fcn_00546190((void*) a);
		return;
	}
	io_FormatTextBuffer(buf, 0x10c2, g_868080 + (unsigned char) g_773d75 * 0x2f4, (gm_RandomMod(3) & 0xffff) + 0x10c4);
	p = (char*) 0x7f4ca0;
	do {
		id = 0;
		if (*(short*) p != -1 && *(unsigned char*) (p + 8) >= 2
		    && (*(char*) (p + 2) == 6 || *(char*) (p + 2) == 7 || *(char*) (p + 2) == 5)) {
			if (fcn_004a5e60((unsigned short*) p, 4, 0x400080, 0, 0.0f, 100.0f, &found)) {
				gm_ResolveEntityById((void**) &id, 0, 0, found);
			}
			if (*(char*) (p + 2) == 6 || *(char*) (p + 2) == 7) {
				fcn_00545d40(*(int*) (p + 4), -1, buf, 0x20, 0x601, 0);
			}
			if (id != 0) {
				n = (int) ((double) gm_WalkEntityChain(*(unsigned short*) p) * g_662910);
				n *= (gm_RandomMod(4) & 0xffff) + 2;
				fcn_004c51a0(*(int*) (p + 4), -1, (unsigned char) g_773d75, n);
				if (*(char*) (p + 2) == 6 || *(char*) (p + 2) == 7) {
					io_FormatTextBuffer(msg, 0x10c3, id, n);
					fcn_00545d40(*(int*) (p + 4), -1, msg, 0, 0x5ff, 0);
				}
			}
		}
		p += 0x21c;
	} while ((int) p < 0x85a0a0);
	fcn_00546190((void*) a);
}
