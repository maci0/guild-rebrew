void __stdcall fcn_00613478(int flag);

/* ADDRESS: GOLDTL 0x005edcfa */
/* PSGP lazy-init stub for dispatch slot 0x006ad6ec (the slot itself holds
 * this address).  Native 17 bytes: push ebp / mov ebp,esp / push 1 / call
 * 0x00613478 / pop ebp / jmp dword ptr [0x006ad6ec], followed by the 6-byte
 * plain thunk at 0x005edd0b (jmp dword ptr [0x006ad6ec]), which the 23-byte
 * inventory extent merges in.  C emits the 13-byte body without the frame. */
void __cdecl fcn_005edcfa(void)
{
    fcn_00613478(1);
    (*(void (__stdcall **)(void))0x6ad6ec)();
}
