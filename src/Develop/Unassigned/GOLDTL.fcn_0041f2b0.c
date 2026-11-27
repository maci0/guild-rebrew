

typedef struct VIDEO_WIN_FS_GET_IFACE VIDEO_WIN_FS_GET_IFACE;
// SIZE 0x4
struct VIDEO_WIN_FS_GET_IFACE {
	int (__stdcall** vt)(VIDEO_WIN_FS_GET_IFACE*, int*);
};

char* __cdecl FindVideoById(int);

int __cdecl IsVideoWindowed(int videoId)
{
	char* p;
	VIDEO_WIN_FS_GET_IFACE* o;

	p = FindVideoById(videoId);
	if (p != 0) {
		o = *(VIDEO_WIN_FS_GET_IFACE**) (p + 0x130);
		if (o->vt[0x8c / 4](o, &videoId) >= 0 && videoId == 0) {
			return 1;
		}
	}
	return 0;
}
