typedef int (__stdcall *VIDEO_PAUSE_FN)(int *);

int *__cdecl FindVideoById(int *);

/* ADDRESS: GOLDTL 0x0041f460 */
int __cdecl PauseVideo(int *videoId)
{
	int *video;
	int *iface;

	video = FindVideoById(videoId);
	if (video != 0) {
		iface = (int *) video[0x120 / 4];
		return (*(VIDEO_PAUSE_FN *) (*iface + 0x20))(iface) >= 0;
	}
	return 0;
}
