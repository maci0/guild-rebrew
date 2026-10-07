// FUNCTION: GOLDTL 0x423b20

#include <string.h>

int __cdecl fcn_00423b20(char* path, char* out, int n)
{
	int r = 0;
	char* s;
	char* e;

	if (path != 0 && out != 0) {
		s = strrchr(path, '\\');
		e = strrchr(s, '.');
		if (e != 0 && s != 0) {
			s++;
			if (e - s < n) {
				strncpy(out, s, e - s);
			} else {
				r = -1;
			}
		} else {
			r = -1;
		}
	} else {
		r = -1;
	}
	return r;
}
