// FUNCTION: GOLD 0x4644f0
// SIZE: 57
// FUNCTION: GOLDTL 0x460a50
// SIZE: 57

typedef struct {
	char pad20[0x20];
	char* (__cdecl* alloc)(char*, int, int);
	char pad24[4];
	char* pool;
} fcn_00460a50_ctx;
// SIZE 0x2c

void __cdecl fcn_00460a50(int a1, int a2, int a3, int a4, fcn_00460a50_ctx* c)
{
	char* p;

	p = c->alloc(c->pool, 1, 0x1c);
	if (p != 0) {
		p[0x10] = (char) a1;
		p[0x11] = (char) a2;
		*(int*) p = 0;
		*(int*) (p + 0x14) = a3;
		*(int*) (p + 0x18) = a4;
	}
}
