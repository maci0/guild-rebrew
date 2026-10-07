// FUNCTION: GOLD 0x00572e20
// FUNCTION: GOLDTL 0x0057b330

typedef struct {
	short w[7];
} Rec14;
// SIZE 0xe

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;

void __cdecl sim_SetSyncParams(char*, int, int, int);

void __cdecl fcn_0057b330(char* e)
{
	*(Rec14*) (e + 0x52) = (*(Rec14*)&g_7f4c00);
	sim_SetSyncParams(e + 0x52, 6, 0, 0);
	*(Rec14*) (e + 0x60) = *(Rec14*) (e + 0x52);
}
