struct unk_41b4b0;

// SIZE 0xc
struct unkvtbl_41b4b0 {
	long (__stdcall* QueryInterface)(struct unk_41b4b0*, void*, void**);
	unsigned long (__stdcall* AddRef)(struct unk_41b4b0*);
	unsigned long (__stdcall* Release)(struct unk_41b4b0*);
};

// SIZE 0x4
struct unk_41b4b0 {
	struct unkvtbl_41b4b0* vtbl;
};

extern struct unk_41b4b0* g_6b5de4;
extern struct unk_41b4b0* g_6b5de0;
extern struct unk_41b4b0* g_6b5ddc;
extern unsigned long g_14ce728;

void __cdecl fcn_0041b7c0(void);

// FUNCTION: GOLDTL 0x41b4b0
// SIZE: 96

/* Releases the Direct3D sprite, device and interface objects. */
void __cdecl fcn_0041b4b0(void)
{
	fcn_0041b7c0();
	if (g_6b5de4 != 0) {
		g_14ce728 = g_6b5de4->vtbl->Release(g_6b5de4);
		g_6b5de4 = 0;
	}
	if (g_6b5de0 != 0) {
		g_14ce728 = g_6b5de0->vtbl->Release(g_6b5de0);
		g_6b5de0 = 0;
	}
	if (g_6b5ddc != 0) {
		g_14ce728 = g_6b5ddc->vtbl->Release(g_6b5ddc);
		g_6b5ddc = 0;
	}
}
