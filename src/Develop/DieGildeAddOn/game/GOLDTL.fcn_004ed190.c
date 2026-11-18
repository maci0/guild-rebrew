


typedef struct
{
	short s[7];
} Pos0e;
// SIZE 0xe

#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;

unsigned char* __cdecl fcn_005463a0(int, int, int);
unsigned char* __cdecl he_fn_Handlung(void);
void __cdecl fcn_004c5620(int, unsigned char*);

void __cdecl fcn_004ed190(char* object)
{
	unsigned char* p;

	for (p = fcn_005463a0(1, 3, *(int*) (object + 1)); p != 0; p = he_fn_Handlung()) {
		if (*p >= 0x95 && *p <= 0x97) {
			*(Pos0e*) (p + 0x52) = (*(Pos0e*)&gm_GameTime);
			fcn_004c5620(-2, p);
		}
	}
}
