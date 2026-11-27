

typedef struct VIDEO_WIN_FS_SET_IFACE VIDEO_WIN_FS_SET_IFACE;
// SIZE 0x4
struct VIDEO_WIN_FS_SET_IFACE {
	int (__stdcall** vt)(VIDEO_WIN_FS_SET_IFACE*, int);
};

char* __cdecl FindVideoById(int);

int __cdecl SetVideoFullscreen(int videoId, int enabled)
{
	char* p;
	VIDEO_WIN_FS_SET_IFACE* o;
	int r;

	p = FindVideoById(videoId);
	if (p != 0) {
		o = *(VIDEO_WIN_FS_SET_IFACE**) (p + 0x130);
		r = o->vt[0x90 / 4](o, enabled ? -1 : 0);
		if (r == 0 || r == 1) {
			return 1;
		}
	}
	return 0;
}
