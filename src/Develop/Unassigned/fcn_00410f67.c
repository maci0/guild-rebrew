void* __cdecl sb_PrepareVoice(int, int);
void __cdecl sb_SetVoiceLoopCount(void*, int);
void __cdecl fcn_00423670(void*, int, int);

/* ADDRESS: GOLDTL 0x00410f67 */
void* __cdecl fcn_00410f67(int* a, int* b)
{
	void* r;

	r = sb_PrepareVoice(0, *a);
	if (r != 0) {
		sb_SetVoiceLoopCount(r, *b);
		fcn_00423670(r, 0, 0);
		return r;
	}
	sb_PrepareVoice(0, *a);
	return r;
}
