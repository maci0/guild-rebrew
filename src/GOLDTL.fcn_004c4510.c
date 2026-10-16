#include "Develop/DieGildeAddOn/game/spiel.h"



#include <string.h>

typedef struct
{
	int id;
	char count;
	char data[0x77];
} Buf220;
// SIZE 0x7c

extern unsigned int g_aed208;
extern char g_aed220[];
#include "client_packet_builder.h"



void __cdecl fcn_004c4510(char* a1, int a2)
{
	void* l0;
	void* l1;
	void* static_ptr;

	(*(Buf220*)g_aed220).id = a2;
	(*(Buf220*)g_aed220).count = 0;
	memset((*(Buf220*)g_aed220).data, 0, sizeof((*(Buf220*)g_aed220).data));
	g_aed208 = 0;
	if (gm_ResolveEntityById(&l1, &l0, &static_ptr, a2) != 0) {
		g_aed32c = a1;
	}
}
