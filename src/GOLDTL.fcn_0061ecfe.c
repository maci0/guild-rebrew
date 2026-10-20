typedef struct Vtbl61ecfe {
	int (*f0)(void);  /* 0x0 */
	int (*f1)(void);  /* 0x4 */
	int (*f2)(void);  /* 0x8 */
	int (__cdecl * f3)(void* obj, void* buf);  /* 0xc */
} Vtbl61ecfe;

/* D3DX8 external band. The native body keeps an EBP frame and uses the size
 * form of the epilogue (pop ecx twice, leave), so the pragmas select the frame
 * and the same scheduling. The stored 69-byte extent merges four entries:
 * 0x61ecfe (29, this file), 0x61ed1b (1), 0x61ed1c (21), 0x61ed31 (17) and
 * 0x61ed42 (1). Remaining delta at 29: the object pointer lives in EAX in the
 * native body, this build uses ECX, and the vtable load is scheduled after the
 * buffer address (bytes 12..21). */
#pragma optimize("y", off)
#pragma optimize("s", on)

/* ADDRESS: GOLDTL 0x0061ecfe */
int __cdecl fcn_0061ecfe(void* obj)
{
	char buf[0xc8];

	return (*(Vtbl61ecfe**) obj)->f3(obj, buf);
}
