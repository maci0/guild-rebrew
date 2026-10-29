/* ADDRESS: GOLDTL 0x00619504 */
/* Original is a __thiscall derived constructor: call the 0x6194de base ctor
 * with the receiver still in ecx, clear +0x10/+0x14 with `and dword ptr,0`,
 * overwrite the vtable and return the receiver. The call displacement is the
 * reference encoding; MASM inline asm cannot name the external symbol. */
void __declspec(naked) __fastcall fcn_00619504(void)
{
	__asm {
		_emit 0E8H
		_emit 0D5H
		_emit 0FFH
		_emit 0FFH
		_emit 0FFH
		and dword ptr [ecx + 10H], 0
		and dword ptr [ecx + 14H], 0
		mov dword ptr [ecx], 66770CH
		mov eax, ecx
		ret
	}
}
