/* ADDRESS: GOLDTL 0x005f37c6 */
/* Original is a __thiscall slot probe: receiver in ecx, index in edx, and the
 * found path tail-jumps into the adjacent row 0x5f37dd. C cannot keep those
 * registers and emits an inline call instead of the tail jump, so the extent is
 * transcribed as naked assembly; the out-of-extent jump keeps its reference
 * displacement. */
void __declspec(naked) __fastcall fcn_005f37c6(void)
{
	__asm {
		xor edx, edx
		lea eax, [ecx + 8]
	probe:
		cmp dword ptr [eax], -1
		_emit 75H
		_emit 00DH
		inc edx
		add eax, 4
		cmp edx, 4
		jb probe
		or eax, 0FFFFFFFFH
		ret
	}
}
