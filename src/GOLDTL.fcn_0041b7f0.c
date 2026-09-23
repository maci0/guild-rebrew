// GLOBAL: GOLDTL 0x6b5de0
extern int* g_6b5de0;
// GLOBAL: GOLDTL 0x14ce820
extern char g_14ce820[];
// FUNCTION: GOLDTL 0x41b7f0
// SIZE: 36

typedef struct
{
	char pad[0x38];
	int (__stdcall* fn)(void*, void*);
} Vtbl38;
// SIZE 0x3c

char __cdecl fcn_0041b7f0(void)
{
	int hr;

	hr = 0x80004005;
	if (g_6b5de0 != 0) {
		hr = (*(Vtbl38**) g_6b5de0)->fn(g_6b5de0, g_14ce820);
	}
	return hr == 0;
}
