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

extern void* g_6b5de4;
extern void* g_6b5de0;
extern void* g_6b5ddc;
extern unsigned long d3_LastReleaseRefCount;

void __cdecl d3_InvalidateDeviceResources(void);


/* Releases the Direct3D sprite, device and interface objects. */
/* ADDRESS: GOLDTL 0x0041b4b0 */
/* ADDRESS: GOLDDE 0x004191f0 */
void __cdecl d3_ReleaseGraphicsInterfaces(void)
{
	d3_InvalidateDeviceResources();
	if ((*(struct unk_41b4b0**)&g_6b5de4) != 0) {
		d3_LastReleaseRefCount = (*(struct unk_41b4b0**)&g_6b5de4)->vtbl->Release((*(struct unk_41b4b0**)&g_6b5de4));
		(*(struct unk_41b4b0**)&g_6b5de4) = 0;
	}
	if ((*(struct unk_41b4b0**)&g_6b5de0) != 0) {
		d3_LastReleaseRefCount = (*(struct unk_41b4b0**)&g_6b5de0)->vtbl->Release((*(struct unk_41b4b0**)&g_6b5de0));
		(*(struct unk_41b4b0**)&g_6b5de0) = 0;
	}
	if ((*(struct unk_41b4b0**)&g_6b5ddc) != 0) {
		d3_LastReleaseRefCount = (*(struct unk_41b4b0**)&g_6b5ddc)->vtbl->Release((*(struct unk_41b4b0**)&g_6b5ddc));
		(*(struct unk_41b4b0**)&g_6b5ddc) = 0;
	}
}
