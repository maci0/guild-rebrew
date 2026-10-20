typedef struct T5f40ed {
	int v[16];
} T5f40ed;

/* Native callee takes its first argument in ecx (__thiscall); C89/VC6 has no
   C-level __thiscall, so the declaration below is the closest faithful form. */
extern void __cdecl fcn_005f0144(void* self, int a);

/* The recorded 69-byte extent also covers a second native function at
   0x5f4103 (release/destructor helper), which has no separate identity. */

/* ADDRESS: GOLDTL 0x005f40ed */

int __cdecl fcn_005f40ed(int a)
{
	T5f40ed buf;

	fcn_005f0144(&buf, a);
	return buf.v[1];
}
