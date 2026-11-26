extern int g_6b7d7c;



int __cdecl fcn_0042a9a0(int, int);

int __cdecl sb_SetVoicePan(int* voice, int pan)
{
	int r;

	r = g_6b7d7c;
	if (r != 0) {
		if (voice != 0) {
			if (pan >= 0 && pan <= 0x7f) {
				if (voice[0xa] != pan) {
					voice[0xa] = pan;
					return fcn_0042a9a0(voice[0], pan);
				}
				return pan;
			}
			return pan;
		}
	}
	return r;
}
