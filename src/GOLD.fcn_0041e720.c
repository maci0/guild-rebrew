// FUNCTION: GOLD 0x0041e720
// fcn_0041e720 — if(arg) *(void**)0x146356c = arg->vtable[2](arg).

void __cdecl fcn_0041e720(void* a)
{
	if (a != 0) {
		*(void**) 0x146356c = (void*) ((void* (__stdcall*)(void*)) (*(void***) a)[2])(a);
	}
}
