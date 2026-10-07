// FUNCTION: GOLDTL 0x43b850

typedef int (__cdecl* fcn_0043b850_f)(char*, int, char*);

extern int g_67a590;
extern int g_67a370;
void __cdecl fcn_004011f0(int, void*);
int __cdecl fcn_004011a0(int, void*);
int __cdecl fcn_0043b500(char*);
char __cdecl fcn_0043b660(char*, int, int, char*);

void __cdecl fcn_0043b850(int r)
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
		fcn_0043b660(((char*)g_67a370), id, (*(fcn_0043b850_f*)&g_67a590)(((char*)g_67a370), id, val), val);
	}
}
