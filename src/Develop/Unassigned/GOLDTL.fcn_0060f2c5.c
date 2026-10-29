/* D3DX8 external band. Native ABI is thiscall: self in ECX, two stack
 * arguments, ret 8. MSVC 6 C rejects __thiscall, so this C form takes the
 * object from the stack and the entry bytes cannot match. The stored 84-byte
 * extent is this body alone. */
int __stdcall fcn_0060f24d(int v, unsigned short a1, unsigned short a2);

/* ADDRESS: GOLDTL 0x0060f2c5 */
int __cdecl fcn_0060f2c5(void* self, unsigned short key, unsigned short a2)
{
	unsigned short* map;
	unsigned short* links;
	unsigned short v;
	unsigned short k;

	map = *(unsigned short**) ((char*) self + 0x80);
	v = map[key];
	if (v == key) {
		links = *(unsigned short**) ((char*) self + 0xc4);
		v = links[key];
		k = key;
		do {
			map[k] = v;
			k = links[k];
		} while (k != key);
	}
	fcn_0060f24d(v, key, a2);
	return 0;
}
