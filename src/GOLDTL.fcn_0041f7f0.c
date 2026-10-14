struct unk_41f7f0;

// SIZE 0xc
struct unkvtbl_41f7f0 {
	long (__stdcall* QueryInterface)(struct unk_41f7f0*, void*, void**);
	unsigned long (__stdcall* AddRef)(struct unk_41f7f0*);
	unsigned long (__stdcall* Release)(struct unk_41f7f0*);
};

// SIZE 0x4
struct unk_41f7f0 {
	struct unkvtbl_41f7f0* vtbl;
};

/* ADDRESS: GOLD 0x00423560 */
/* ADDRESS: GOLDTL 0x0041f7f0 */

/* Releases a video's DirectShow interfaces. */
void __cdecl fcn_0041f7f0(char* v)
{
	if (*(struct unk_41f7f0**) (v + 0x140) != 0) {
		(*(struct unk_41f7f0**) (v + 0x140))->vtbl->Release(*(struct unk_41f7f0**) (v + 0x140));
		*(struct unk_41f7f0**) (v + 0x140) = 0;
	}
	if (*(struct unk_41f7f0**) (v + 0x144) != 0) {
		(*(struct unk_41f7f0**) (v + 0x144))->vtbl->Release(*(struct unk_41f7f0**) (v + 0x144));
		*(struct unk_41f7f0**) (v + 0x144) = 0;
	}
	if (*(struct unk_41f7f0**) (v + 0x13c) != 0) {
		(*(struct unk_41f7f0**) (v + 0x13c))->vtbl->Release(*(struct unk_41f7f0**) (v + 0x13c));
		*(struct unk_41f7f0**) (v + 0x13c) = 0;
	}
	if (*(struct unk_41f7f0**) (v + 0x138) != 0) {
		(*(struct unk_41f7f0**) (v + 0x138))->vtbl->Release(*(struct unk_41f7f0**) (v + 0x138));
		*(struct unk_41f7f0**) (v + 0x138) = 0;
	}
	if (*(struct unk_41f7f0**) (v + 0x134) != 0) {
		(*(struct unk_41f7f0**) (v + 0x134))->vtbl->Release(*(struct unk_41f7f0**) (v + 0x134));
		*(struct unk_41f7f0**) (v + 0x134) = 0;
	}
	if (*(struct unk_41f7f0**) (v + 0x128) != 0) {
		(*(struct unk_41f7f0**) (v + 0x128))->vtbl->Release(*(struct unk_41f7f0**) (v + 0x128));
		*(struct unk_41f7f0**) (v + 0x128) = 0;
	}
	if (*(struct unk_41f7f0**) (v + 0x12c) != 0) {
		(*(struct unk_41f7f0**) (v + 0x12c))->vtbl->Release(*(struct unk_41f7f0**) (v + 0x12c));
		*(struct unk_41f7f0**) (v + 0x12c) = 0;
	}
	if (*(struct unk_41f7f0**) (v + 0x130) != 0) {
		(*(struct unk_41f7f0**) (v + 0x130))->vtbl->Release(*(struct unk_41f7f0**) (v + 0x130));
		*(struct unk_41f7f0**) (v + 0x130) = 0;
	}
	if (*(struct unk_41f7f0**) (v + 0x120) != 0) {
		(*(struct unk_41f7f0**) (v + 0x120))->vtbl->Release(*(struct unk_41f7f0**) (v + 0x120));
		*(struct unk_41f7f0**) (v + 0x120) = 0;
	}
	if (*(struct unk_41f7f0**) (v + 0x124) != 0) {
		(*(struct unk_41f7f0**) (v + 0x124))->vtbl->Release(*(struct unk_41f7f0**) (v + 0x124));
		*(struct unk_41f7f0**) (v + 0x124) = 0;
	}
	if (*(struct unk_41f7f0**) (v + 0x11c) != 0) {
		(*(struct unk_41f7f0**) (v + 0x11c))->vtbl->Release(*(struct unk_41f7f0**) (v + 0x11c));
		*(struct unk_41f7f0**) (v + 0x11c) = 0;
	}
}
