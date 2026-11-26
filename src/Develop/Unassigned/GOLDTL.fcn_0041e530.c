


__declspec(dllimport) long __stdcall DefWindowProcA(void* hwnd, unsigned int msg, unsigned int wp, long lp);
__declspec(dllimport) int __stdcall DestroyWindow(void* hwnd);

typedef struct VIDEO_CONTROL VIDEO_CONTROL;

// SIZE 0x28
typedef struct {
	void* fn[10];
} VIDEO_CONTROL_VTBL;

struct VIDEO_CONTROL {
	VIDEO_CONTROL_VTBL* vt;
};

long __cdecl PollVideoEvents(int id, long* p1, long* p2);
int __cdecl CloseVideo(int id);
char* __cdecl FindVideoByWindow(void* hwnd);

long __stdcall VideoWindowProc(void* hwnd, unsigned int msg, unsigned int wp, long lp)
{
	char* video;
	int id;
	VIDEO_CONTROL* ctrl;

	switch (msg) {
	case 2:
		video = FindVideoByWindow(hwnd);
		if (video != 0) {
			CloseVideo(*(int*) (video + 8));
		}
		break;
	case 0x100:
		if (wp == 0x20 || wp == 0x1b) {
			video = FindVideoByWindow(hwnd);
			if (video != 0) {
				ctrl = *(VIDEO_CONTROL**) (video + 0x120);
				((void(__stdcall*)(VIDEO_CONTROL*)) ctrl->vt->fn[9])(ctrl);
				CloseVideo(*(int*) (video + 8));
				DestroyWindow(hwnd);
				return 0;
			}
		}
		break;
	case 0x9021:
		id = lp;
		if (PollVideoEvents(id, (long*) &wp, &lp) == 1) {
			CloseVideo(id);
			DestroyWindow(hwnd);
			return 0;
		}
		break;
	default:
		return DefWindowProcA(hwnd, msg, wp, lp);
	}
	return 0;
}
