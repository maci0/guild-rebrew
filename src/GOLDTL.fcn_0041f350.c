struct unk_41f350;

// SIZE 0x20
struct ctlvtbl_41f350 {
	char pad0[0x1c];
	long (__stdcall* Run)(struct unk_41f350*);
};

// SIZE 0x4
struct unk_41f350 {
	struct ctlvtbl_41f350* vtbl;
};

// SIZE 0x1c
struct msg_41f350 {
	void* hwnd;
	unsigned int message;
	unsigned int wParam;
	long lParam;
	unsigned long time;
	long x;
	long y;
};

__declspec(dllimport) int __stdcall ShowWindow(void*, int);
__declspec(dllimport) int __stdcall BringWindowToTop(void*);
__declspec(dllimport) int __stdcall SetWindowPos(void*, void*, int, int, int, int, unsigned int);
__declspec(dllimport) int __stdcall UpdateWindow(void*);
__declspec(dllimport) int __stdcall PeekMessageA(struct msg_41f350*, void*, unsigned int, unsigned int, unsigned int);
__declspec(dllimport) int __stdcall GetMessageA(struct msg_41f350*, void*, unsigned int, unsigned int);
__declspec(dllimport) int __stdcall TranslateMessage(const struct msg_41f350*);
__declspec(dllimport) long __stdcall DispatchMessageA(const struct msg_41f350*);
__declspec(dllimport) int __stdcall IsWindow(void*);
__declspec(dllimport) void __stdcall Sleep(unsigned long);

char* __cdecl fcn_0041f9b0(int);

// FUNCTION: GOLD 0x00423390
// SIZE: 270
// FUNCTION: GOLDTL 0x41f350
// SIZE: 270

/* Shows a video window topmost and starts playback; a modal video pumps
 * messages until its window closes. */
int __cdecl fcn_0041f350(int id)
{
	char* v;
	long hr;
	struct msg_41f350 msg;

	v = fcn_0041f9b0(id);
	if (v != 0) {
		ShowWindow(*(void**) (v + 0x114), 5);
		BringWindowToTop(*(void**) (v + 0x114));
		SetWindowPos(*(void**) (v + 0x114), (void*) -1, 0, 0, 0, 0, 3);
		UpdateWindow(*(void**) (v + 0x114));
		hr = (*(struct unk_41f350**) (v + 0x120))->vtbl->Run(*(struct unk_41f350**) (v + 0x120));
		if (*(int*) (v + 0xc) & 0x100) {
			for (;;) {
				if (PeekMessageA(&msg, *(void**) (v + 0x114), 0, 0, 0)) {
					if (!GetMessageA(&msg, *(void**) (v + 0x114), 0, 0)) {
						break;
					}
					TranslateMessage(&msg);
					DispatchMessageA(&msg);
					if (msg.message == 2) {
						break;
					}
				} else {
					if (!IsWindow(*(void**) (v + 0x114))) {
						break;
					}
					Sleep(100);
				}
			}
			return 1;
		}
		return hr >= 0;
	}
	return 0;
}
