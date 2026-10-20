/* ADDRESS: GOLDTL 0x005ed45f */
/* Body of the leading 6-byte PSGP dispatch thunk only: jmp dword ptr
 * [0x006ad6a8].  The remaining 19 bytes of the 25-byte inventory extent are
 * two further entries: the lazy-init stub at 0x005ed465 (push 1 / call
 * 0x00613478 / jmp dword ptr [0x006ad694]) and the plain thunk at
 * 0x005ed472 (jmp dword ptr [0x006ad694]). */
void __cdecl fcn_005ed45f(void)
{
    (*(void (__stdcall **)(void))0x6ad6a8)();
}
