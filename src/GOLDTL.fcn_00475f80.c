typedef struct fcn_00475f80_com fcn_00475f80_com;
typedef struct {
	char pad0[0x8];
	int(__stdcall* release)(fcn_00475f80_com*);
} fcn_00475f80_vtbl;
// SIZE 0xc
struct fcn_00475f80_com {
	fcn_00475f80_vtbl* vtbl;
};

typedef struct {
	char pad0[0x20];
	fcn_00475f80_com* f20;
	fcn_00475f80_com* f24;
	char pad28[0x14];
	int f3c;
	int f40;
} fcn_00475f80_obj;

int __cdecl fcn_00476060(fcn_00475f80_obj*);
void __cdecl m_FreeTracked(void*);

/* ADDRESS: GOLDTL 0x00475f80 */

int __cdecl fcn_00475f80(fcn_00475f80_obj* o)
{
	if (o == 0)
		return 0;
	if (o->f3c != 0)
		fcn_00476060(o);
	if (o->f40 == 0) {
		if (o->f24 != 0)
			o->f24->vtbl->release(o->f24);
		if (o->f20 != 0)
			o->f20->vtbl->release(o->f20);
	}
	m_FreeTracked(o);
	return 1;
}
