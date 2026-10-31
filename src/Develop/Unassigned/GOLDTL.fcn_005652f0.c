


typedef struct {
	short w[7];
} Rec14;
// SIZE 0xe

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;

char* __cdecl gm_LookupEntityRecordById(int);
char* __cdecl fcn_005463a0(int, int, int, ...);

void __cdecl fcn_005652f0(char* e)
{
	char* r;

	gm_LookupEntityRecordById(*(int*) (e + 0xac));
	r = fcn_005463a0(2, 2, *(unsigned short*) (e + 8), 0, 0x25);
	if (r != 0) {
		*(int*) (r + 0x70) = -1;
	}
	*(Rec14*) (e + 0x52) = (*(Rec14*)&g_7f4c00);
}
