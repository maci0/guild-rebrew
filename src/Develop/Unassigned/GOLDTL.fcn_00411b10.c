


#include "client_input.h"























void __cdecl io_ShutdownInput(void)
{
	g_14ce89c = 0;
	io_AcquireMouse(0);
	io_AcquireKeyboard(0);
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
