// FUNCTION: GOLDTL 0x43b7b0
// SIZE: 147

typedef int (__cdecl* fcn_0043b7b0_f)(char*, int, char*);

extern fcn_0043b7b0_f g_67a590;

void __cdecl fcn_004011f0(int, void*);
int __cdecl fcn_004011a0(int, void*);
int __cdecl fcn_0043b500(char*);
char __cdecl fcn_0043b580(char*, int, int, char*);

void __cdecl fcn_0043b7b0(int r, char* o)
{
	int n;
	char val[0x100];
	char name[0x100];
	int i;
	int id;

	fcn_004011f0(r, &n);
	for (i = 0; i < n; i++) {
		fcn_004011a0(r, name);
		id = fcn_0043b500(name);
		fcn_004011a0(r, val);
		if (o != 0) {
			fcn_0043b580(o, id, g_67a590(o, id, val), val);
		}
	}
}
