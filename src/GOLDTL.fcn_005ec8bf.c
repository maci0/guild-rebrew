void __stdcall fcn_00613478(int flag);

/* ADDRESS: GOLDTL 0x005ec8bf */
/* PSGP lazy-init stub for dispatch slot 0x006ad6d4 (the slot itself holds
 * this address).  Native 17 bytes: push ebp / mov ebp,esp / push 1 / call
 * 0x00613478 / pop ebp / jmp dword ptr [0x006ad6d4].  The init call plus the
 * tail jump compile to the 13-byte body below; C does not emit the EBP frame
 * (the sibling stub at 0x005eb307 has the same 13-byte shape). */
void __cdecl fcn_005ec8bf(void)
{
    fcn_00613478(1);
    (*(void (__stdcall **)(void))0x6ad6d4)();
}
