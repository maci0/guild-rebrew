

#pragma pack(push, 2)
typedef struct
{
	int a;
	unsigned short b;
	short b2;
	int c;
	short d;
} Blob14;
// SIZE 0xe
#pragma pack(pop)

extern Blob14 g_99f590;
#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;
extern float g_773d4c;
extern float g_773d50;
extern float g_99ec14;
extern float g_6628a8;
extern double g_662ad8;

int __cdecl fcn_00500d20(Blob14* a, Blob14* b);

void __cdecl fcn_004fc180(void)
{
	int r;
	double lim;

	r = fcn_00500d20(&g_99f590, &(*(Blob14*)&g_7f4c00));
	if (r == 0) {
		g_99f590 = (*(Blob14*)&g_7f4c00);
		return;
	}
	if (g_773d50 != g_6628a8 && (*(Blob14*)&g_7f4c00).b > 6 && (*(Blob14*)&g_7f4c00).b < 0x15) {
		g_773d4c += r * g_99ec14;
		lim = g_773d50 * g_662ad8;
		if (g_773d4c < lim) {
			g_773d4c = (float) lim;
		}
		g_99f590 = (*(Blob14*)&g_7f4c00);
	}
}
