// FUNCTION: GOLD 0x0041e740
// SIZE: 21
// fcn_0041e740 — if(arg) arg->vtable[32](arg, 0).

void __cdecl fcn_0041e740(void* a)
{
	if (a != 0) {
		((void (__stdcall*)(void*, int)) (*(void***) a)[32])(a, 0);
	}
}
