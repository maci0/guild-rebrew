typedef struct fcn_004760c0_com fcn_004760c0_com;
typedef struct {
	char pad0[0x38];
	int(__stdcall* f38)(fcn_004760c0_com*, int, void*);
} fcn_004760c0_vtbl;
// SIZE 0x3c
struct fcn_004760c0_com {
	fcn_004760c0_vtbl* vtbl;
};

typedef struct {
	char pad0[0x20];
	fcn_004760c0_com* f20;
} fcn_004760c0_obj;

// FUNCTION: GOLDTL 0x4760c0
// SIZE: 31

int __cdecl fcn_004760c0(fcn_004760c0_obj* o, void* desc)
{
	fcn_004760c0_com* c;

	c = o->f20;
	if (c == 0)
		return 0;
	return c->vtbl->f38(c, 0, desc) == 0;
}
