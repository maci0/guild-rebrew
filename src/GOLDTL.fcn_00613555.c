typedef struct VTBL_613555 VTBL_613555;
struct VTBL_613555 {
	void* pad_000[2];
	void (__stdcall* m8)(void* obj);
};

__declspec(dllimport) int __stdcall DeleteObject(void* obj);
int __fastcall fcn_0062af4d(void* self);
int __fastcall fcn_0062af70(void* self);

/* D3DX8 external band. Native entry is thiscall with no stack arguments
 * (ECX = self, ret 0), which __fastcall reproduces. The stored 71-byte extent
 * merges this 58-byte body with the 13-byte member at 0x61358f. Remaining
 * delta: the native body schedules test ecx,ecx before the vtable store while
 * this build hoists the store above the test (bytes 6..13); the other 50
 * bytes agree. */
/* ADDRESS: GOLDTL 0x00613555 */
void __fastcall fcn_00613555(char* self)
{
	void* p;

	*(int*) self = 0x66701c;
	if (*(void**) (self + 0x48) != 0) {
		fcn_0062af4d(*(void**) (self + 0x48));
		fcn_0062af70(*(void**) (self + 0x48));
	}
	if (*(void**) (self + 8) != 0) {
		DeleteObject(*(void**) (self + 8));
	}
	p = *(void**) (self + 0x4c);
	if (p != 0) {
		(*(VTBL_613555**) p)->m8(p);
	}
}
