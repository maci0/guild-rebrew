/* ADDRESS: GOLDTL 0x005ec938 */
/* Original is a linker/compiler import thunk: absolute memory jump into the
 * 0x6ad6dc import slot. MSVC 6 C has no spelling for a naked absolute jump, so
 * the six reference bytes are emitted verbatim. */
void __declspec(naked) __cdecl fcn_005ec938(void)
{
	__asm {
		_emit 0FFH
		_emit 025H
		_emit 0DCH
		_emit 0D6H
		_emit 06AH
		_emit 000H
	}
}
