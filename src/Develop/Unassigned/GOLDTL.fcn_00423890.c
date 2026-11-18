extern int g_6b7d7c;



int __cdecl fcn_0042a920(int, int);

int __cdecl fcn_00423890(int* state, int value)
{
	int r;

	r = g_6b7d7c;
	if (r != 0) {
		if (state != 0) {
			if (value >= 0 && value <= 0x7f) {
				if (state[9] != value) {
					state[9] = value;
					return fcn_0042a920(state[0], value);
				}
				return value;
			}
			return value;
		}
	}
	return r;
}
