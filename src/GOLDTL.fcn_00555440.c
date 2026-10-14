


typedef struct {
	short w[7];
} Rec14;
// SIZE 0xe

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;

void __cdecl fcn_00555440(char* e)
{
	*(Rec14*) (e + 0x52) = (*(Rec14*)&g_7f4c00);
	*(short*) (e + 0x56) = 0x16;
	*(int*) (e + 0x58) = 0x1e;
	*(int*) (e + 0x5c) = 0;
	*(int*) (e + 0xac) = 0;
	*(int*) (e + 0xb0) = 0;
}
