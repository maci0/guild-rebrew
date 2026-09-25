extern int g_67a370;

// SIZE 0x84
struct list_55d630 {
	char* a[32];
	int n;
};

// FUNCTION: GOLDTL 0x55d630
// SIZE: 175

#include <string.h>

void __cdecl fcn_004379a0(int, char*, int, void*, struct list_55d630*);
char __cdecl fcn_0055d5e0(char*, struct list_55d630*);
unsigned short __cdecl fcn_0042e410(int);

char* __cdecl fcn_0055d630(char* o)
{
	struct list_55d630 l;
	int saved;

	memset(&l, 0, sizeof(l));
	l.n = 0;
	if (o != 0 && (o[0x214] & 1) == 0) {
		saved = *(int*) (o + 0x1f4);
		*(int*) (o + 0x1f4) = 0;
		fcn_004379a0(g_67a370, o, 0x100, (void*) fcn_0055d5e0, &l);
		*(int*) (o + 0x1f4) = saved;
	} else {
		fcn_004379a0(g_67a370, o, 0x100, (void*) fcn_0055d5e0, &l);
	}
	if (l.n == 0) {
		return 0;
	}
	return l.a[fcn_0042e410(l.n)];
}
