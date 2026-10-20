/* ADDRESS: GOLDTL 0x005eaeca */
/* Body of the leading 6-byte PSGP dispatch thunk only: jmp dword ptr
 * [0x006ad654].  The slot initially holds the lazy-init stub at 0x005eaebd.
 * The remaining 10 bytes of the 16-byte extent (0x005eaed0: fld dword
 * [esp+4] / call CIasin / ret) are the next function. */
void __cdecl fcn_005eaeca(void)
{
    (*(void (__stdcall **)(void))0x6ad654)();
}
