// FUNCTION: GOLD 0x0054ff30
// FUNCTION: GOLDTL 0x557fe0

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;
extern int g_6b8010;

void __cdecl fcn_005015e0(char**, int*, int*, int);
void __cdecl fcn_004432d0(int, int);
char* __cdecl fcn_00557f00(char*);
char* __cdecl fcn_00557f70(char*);
int __cdecl fcn_00500cb0(pos14_7f4c00*, char*);
int __cdecl m_is_tracked(char*);
void __cdecl fcn_00452420(char*);
void __cdecl fcn_00546190(char*);

void __cdecl fcn_00557fe0(char* u)
{
	char* x;
	int t;

	switch (*(int*) (u + 0x70)) {
	case 0:
		fcn_005015e0(&x, 0, 0, *(int*) (u + 0xac));
		if (x == 0 || *(char**) (x + 0x61) == 0) {
			goto kill;
		}
		t = g_6b8010;
		fcn_004432d0(0, 1);
		if (*(unsigned short*) (u + 0xc2) == 0x177) {
			*(char**) (u + 0xb0) = fcn_00557f00(x);
		} else if (*(unsigned short*) (u + 0xc2) == 0x178) {
			*(char**) (u + 0xb0) = fcn_00557f70(x);
		}
		fcn_004432d0(t, 1);
		*(int*) (u + 0x70) = *(char**) (u + 0xb0) != 0 ? 1 : -1;
		break;
	case 1:
		if (fcn_00500cb0(&g_7f4c00, u + 0xb4) == 1) {
			if (*(char**) (u + 0xb0) != 0 && m_is_tracked(*(char**) (u + 0xb0)) != 0) {
				*(int*) (*(char**) (u + 0xb0) + 0x24) = 0;
			}
			*(int*) (u + 0x70) = 2;
		} else if (*(char**) (u + 0xb0) == 0) {
			*(int*) (u + 0x70) = 0;
		}
		break;
	case 2:
		if (*(char**) (u + 0xb0) == 0 || (*(*(char**) (u + 0xb0) + 0x20) & 2) != 0) {
			*(int*) (u + 0x70) = -1;
		}
		break;
	case -2:
	case -1:
		fcn_005015e0(&x, 0, 0, *(int*) (u + 0xac));
		if (*(char**) (u + 0xb0) != 0 && m_is_tracked(*(char**) (u + 0xb0)) != 0) {
			t = g_6b8010;
			fcn_004432d0(0, 1);
			fcn_00452420(*(char**) (u + 0xb0));
			fcn_004432d0(t, 1);
		}
kill:
		fcn_00546190(u);
		break;
	}
}
