extern int sb_WaveDriver;



extern volatile int gm_GameTicks;
int __cdecl msx_EndSample(int);

/* ADDRESS: GOLDDE 0x00420580 */
void __cdecl sb_StopVoice(int* p, int fade)
{
	if (sb_WaveDriver != 0 && p != 0) {
		if (fade != 0) {
			p[5] |= 2;
			p[4] = (gm_GameTicks * 2 + gm_GameTicks) * 4 + gm_GameTicks;
			return;
		}
		msx_EndSample(p[0]);
		p[5] |= 8;
	}
}
