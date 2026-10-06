// FUNCTION: GOLDTL 0x4545c0

// SIZE 0x8
typedef struct Link {
	char* e;
	struct Link* next;
} Link;

extern char g_6b89a4[];

void* __cdecl fcn_0041e1d0(void*, int, int);

char __cdecl fcn_004545c0(char* e, char* ctx)
{
	char* d;
	Link* n;

	d = *(char**) (e + 0x1ec);
	if (d != 0 && *(int*) (d + 0x40c) != 0 && (e[0x217] & 1) != 0) {
		(*(int*) (ctx + 0x30))++;
		n = (Link*) fcn_0041e1d0(g_6b89a4, 8, 0x80);
		n->e = e;
		if (*(Link**) (ctx + 0x40) != 0) {
			(*(Link**) (ctx + 0x40))->next = n;
		} else {
			*(Link**) (ctx + 0x3c) = n;
		}
		*(Link**) (ctx + 0x40) = n;
	}
	return 1;
}
