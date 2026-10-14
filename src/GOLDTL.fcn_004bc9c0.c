


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
