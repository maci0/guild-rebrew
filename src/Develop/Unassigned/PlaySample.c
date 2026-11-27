void* __cdecl sb_PrepareVoice(int, int);
void __cdecl sb_SetVoiceLoopCount(void*, int);
void __cdecl sb_StartVoice(void*, int, int);

/* ADDRESS: GOLDTL 0x00410f50 */
void* __cdecl PlaySample(int* sampleId, int* playbackControl)
{
	void* h;

	if (*(int*) ((char*) *(void**) 0x6b7e98 + 0x104) != *(int*) 0x6791c8)
		return 0;
	h = sb_PrepareVoice(0, *sampleId);
	if (h != 0) {
		sb_SetVoiceLoopCount(h, *playbackControl);
		sb_StartVoice(h, 0, 0);
	} else {
		sb_PrepareVoice(0, *sampleId);
	}
	return h;
}
