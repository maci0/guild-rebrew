


extern int g_772f2c;

unsigned int __cdecl cut_RandMod(unsigned int);

void __cdecl cut_SelectDuellResponse(char* state)
{
	int r;

	if (g_772f2c == 0) {
		if (cut_RandMod(10) > 7)
			state[0x94] = 1;
		else
			state[0x94] = 0;
	} else {
		r = cut_RandMod(100);
		if (r > 50)
			state[0x94] = 4;
		else if (r > 15)
			state[0x94] = 2;
		else
			state[0x94] = 3;
	}
}
