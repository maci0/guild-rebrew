

typedef struct VIDEO_WIN_VIS_IFACE VIDEO_WIN_VIS_IFACE;
// SIZE 0x4
struct VIDEO_WIN_VIS_IFACE {
	int (__stdcall** vt)(VIDEO_WIN_VIS_IFACE*, int);
};

char* __cdecl FindVideoById(int);

int __cdecl SetVideoVisible(int videoId, int visible)
{
	char* video;
	VIDEO_WIN_VIS_IFACE* iface;

	video = FindVideoById(videoId);
	if (video != 0) {
		iface = *(VIDEO_WIN_VIS_IFACE**) (video + 0x130);
		return iface->vt[0x4c / 4](iface, visible ? -1 : 0) >= 0;
	}
	return 0;
}
