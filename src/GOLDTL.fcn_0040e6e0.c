// FUNCTION: GOLD 0x0040d7b0
// SIZE: 176
// FUNCTION: GOLDTL 0x0040e6e0
// SIZE: 176

#include <stdlib.h>
#include <string.h>

// SIZE 0xc4
typedef struct {
	int list[0x20];
	int count;
	char name[0x40];
} Query;

extern int g_67a370;
int __cdecl fcn_0041dd90(int p);
void __cdecl fcn_004379a0(int a, int b, int c, void (__cdecl* cb)(void), Query* q);
void __cdecl fcn_0040e610(void);

int __cdecl fcn_0040e6e0(int* a, char** name)
{
	Query q;

	if (*a == 0) {
		return 0;
	}
	if (!fcn_0041dd90(*a)) {
		return 0;
	}
	memset(&q, 0, sizeof(q));
	strcpy(q.name, *name);
	fcn_004379a0(g_67a370, *a, 0x340, fcn_0040e610, &q);
	if (q.count == 0) {
		return 0;
	}
	return q.list[rand() % q.count];
}
