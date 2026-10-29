

/* GOLD twin of GOLDTL fcn_004545c0: the enable field is 0x104 (GOLDTL 0x40c)
 * and the flag is bit 4 of byte 0x213 (GOLDTL: bit 1 of 0x217). */

// SIZE 0x8
typedef struct Link {
	char* e;
	struct Link* next;
} Link;

extern char g_633db4[];

void* __cdecl m_PoolAlloc(void*, int, int);

char __cdecl fcn_00457c80(char* e, char* ctx)
{
	char* d;
	Link* n;

	d = *(char**) (e + 0x1ec);
	if (d != 0 && *(int*) (d + 0x104) != 0 && (e[0x213] & 4) != 0) {
		(*(int*) (ctx + 0x30))++;
		n = (Link*) m_PoolAlloc(g_633db4, 8, 0x80);
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
