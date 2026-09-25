// FUNCTION: GOLDTL 0x4bca30
// SIZE: 115

#include <string.h>

typedef struct {
	char name[0x20];
	char* list[0x20];
	int n;
} pickctx;
// SIZE 0xa4

extern int g_67a370;

int __cdecl fcn_004bc9c0(char*, pickctx*);
void __cdecl fcn_004379a0(int, int, int, int(__cdecl*)(char*, pickctx*), pickctx*);
unsigned short __cdecl fcn_0042e410(int);

char* __cdecl fcn_004bca30(char* name)
{
	pickctx c;

	c.n = 0;
	strcpy(c.name, name);
	fcn_004379a0(g_67a370, 0, 0x380, fcn_004bc9c0, &c);
	if (c.n == 0)
		return 0;
	return c.list[fcn_0042e410(c.n)];
}
