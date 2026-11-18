

typedef struct I41f630 I41f630;
// SIZE 0x4
struct I41f630 {
	int (__stdcall** vt)(I41f630*, int);
};

char* __cdecl FindVideoById(int);

int __cdecl fcn_0041f630(int videoId, int a2)
{
	char* video;
	I41f630* iface;

	video = FindVideoById(videoId);
	if (video != 0) {
		iface = *(I41f630**) (video + 0x130);
		return iface->vt[0x4c / 4](iface, a2 ? -1 : 0) >= 0;
	}
	return 0;
}
