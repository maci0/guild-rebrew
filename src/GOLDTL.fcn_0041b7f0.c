/* ADDRESS: GOLDTL 0x006b5de0 */
extern void* g_6b5de0;
/* ADDRESS: GOLDTL 0x014ce820 */
extern char g_14ce820[];


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
	if (((int*)g_6b5de0) != 0) {
		hr = (*(Vtbl38**) ((int*)g_6b5de0))->fn(((int*)g_6b5de0), g_14ce820);
	}
	return hr == 0;
}
