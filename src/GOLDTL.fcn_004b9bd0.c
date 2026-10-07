#include <string.h>

#pragma pack(push, 2)
typedef struct Date {
	int a;
	int b;
	int c;
	short d;
} Date;
#pragma pack(pop)
// SIZE 0xe

extern char g_868060[];
#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;

unsigned short* __cdecl fcn_00508e40(int);
int __cdecl fcn_005c6270(unsigned short*, int);
char* __cdecl fcn_005463a0(int, int, int);
char* __cdecl fcn_005462a0(void);
int __cdecl fcn_005015e0(char**, char**, char**, int);
int __cdecl gm_CheckEntityType(char*);
unsigned short __cdecl fcn_0042e410(unsigned short);
void __cdecl fcn_0051af00(void*, int, ...);
void __cdecl fcn_00545d40(int, int, char*, int, int, int);

// FUNCTION: GOLDTL 0x4b9bd0
int __cdecl fcn_004b9bd0(int* a1)
{
	char* x1;
	char* x2;
	char* y;
	Date d;
	char* ys[8];
	char* ss[8];
	char buf[0x200];
	unsigned short* e;
	char* s;
	int n;
	int r;

	n = 0;
	e = fcn_00508e40(a1[0]);
	if (e == 0)
		return 1;
	if (fcn_005c6270(e, 0x290))
		return 0x400;
	for (s = fcn_005463a0(1, 0, 0xf); s != 0 && n < 8; s = fcn_005462a0()) {
		fcn_005015e0(0, &y, 0, *(int*) (s + 0xac));
		if (y != 0 && *(int*) (y + 0xa) == *e) {
			fcn_005015e0(&x1, 0, 0, *(int*) (s + 0xb4));
			fcn_005015e0(&x2, 0, 0, *(int*) (s + 0xb0));
			if ((x1 != 0 && gm_CheckEntityType(x1) != 0) || (x2 != 0 && gm_CheckEntityType(x2) != 0)) {
				if ((x1 != 0 && x2 != 0 && *x2 == 'G') || *x1 == 'G') {
					ss[n] = s;
					ys[n] = y;
					n++;
				}
			}
		}
	}
	if (n == 0)
		return 0x400;
	d = (*(Date*)&g_7f4c00);
	d.a++;
	r = fcn_0042e410(n);
	s = ss[r];
	y = ys[r];
	fcn_005015e0(&x2, 0, 0, *(int*) (s + 0xb0));
	fcn_005015e0(&x1, 0, 0, *(int*) (s + 0xb4));
	if (x2 != 0 && x1 != 0) {
		if (*x2 == 'G')
			fcn_0051af00(buf, *(unsigned short*) (a1 + 1) + 0x12e7, g_868060 + *(int*) (x2 + 0x65) * 756, g_868060, &d, g_868060);
		else
			fcn_0051af00(buf, *(unsigned short*) (a1 + 1) + 0x12e7, g_868060, g_868060 + *(int*) (x1 + 0x65) * 756, &d, g_868060 + *(int*) (x1 + 0x65) * 756);
		fcn_00545d40(*(int*) (e + 2), *(int*) (e + 2), buf, strlen(buf) > 0x100, 0x5ef, 0);
	}
	return 0;
}
