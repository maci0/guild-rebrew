// FUNCTION: GOLDTL 0x005a0630

#include <string.h>

typedef struct
{
	int x0;
	int x4;
	__int64 mask;
	int x10;
	char pad14[0x3c];
} Query;
// SIZE 0x50

extern __int64 g_666018;

void __cdecl fcn_0051af00(void*, int, ...);
void __cdecl fcn_005cd440(Query*, char*, int, void*);
void __cdecl fcn_005bf580(void);
void __cdecl fcn_00532ef0(void);

void __cdecl fcn_005a0630(void)
{
	Query q;
	char buf[0x80];

	memset(&q, 0, sizeof(q));
	q.x4 = 0x400;
	q.x10 = 6;
	q.mask = g_666018;
	fcn_0051af00(buf, 0x16f9);
	fcn_005cd440(&q, buf, 0, (void*) fcn_005bf580);
	fcn_00532ef0();
}
