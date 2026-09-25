// FUNCTION: GOLD 0x0040d730
// SIZE: 128
// FUNCTION: GOLDTL 0x0040e660
// SIZE: 128

#include <stdlib.h>
#include <string.h>

// SIZE 0xc4
typedef struct {
	int list[0x20];
	int count;
	char name[0x40];
} Query;

extern int g_67a370;
void __cdecl fcn_004379a0(int a, int b, int c, void (__cdecl* cb)(void), Query* q);
void __cdecl fcn_0040e610(void);

int __cdecl fcn_0040e660(char** name)
{
	Query q;

	memset(&q, 0, sizeof(q));
	strcpy(q.name, *name);
	fcn_004379a0(g_67a370, 0, 0x140, fcn_0040e610, &q);
	if (q.count == 0) {
		return 0;
	}
	return q.list[rand() % q.count];
}
