extern int g_67a370;
extern int g_773dd8;

// SIZE 0x84
struct list_52dd80 {
	int n;
	char* a[32];
};

// FUNCTION: GOLDTL 0x52dd80

#include <string.h>

void __cdecl fcn_004379a0(int, char*, int, void*, struct list_52dd80*);
char __cdecl fcn_0052dd40(char*, struct list_52dd80*);
void __cdecl fcn_004550b0(char*, int);
void __cdecl fcn_00442be0(char*);

void __cdecl fcn_0052dd80(char* e)
{
	struct list_52dd80 l;
	char* o;
	int saved;
	int i;

	o = *(char**) (e + 0x61);
	if (o != 0) {
		memset(&l, 0, sizeof(l));
		if ((o[0x214] & 1) == 0) {
			saved = *(int*) (o + 0x1f4);
			*(int*) (o + 0x1f4) = 0;
			fcn_004379a0(g_67a370, *(char**) (e + 0x61), 0x40, (void*) fcn_0052dd40, &l);
			*(int*) (*(char**) (e + 0x61) + 0x1f4) = saved;
		} else {
			fcn_004379a0(g_67a370, o, 0x40, (void*) fcn_0052dd40, &l);
		}
		for (i = 0; i < l.n; i++) {
			if (g_773dd8 != 0) {
				fcn_004550b0(l.a[i], g_773dd8);
			}
			fcn_00442be0(l.a[i]);
		}
	}
}
