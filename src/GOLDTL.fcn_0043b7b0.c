

typedef int (__cdecl* fcn_0043b7b0_f)(char*, int, char*);

extern int g_67a590;

int __cdecl fcn_004011f0(void* stream, void* dst);
char* __cdecl fcn_004011a0(void* stream, char* text);
int __cdecl fcn_0043b500(char*);
char __cdecl fcn_0043b580(char*, int, int, char*);

void __cdecl fcn_0043b7b0(void* r, char* o)
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
			fcn_0043b580(o, id, (*(fcn_0043b7b0_f*)&g_67a590)(o, id, val), val);
		}
	}
}
