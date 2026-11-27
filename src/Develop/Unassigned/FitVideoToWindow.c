struct VIDEO_WIN_OBJ;

// SIZE 0xa4
struct VIDEO_WIN_VTBL {
	char pad0[0x88];
	long (__stdcall* GetVideoSize)(struct VIDEO_WIN_OBJ*, long*, long*);
	char pad8c[0x9c - 0x8c];
	long (__stdcall* SetWindowPosition)(struct VIDEO_WIN_OBJ*, long, long, long, long);
	long (__stdcall* GetWindowPosition)(struct VIDEO_WIN_OBJ*, long*, long*, long*, long*);
};

// SIZE 0x4
struct VIDEO_WIN_OBJ {
	struct VIDEO_WIN_VTBL* vtbl;
};

// SIZE 0x10
struct VIDEO_FIT_RECT {
	long left;
	long top;
	long right;
	long bottom;
};

__declspec(dllimport) int __stdcall GetClientRect(void*, struct VIDEO_FIT_RECT*);

char* __cdecl FindVideoById(int);


/* Fits a video into its window: stretched to the window width keeping the
 * aspect ratio, or centred at its own size. */
/* ADDRESS: GOLDTL 0x0041f670 */
int __cdecl FitVideoToWindow(int id)
{
	char* v;
	long hr;
	long x;
	long y;
	long w;
	long h;
	long nh;
	struct VIDEO_WIN_OBJ* win;
	struct VIDEO_FIT_RECT rc;

	v = FindVideoById(id);
	if (v != 0) {
		if (*(int*) (v + 0xc) & 2) {
			GetClientRect(*(void**) (v + 0x114), &rc);
			if (*(int*) (v + 0xc) & 4) {
				hr = (*(struct VIDEO_WIN_OBJ**) (v + 0x128))->vtbl->GetVideoSize(*(struct VIDEO_WIN_OBJ**) (v + 0x128), &x, &w);
				if (hr < 0) {
					return 0;
				}
				w = (rc.right - rc.left) * w;
				nh = (long) ((float) w / x);
				rc.top = ((rc.bottom - rc.top) >> 1) - (nh >> 1);
				rc.bottom = nh + rc.top;
			}
			hr = (*(struct VIDEO_WIN_OBJ**) (v + 0x130))->vtbl->SetWindowPosition(*(struct VIDEO_WIN_OBJ**) (v + 0x130), rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top);
			return hr < 0;
		}
		if (*(int*) (v + 0xc) & 1) {
			hr = (*(struct VIDEO_WIN_OBJ**) (v + 0x130))->vtbl->GetWindowPosition(*(struct VIDEO_WIN_OBJ**) (v + 0x130), &x, &y, &w, &h);
			if (hr < 0) {
				return 0;
			}
			GetClientRect(*(void**) (v + 0x114), &rc);
			win = *(struct VIDEO_WIN_OBJ**) (v + 0x130);
			x = ((rc.right - rc.left) >> 1) - (w >> 1);
			y = ((rc.bottom - rc.top) >> 1) - (h >> 1);
			hr = win->vtbl->SetWindowPosition(win, x, y, w, h);
			return hr >= 0;
		}
	}
	return 0;
}
