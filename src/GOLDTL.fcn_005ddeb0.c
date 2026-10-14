


// SIZE 0xe
typedef struct {
	char b[14];
} Stamp;

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;
extern char g_7f4ca0[];

char* __cdecl fcn_005463a0(int, int, int);
char* __cdecl fcn_005462a0(void);
void __cdecl fcn_005b2350(char*, char*);
void __cdecl fcn_004c5620(int, char*);

int __cdecl fcn_005ddeb0(char* e)
{
	char* p;

	for (p = fcn_005463a0(1, 0, 0x35); p != 0; p = fcn_005462a0()) {
		if (*(int*) (e + 4) == *(int*) (p + 0xbc)) {
			fcn_005b2350(e, g_7f4ca0 + *(unsigned short*) (p + 8) * 540);
			*(Stamp*) (p + 0x52) = (*(Stamp*)&g_7f4c00);
			fcn_004c5620(-1, p);
		}
	}
	return 1;
}
