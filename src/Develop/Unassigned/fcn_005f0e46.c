typedef int (__stdcall* Fn_005f0e46)(void*);

/* The native body calls the slot and returns the callee's EAX; a C return
 * of the call result makes VC6 tail-jump through the slot instead, so the
 * call is spelled as a plain void call. */
/* ADDRESS: GOLDTL 0x005f0e46 */
void __fastcall fcn_005f0e46(void* self)
{
	void* p;
	Fn_005f0e46 fn;

	p = *(void**) ((char*) self + 0x28);
	fn = *(Fn_005f0e46*) ((char*) *(void**) p + 0x30);
	fn(p);
}
