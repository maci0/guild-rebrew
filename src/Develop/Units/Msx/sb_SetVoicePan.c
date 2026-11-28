extern int sb_WaveDriver;



int __cdecl msx_SetSamplePan(int, int);

int __cdecl sb_SetVoicePan(int* voice, int pan)
{
	int r;

	r = sb_WaveDriver;
	if (r != 0) {
		if (voice != 0) {
			if (pan >= 0 && pan <= 0x7f) {
				if (voice[0xa] != pan) {
					voice[0xa] = pan;
					return msx_SetSamplePan(voice[0], pan);
				}
				return pan;
			}
			return pan;
		}
	}
	return r;
}
