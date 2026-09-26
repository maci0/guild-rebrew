// FUNCTION: GOLD 0x005b5100
// SIZE: 84
// FUNCTION: GOLDTL 0x5c0a30
// SIZE: 84

#include <string.h>

// SIZE 0x50
typedef struct {
	int size;
	int flags;
	int w;
	int h;
	int caps;
	int rest[15];
} Desc;

extern int g_14ab080;
extern __int64 g_666018;
extern int g_66601c;

void __cdecl fcn_005cd440(Desc*, int, int, void*);
void __cdecl fcn_005c06e0(void);

void __cdecl fcn_005c0a30(void)
{
	Desc d;

	memset(&d, 0, sizeof(d));
	d.flags = 0x400;
	d.w = (*(int*)&g_666018);
	d.caps = 6;
	d.h = g_66601c;
	fcn_005cd440(&d, g_14ab080, 0, fcn_005c06e0);
}
