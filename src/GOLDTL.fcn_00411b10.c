// FUNCTION: GOLDTL 0x00411b10
// SIZE: 107

#include <windows.h>

typedef struct Com Com;

// SIZE 0xc
typedef struct {
	void* QueryInterface;
	void* AddRef;
	ULONG (__stdcall* Release)(Com* self);
} ComVtbl;

// SIZE 0x4
struct Com {
	ComVtbl* vtbl;
};

extern int g_14ce89c;
extern Com* g_14ce90c;
extern Com* g_14ce8a0;
extern Com* g_14cf954;
extern HANDLE g_14cf94c;
void __cdecl fcn_004117f0(int a);
void __cdecl fcn_004117c0(int a);

void __cdecl fcn_00411b10(void)
{
	g_14ce89c = 0;
	fcn_004117f0(0);
	fcn_004117c0(0);
	if (g_14ce90c != 0) {
		g_14ce90c->vtbl->Release(g_14ce90c);
		g_14ce8a0 = 0;
	} else if (g_14ce8a0 != 0) {
		g_14ce8a0->vtbl->Release(g_14ce8a0);
		g_14ce8a0 = 0;
	}
	if (g_14cf954 != 0) {
		g_14cf954->vtbl->Release(g_14cf954);
		g_14cf954 = 0;
	}
	if (g_14cf94c != 0) {
		CloseHandle(g_14cf94c);
		g_14cf94c = 0;
	}
}
