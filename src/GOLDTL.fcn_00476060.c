typedef struct fcn_00476060_com fcn_00476060_com;
typedef struct {
	char pad0[0x28];
	int(__stdcall* f28)(fcn_00476060_com*);
	char pad2c[0x18];
	int(__stdcall* f44)(fcn_00476060_com*, int);
} fcn_00476060_vtbl;
// SIZE 0x48
struct fcn_00476060_com {
	fcn_00476060_vtbl* vtbl;
};

typedef struct {
	char pad0[0xc];
	int fc;
	int f10;
	char pad14[0x8];
	int f1c;
	fcn_00476060_com* f20;
	fcn_00476060_com* f24;
	char pad28[0x14];
	int f3c;
} fcn_00476060_obj;

// FUNCTION: GOLDTL 0x476060
// SIZE: 85

int __cdecl fcn_00476060(fcn_00476060_obj* o)
{
	if (o->f3c == 0)
		return 0;
	if (o->f20 != 0) {
		o->f20->vtbl->f44(o->f20, 0);
		o->f1c = 0;
		o->fc = 0;
		o->f10 = 0;
	} else if (o->f24 != 0) {
		o->f24->vtbl->f28(o->f24);
		o->f1c = 0;
		o->fc = 0;
		o->f10 = 0;
	}
	o->f3c = 0;
	return 1;
}
