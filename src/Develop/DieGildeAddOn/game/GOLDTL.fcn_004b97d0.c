#include "Develop/DieGildeAddOn/game/spiel.h"
#include <string.h>

unsigned short* __cdecl gm_LookupEntityRecordById(int);
int __cdecl fcn_005c6270(void*, int);
char* __cdecl fcn_005463a0(int, int, int);
char* __cdecl he_fn_Handlung(void);

int __cdecl gm_CheckEntityType(char*);
unsigned short __cdecl gm_RandomMod(unsigned short);
void __cdecl io_FormatTextBuffer(void*, int, ...);
void __cdecl fcn_00545d40(int, int, char*, int, int, int);


/* ADDRESS: GOLDTL 0x004b97d0 */
int __cdecl fcn_004b97d0(int* a1)
{
	char* x2;
	char* x1;
	char* y;
	char* ys[8];
	char* ss[8];
	char buf[0x200];
	unsigned short* e;
	char* s;
	int n;
	int cnt;
	int r;

	n = 0;
	e = gm_LookupEntityRecordById(a1[0]);
	if (e == 0)
		return 1;
	if (fcn_005c6270(e, 0x290) != 0)
		return 0x400;
	for (s = fcn_005463a0(1, 0, 0xf); s != 0 && n < 8; s = he_fn_Handlung()) {
		gm_ResolveEntityById(0, (void**) (&y), 0, *(int*) (s + 0xac));
		if (y != 0 && *(int*) (y + 0xa) == *e) {
			gm_ResolveEntityById((void**) (&x1), 0, 0, *(int*) (s + 0xb4));
			gm_ResolveEntityById((void**) (&x2), 0, 0, *(int*) (s + 0xb0));
			if ((x1 != 0 && gm_CheckEntityType(x1) != 0) || (x2 != 0 && gm_CheckEntityType(x2) != 0)) {
				if ((x2 != 0 && x1 != 0 && *x2 != 'G') || *x1 != 'G') {
					ss[n] = s;
					ys[n] = y;
					n++;
				}
			}
		}
	}
	if (n == 0)
		return 0x400;
	cnt = gm_RandomMod(3) + 2;
	r = gm_RandomMod(n);
	s = ss[r];
	y = ys[r];
	gm_ResolveEntityById((void**) (&x2), 0, 0, *(int*) (s + 0xb0));
	gm_ResolveEntityById((void**) (&x1), 0, 0, *(int*) (s + 0xb4));
	if (x2 != 0 && x1 != 0) {
		io_FormatTextBuffer(buf, *(unsigned short*) (a1 + 1) + 0x12e7, x2, x1, cnt);
		fcn_00545d40(*(int*) (e + 2), *(int*) (e + 2), buf, strlen(buf) > 0x100, 0x5ef, 0);
	}
	return 0;
}
