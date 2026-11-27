

char* __cdecl FindVideoById(int);

typedef int (__stdcall* VIDEO_STOP_FN)(void*);

int __cdecl StopVideo(int videoId)
{
	char* node;
	void* obj;

	node = FindVideoById(videoId);
	if (node != 0) {
		obj = *(void**) (node + 0x120);
		return ((VIDEO_STOP_FN) ((int*) *(int*) obj)[9])(obj) == 0;
	}
	return 0;
}
