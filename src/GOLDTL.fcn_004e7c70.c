// FUNCTION: GOLD 0x4e60b0
// FUNCTION: GOLDTL 0x4e7c70

typedef struct {
	int a;
	int id;
	unsigned char kind;
	char pad9[0xf];
} rec18;
// SIZE 0x18

#include "client_types.h"
extern Rec18_68da68 g_68da68[];
extern int g_68d9a0[];

int __cdecl fcn_004e7c70(unsigned char* e, int k, int* out)
{
	if (e == 0 || *(unsigned short*) e == 0xffff || k == 0 || k >= 30)
		return 0;
	if (e[0x166] >= 30 || e[0x167] >= 30)
		return 0;
	if (((rec18*)g_68da68)[e[0x167]].kind + 1 < ((rec18*)g_68da68)[k].kind)
		return 0;
	if (((rec18*)g_68da68)[e[0x166]].kind >= ((rec18*)g_68da68)[k].kind)
		return 0;
	*out = g_68d9a0[((rec18*)g_68da68)[e[0x166]].id * 7 + ((rec18*)g_68da68)[k].id];
	return 1;
}
