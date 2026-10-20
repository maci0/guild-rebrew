/* D3DX8 external band. Native ABI is thiscall: self in ECX, two stack
 * arguments, ret 8. MSVC 6 C rejects __thiscall (C4234 is an error), so the
 * C89 reconstruction keeps the recovered algorithm but takes the object from
 * the stack; entry bytes cannot match. The stored 71-byte extent is this body
 * alone (no merged neighbour). */
void __stdcall fcn_0060d860(int v, int a1, int a2);

/* ADDRESS: GOLDTL 0x0060d8c7 */
void __cdecl fcn_0060d8c7(void* self, int a1, int a2)
{
	int v;
	int i;

	v = (*(int**) ((char*) self + 0x80))[a1];
	if (v == a1) {
		v = (*(int**) ((char*) self + 0xc4))[a1];
		i = a1;
		do {
			(*(int**) ((char*) self + 0x80))[i] = v;
			i = (*(int**) ((char*) self + 0xc4))[i];
		} while (i != a1);
	}
	fcn_0060d860(v, a1, a2);
}
