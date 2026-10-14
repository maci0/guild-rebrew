


typedef struct {
	short w[7];
} Rec14;
// SIZE 0xe

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;

void __cdecl fcn_00569700(char* e)
{
	*(Rec14*) (e + 0x52) = (*(Rec14*)&g_7f4c00);
	*(Rec14*) (e + 0xb4) = (*(Rec14*)&g_7f4c00);
}
