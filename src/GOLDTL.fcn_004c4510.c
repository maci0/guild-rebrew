// FUNCTION: GOLD 0x004c3ba0
// SIZE: 90
// FUNCTION: GOLDTL 0x4c4510
// SIZE: 90

#include <string.h>

typedef struct
{
	int id;
	char count;
	char data[0x77];
} Buf220;
// SIZE 0x7c

extern unsigned int g_aed208;
extern Buf220 g_aed220;
extern char* g_aed32c;

int __cdecl fcn_005015e0(int*, int*, int*, int);

void __cdecl fcn_004c4510(int a1, int a2)
{
	int l0;
	int l1;

	g_aed220.id = a2;
	g_aed220.count = 0;
	memset(g_aed220.data, 0, sizeof(g_aed220.data));
	(*(int*)&g_aed208) = 0;
	if (fcn_005015e0(&l1, &l0, &a2, a2) != 0) {
		(*(int*)&g_aed32c) = a1;
	}
}
