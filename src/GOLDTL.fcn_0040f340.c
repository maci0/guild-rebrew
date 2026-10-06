// FUNCTION: GOLD 0x0040e430
// FUNCTION: GOLDTL 0x0040f340

#include <string.h>

// SIZE 0xcc
typedef struct {
	char name[0x40];
	char name2[0x80];
	int a;
	int b;
	int found;
} Query;

extern int g_67a370;
void __cdecl fcn_004379a0(int a, int b, int c, void (__cdecl* cb)(void), Query* q);
void __cdecl fcn_0040f1c0(void);

int __cdecl fcn_0040f340(char** name, char** name2, int* a, int* b)
{
	Query q;

	strcpy(q.name, *name);
	strcpy(q.name2, *name2);
	q.a = *a;
	q.b = *b;
	if (q.name[0] != 0) {
		fcn_004379a0(g_67a370, 0, 0x40, fcn_0040f1c0, &q);
	}
	return 0;
}
