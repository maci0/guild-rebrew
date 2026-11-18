typedef int (__stdcall *FN_41f460)(int *);

int *__cdecl FindVideoById(int *);

/* ADDRESS: GOLDTL 0x0041f460 */
int __cdecl fcn_0041f460(int *videoId)
{
	int *video;
	int *iface;

	video = FindVideoById(videoId);
	if (video != 0) {
		iface = (int *) video[0x120 / 4];
		return (*(FN_41f460 *) (*iface + 0x20))(iface) >= 0;
	}
	return 0;
}
