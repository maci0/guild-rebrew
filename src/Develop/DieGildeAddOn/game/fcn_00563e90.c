#include "client_types.h"

extern pos14_7f4c00 g_7f4c00;
extern int g_774800;

void __cdecl fcn_00500bb0(pos14_7f4c00* when, int h, int m, int s);
int __cdecl fcn_00503fe0(int a, int b, int c);
void __cdecl fcn_004c5420(int id, int a, int b, int c, int d);
void __cdecl fcn_00546190(void* p);

/* ADDRESS: GOLDTL 0x00563e90 */
void __cdecl fcn_00563e90(char* p)
{
	void* rec;

	*(pos14_7f4c00*) (p + 0x52) = g_7f4c00;
	*(pos14_7f4c00*) (p + 0x44) = g_7f4c00;
	if (g_774800 != 0) {
		fcn_00500bb0((pos14_7f4c00*) (p + 0x52), 0, 0, 1);
	} else {
		fcn_00500bb0((pos14_7f4c00*) (p + 0x52), 5, 0, 0);
	}
	rec = (void*) fcn_00503fe0(1, 1, *(int*) (p + 0xac));
	if (rec == 0) {
		fcn_00546190(p);
		return;
	}
	*(int*) (p + 0x10) = *(int*) ((char*) rec + 1);
	if (*(unsigned char*) ((char*) rec + 0x5a) & 0x80) {
		return;
	}
	fcn_004c5420(*(int*) ((char*) rec + 1), 0x5a, 2, 0x80, 0);
}
