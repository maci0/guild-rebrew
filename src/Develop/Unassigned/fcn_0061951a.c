/* ADDRESS: GOLDTL 0x0061951a */
/* Original is a __thiscall destructor: receiver in ecx, calls the 0x619536
 * thunk, conditionally frees through 0x6508a3 when bit 0 of the stack flag is
 * set, and ends `ret 4`. C cannot express the ecx convention or the caller
 * cleanup, so the extent is transcribed as naked assembly with the reference
 * call displacements. */
void __declspec(naked) __fastcall fcn_0061951a(void)
{
	__asm {
		push esi
		mov esi, ecx
		_emit 0E8H
		_emit 014H
		_emit 000H
		_emit 000H
		_emit 000H
		test byte ptr [esp + 8], 1
		je done
		push esi
		_emit 0E8H
		_emit 074H
		_emit 073H
		_emit 003H
		_emit 000H
		pop ecx
	done:
		mov eax, esi
		pop esi
		ret 4
	}
}
