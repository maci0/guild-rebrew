// FUNCTION: GOLD 0x005beb50
// SIZE: 79
// FUNCTION: GOLDTL 0x5cad70
// SIZE: 79

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

extern int g_666018;
extern int g_66601c;

void __cdecl fcn_005ccca0(Desc*, int, int, int);

void __cdecl fcn_005cad70(int unused, int a)
{
	Desc d;

	memset(&d, 0, sizeof(d));
	d.flags = 0x204;
	d.w = g_666018;
	d.caps = 6;
	d.h = g_66601c;
	fcn_005ccca0(&d, a, 0, 0);
}
