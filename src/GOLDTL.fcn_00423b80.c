// FUNCTION: GOLDTL 0x00423b80

#include <string.h>

int __cdecl fcn_00423b80(const char* name)
{
	int r;

	r = 0;
	if (name != 0) {
		if (strstr(name, ".wav") || strstr(name, ".WAV")) {
			r = 1;
		} else if (strstr(name, ".mp3") || strstr(name, ".MP3")) {
			r = 2;
		}
	}
	return r;
}
