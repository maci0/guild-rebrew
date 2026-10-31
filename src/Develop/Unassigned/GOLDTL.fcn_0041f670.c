struct unk_41f670;

// SIZE 0xa4
struct vtbl_41f670 {
	char pad0[0x88];
	long (__stdcall* GetVideoSize)(struct unk_41f670*, long*, long*);
	char pad8c[0x9c - 0x8c];
	long (__stdcall* SetWindowPosition)(struct unk_41f670*, long, long, long, long);
	long (__stdcall* GetWindowPosition)(struct unk_41f670*, long*, long*, long*, long*);
};

// SIZE 0x4
struct unk_41f670 {
	struct vtbl_41f670* vtbl;
};

// SIZE 0x10
struct rect_41f670 {
	long left;
	long top;
	long right;
	long bottom;
};

__declspec(dllimport) int __stdcall GetClientRect(void*, struct rect_41f670*);

char* __cdecl FindVideoById(int);


/* Fits a video into its window: stretched to the window width keeping the
 * aspect ratio, or centred at its own size. */
/* ADDRESS: GOLDTL 0x0041f670 */
int __cdecl fcn_0041f670(int id)
{
	char* v;
	long hr;
	long x;
	long y;
	long w;
	long h;
	long nh;
	struct unk_41f670* win;
	struct rect_41f670 rc;

	v = FindVideoById(id);
	if (v != 0) {
		if (*(int*) (v + 0xc) & 2) {
			GetClientRect(*(void**) (v + 0x114), &rc);
			if (*(int*) (v + 0xc) & 4) {
				hr = (*(struct unk_41f670**) (v + 0x128))->vtbl->GetVideoSize(*(struct unk_41f670**) (v + 0x128), &x, &w);
				if (hr < 0) {
					return 0;
				}
				w = (rc.right - rc.left) * w;
				nh = (long) ((float) w / x);
				rc.top = ((rc.bottom - rc.top) >> 1) - (nh >> 1);
				rc.bottom = nh + rc.top;
			}
			hr = (*(struct unk_41f670**) (v + 0x130))->vtbl->SetWindowPosition(*(struct unk_41f670**) (v + 0x130), rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top);
			return hr < 0;
		}
		if (*(int*) (v + 0xc) & 1) {
			hr = (*(struct unk_41f670**) (v + 0x130))->vtbl->GetWindowPosition(*(struct unk_41f670**) (v + 0x130), &x, &y, &w, &h);
			if (hr < 0) {
				return 0;
			}
			GetClientRect(*(void**) (v + 0x114), &rc);
			win = *(struct unk_41f670**) (v + 0x130);
			x = ((rc.right - rc.left) >> 1) - (w >> 1);
			y = ((rc.bottom - rc.top) >> 1) - (h >> 1);
			hr = win->vtbl->SetWindowPosition(win, x, y, w, h);
			return hr >= 0;
		}
	}
	return 0;
}
