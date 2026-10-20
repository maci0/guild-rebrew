/* D3DX8 external band. Native is a scalar deleting destructor: thiscall
 * (ECX = self, ret 0) with the delete flag pushed for the virtual call, so the
 * callee sees the object in ECX and one stack dword and cleans 4 bytes. MSVC 6
 * C cannot place "this" in ECX for an indirect call, so this C form passes the
 * flag through a __cdecl pointer and the call site differs (push/push the
 * object, caller cleanup). Non-C ABI class. The stored 69-byte extent merges
 * four entries: 0x620787 (30, this file), 0x6207a5 (17), 0x6207b6 (13) and
 * 0x6207c3 (9). */
/* ADDRESS: GOLDTL 0x00620787 */
void __fastcall fcn_00620787(char* self)
{
	void** p;

	p = *(void***) (self + 4);
	if (p != 0) {
		(*(void (__cdecl**) (int)) *p) (1);
	}
	p = *(void***) self;
	if (p != 0) {
		(*(void (__cdecl**) (int)) *p) (1);
	}
}
