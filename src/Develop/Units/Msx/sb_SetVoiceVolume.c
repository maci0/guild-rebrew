extern int sb_WaveDriver;



int __cdecl msx_SetSampleVolume(int, int);

/* ADDRESS: GOLDDE 0x00420620 */
int __cdecl sb_SetVoiceVolume(int* state, int value)
{
	int r;

	r = sb_WaveDriver;
	if (r != 0) {
		if (state != 0) {
			if (value >= 0 && value <= 0x7f) {
				if (state[9] != value) {
					state[9] = value;
					return msx_SetSampleVolume(state[0], value);
				}
				return value;
			}
			return value;
		}
	}
	return r;
}
