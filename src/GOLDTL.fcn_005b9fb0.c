


// SIZE 0xe
typedef struct {
	char b[14];
} Stamp;

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;

char* __cdecl fcn_005463a0(int, int, int);
char* __cdecl fcn_005462a0(void);
void __cdecl fcn_004c5620(int, char*);

void __cdecl fcn_005b9fb0(char* e)
{
	char* p;

	for (p = fcn_005463a0(1, 0, 0xf); p != 0; p = fcn_005462a0()) {
		if (*(int*) (p + 0xac) == *(int*) (e + 2)) {
			*(Stamp*) (p + 0x52) = (*(Stamp*)&g_7f4c00);
			fcn_004c5620(-1, p);
			return;
		}
	}
}
