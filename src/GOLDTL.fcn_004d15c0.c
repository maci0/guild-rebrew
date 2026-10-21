#include <string.h>

extern int g_14ce8cc;
extern int g_7746a0;
extern char g_14cf736;
extern int g_67a370;
extern char* g_14a9a10;
extern short g_14ce8c0;
extern short g_14ce8c2;

typedef struct {
	int id;
	int f4;
	char pad8[4];
	unsigned char fc;
	char padr[3];
	int f10;
	int f14;
	char rest[0x14];
} pkt2c;
/* SIZE 0x2c */

char __cdecl fcn_0045bad0(int, int, int, int*, int*);
int __cdecl fcn_004ce270(char*, int);
int __cdecl fcn_004d1250(char*, char*, char*);
int __cdecl fcn_004d1320(char*, char*, char*);
int __cdecl fcn_004d13d0(char*, char*, char*);
int __cdecl fcn_004d1020(char*, char*, char*, int, int);
pkt2c* __cdecl fcn_004ceac0(char*, char*);
int __cdecl fcn_004c67c0(int, pkt2c*);
void __cdecl fcn_00533a40(char*);

/* ADDRESS: GOLDTL 0x004d15c0 */
int __cdecl fcn_004d15c0(char* a0, char* a1)
{
	pkt2c l;
	pkt2c* e;
	int v13;
	int v12;
	int obj;
	char r;

	r = 0;
	if (g_14ce8cc) {
		if (g_7746a0) {
			if (*(int*) ((char*) g_7746a0 + 0x220) != 2) {
				if (strncmp((char*) g_7746a0, "sp_ESCAPE", 10) == 0) {
					fcn_004d1250(a0, a1, (char*) g_7746a0);
					r = 1;
					return r;
				}
				if (strncmp((char*) g_7746a0, "sp_CONQUER", 10) == 0) {
					fcn_004d1320(a0, a1, (char*) g_7746a0);
					r = 1;
					return r;
				}
				if (strncmp((char*) g_7746a0, "WARE", 4) == 0) {
					fcn_004d13d0(a0, a1, (char*) g_7746a0);
					r = 1;
					return r;
				}
			} else {
				obj = *(int*) ((char*) g_7746a0 + 0x204);
				if (fcn_004ce270(a1, obj) != 0 || g_14cf736 != 0) {
					if (fcn_004d1020(a0, a1, (char*) obj, 0, 0) != -1) {
						r = 1;
						return r;
					}
				}
			}
		} else {
			if (fcn_0045bad0(*(int*) (g_67a370 + 0xb0), g_14ce8c0 + 0x1a,
					 g_14ce8c2 + 0x1a, &v13, &v12) != 0) {
				e = fcn_004ceac0(a0, a1);
				e->fc = 0;
				l = *e;
				l.id = *(int*) (a1 + 4);
				l.f4 = 1;
				l.f10 = v13;
				l.f14 = v12;
				fcn_004c67c0(*(int*) (a0 + 0x10), &l);
				r = 1;
				return r;
			}
			fcn_00533a40(g_14a9a10);
		}
	}
	return r;
}
