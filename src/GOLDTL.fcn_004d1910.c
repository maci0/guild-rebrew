#include "client_types.h"
struct ent_4d1910 {
	int f0;
	char* obj;
	unsigned char flag;
	char pad9[0x213];
};
// SIZE 0x21c

extern struct ent_4d1910 g_9b4bc0[32];

void __cdecl fcn_00414be0(char*, int, int, int);

void __cdecl fcn_004cfa80(void);
void __cdecl fcn_004d0050(void);

// FUNCTION: GOLDTL 0x4d1910

void __cdecl fcn_004d1910(void)
{
	int i;

	for (i = 0; i < 32; i++) {
		if (g_9b4bc0[i].flag != 0)
			g_9b4bc0[i].flag = 0;
		if (g_9b4bc0[i].obj != 0
		    && (*(unsigned char*) (*(char**) (g_9b4bc0[i].obj + 0x34) + 0x215) & 0x80) == 0x80)
			fcn_00414be0(*(char**) (g_9b4bc0[i].obj + 0x34), 0, 0, 0);
	}
	ResetDisplayCounters();
	fcn_004cfa80();
	fcn_004d0050();
}
