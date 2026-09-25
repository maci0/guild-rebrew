void* __cdecl fcn_0064e2f9(const char*, const char*);
int __cdecl fcn_0064e48f(void*, int, int);
int __cdecl fcn_0064ed28(const void*, int, int, void*);
int __cdecl fcn_0064e1fd(void*);

extern char g_6790b0[];

// FUNCTION: GOLDTL 0x479ff0
// SIZE: 70

int __cdecl fcn_00479ff0(const char* name, char* data)
{
	void* f;

	f = fcn_0064e2f9(name, g_6790b0);
	if (f == 0)
		return 0;
	fcn_0064e48f(f, 0, 0);
	fcn_0064ed28(data, *(int*) (data + 0x30), 1, f);
	fcn_0064e1fd(f);
	return 1;
}
