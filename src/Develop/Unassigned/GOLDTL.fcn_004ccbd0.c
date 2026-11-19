


#include <string.h>

char* __cdecl ch_FindCharacterByName(char*);
int __cdecl d3_GetContextIndex(int);
char* __cdecl ch_CreateAction(char*, int, int, int, int);

int __cdecl fcn_004ccbd0(char* x, char* out)
{
	char* a;
	char* b;
	char* o;

	b = 0;
	a = ch_FindCharacterByName(x + 0x10);
	if (a == 0)
		return 1;
	if (x[0x10] != 0)
		b = ch_FindCharacterByName(x + 0x30);
	if (out != 0) {
		o = ch_CreateAction(a, 0x2d, *(int*) (x + 0x28), *(int*) (x + 0x2c), d3_GetContextIndex(*(int*) (a + 0x88)));
		*(int*) (o + 0x160) |= 2;
		if (b != 0) {
			strcpy(o + 0x114, x + 0x30);
			*(int*) (o + 0x160) |= 8;
		}
		out[0] = 1;
		out[1] = 0;
		*(int*) (out + 6) = 0;
		return 0;
	}
	ch_CreateAction(a, 0x3a, *(int*) (x + 0x28), *(int*) (x + 0x2c), d3_GetContextIndex(*(int*) (a + 0x88)));
	return 0;
}
