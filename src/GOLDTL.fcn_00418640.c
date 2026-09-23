// FUNCTION: GOLDTL 0x418640
// SIZE: 61

typedef struct {
	int (*f0)(void);
	int (*f1)(void);
	int (__stdcall* release)(void*);
} fcn_00418640_vtbl;
// SIZE 0xc

void __cdecl fcn_00418640(void)
{
	void** p;

	p = (void**) *(int*) 0x6b5cb4;
	if (p != 0) {
		*(int*) 0x14ce728 = ((fcn_00418640_vtbl*) p[0])->release(p);
		*(int*) 0x6b5cb4 = 0;
	}
	p = (void**) *(int*) 0x6b5cb8;
	if (p != 0) {
		*(int*) 0x14ce728 = ((fcn_00418640_vtbl*) p[0])->release(p);
		*(int*) 0x6b5cb8 = 0;
	}
}
