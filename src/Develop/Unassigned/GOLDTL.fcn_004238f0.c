extern int g_6b7d7c;
extern int g_6b7d7c;



void __cdecl msx_SetSampleLoopCount(int, int);

void __cdecl sb_SetVoiceLoopCount(int* p, int value)
{
	if (*(int*) ((char*)&g_6b7d7c) == 0) {
		return;
	}
	if (p == 0) {
		return;
	}
	*(int*) ((char*) p + 0xc) = value;
	msx_SetSampleLoopCount(*(int*) p, value);
}
