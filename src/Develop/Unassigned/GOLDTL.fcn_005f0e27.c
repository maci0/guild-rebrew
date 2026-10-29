typedef struct Obj5f0e27 {
	char pad0[0x28];
	void* inner;
} Obj5f0e27;

/* ADDRESS: GOLDTL 0x005f0e27 */
/* Native ABI is __thiscall with two stack arguments (ret 8).  MSVC 6 C
 * rejects __thiscall (C4234), so __fastcall carries self in ecx and its
 * unused edx slot is the dummy parameter.  The native body ends after
 * ret 8 at 0x005f0e45; the stored 41-byte extent also merges the separate
 * 10-byte routine at 0x005f0e46. */
void __fastcall fcn_005f0e27(Obj5f0e27* self, int d1, unsigned int a1,
	unsigned int a2)
{
	void* obj;

	obj = self->inner;
	(*(void (__stdcall **)(void*, int, int, unsigned int, unsigned int))
	  ((char*)(*(void**)obj) + 0x2c))(obj, 0, 0, a1, a2 | 0x800);
}
