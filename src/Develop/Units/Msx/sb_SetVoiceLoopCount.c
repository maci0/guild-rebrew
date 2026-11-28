extern int sb_WaveDriver;
extern int sb_WaveDriver;



void __cdecl msx_SetSampleLoopCount(int, int);

/* ADDRESS: GOLDDE 0x00420680 */
void __cdecl sb_SetVoiceLoopCount(int* p, int value)
{
	if (*(int*) ((char*)&sb_WaveDriver) == 0) {
		return;
	}
	if (p == 0) {
		return;
	}
	*(int*) ((char*) p + 0xc) = value;
	msx_SetSampleLoopCount(*(int*) p, value);
}
