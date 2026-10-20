/* ADDRESS: GOLDTL 0x005ed44c */
/* Body of the leading 6-byte PSGP dispatch thunk only: jmp dword ptr
 * [0x006ad6a4].  The 13 bytes after it (0x005ed452: push 1 / call
 * 0x00613478 / jmp dword ptr [0x006ad6a8]) are the lazy-init stub of the
 * next dispatch slot, merged into this 19-byte inventory extent. */
void __cdecl fcn_005ed44c(void)
{
    (*(void (__stdcall **)(void))0x6ad6a4)();
}
