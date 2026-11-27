extern void* g_6b5de0;
extern char g_14ce820[];


typedef struct
{
	char pad[0x38];
	int (__stdcall* fn)(void*, void*);
} D3_DEVICE_RESET_VTBL;
// SIZE 0x3c

char __cdecl d3_ResetGraphicsDevice(void)
{
	int hr;

	hr = 0x80004005;
	if (((int*)g_6b5de0) != 0) {
		hr = (*(D3_DEVICE_RESET_VTBL**) ((int*)g_6b5de0))->fn(((int*)g_6b5de0), g_14ce820);
	}
	return hr == 0;
}
