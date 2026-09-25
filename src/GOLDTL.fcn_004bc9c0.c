// FUNCTION: GOLD 0x4bc4b0
// SIZE: 107
// FUNCTION: GOLDTL 0x4bc9c0
// SIZE: 107

#include <string.h>

typedef struct {
	char name[0x20];
	char* list[0x20];
	int n;
} pickctx;
// SIZE 0xa4

int __cdecl fcn_004bc9c0(char* name, pickctx* c)
{
	if (strcmp(name, c->name) == 0) {
		c->list[c->n] = name;
		c->n++;
	}
	return c->n < 0x20;
}
