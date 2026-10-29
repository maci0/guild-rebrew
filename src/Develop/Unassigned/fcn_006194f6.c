/* ADDRESS: GOLDTL 0x006194f6 */
/* Original is a __thiscall derived constructor tail: call the base ctor at
 * 0x6194de (receiver stays in ecx), overwrite the vtable and return the
 * receiver in eax. The relative call encoding from the reference is emitted
 * verbatim because MASM inline asm cannot reference the external ctor symbol. */
void __declspec(naked) __fastcall fcn_006194f6(void)
{
	__asm {
		_emit 0E8H
		_emit 0E3H
		_emit 0FFH
		_emit 0FFH
		_emit 0FFH
		mov dword ptr [ecx], 6676F0H
		mov eax, ecx
		ret
	}
}
