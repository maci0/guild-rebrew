

typedef struct {
	int (*pad[0x17]);
	int (__stdcall* setup)(void*, int, int, int, int, int);
} fcn_00418680_vtbl;
// SIZE 0x60

void __cdecl fcn_00418680(void)
{
	void* obj;
	fcn_00418680_vtbl* vt;

	obj = *(void**) 0x6b5de0;
	vt = (fcn_00418680_vtbl*) *(int**) obj;
	vt->setup(obj, 0xa00, 0x208, 0x44, 0, 0x6b5cb4);
	obj = *(void**) 0x6b5de0;
	vt = (fcn_00418680_vtbl*) *(int**) obj;
	vt->setup(obj, 0x1500, 0x208, 0x144, 0, 0x6b5cb8);
}
