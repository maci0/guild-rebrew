// FUNCTION: GOLDTL 0x004f0da0
// SIZE: 110

typedef struct
{
	char data[0x5c];
	int active;
	int x60;
	int x64;
} Sub68;
// SIZE 0x68

typedef struct
{
	int id;
	int flags;
	float s[3];
	int x14;
	Sub68 sub[3];
	int used[3];
	int h[3];
	void* fn;
	void* ctx;
} Slot170;
// SIZE 0x170

#include "client_types.h"
extern Slot170_7731b8 g_7731b8[8];
extern unsigned char* g_868050;

void __cdecl fcn_005015e0(unsigned char** out, int a, int b, int id);
void __cdecl fcn_004f0930(int id);

void __cdecl fcn_004f0da0(void)
{
	int i;
	unsigned char* r;

	for (i = 0; i < 8; i++) {
		if (((Slot170*)g_7731b8)[i].id != -1) {
			fcn_005015e0(&r, 0, 0, ((Slot170*)g_7731b8)[i].id);
			if ((r == 0 && ((Slot170*)g_7731b8)[i].flags == 0) || (g_868050[*r * 0x24d] != 0x1e && ((Slot170*)g_7731b8)[i].flags == 0)) {
				fcn_004f0930(((Slot170*)g_7731b8)[i].id);
			}
		}
	}
}
