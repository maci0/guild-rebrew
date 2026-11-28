extern int g_6b7d7c;



int __cdecl msx_SetSampleVolume(int, int);

int __cdecl sb_SetVoiceVolume(int* state, int value)
{
	int r;

	r = g_6b7d7c;
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
