

#include <errno.h>
#include <stdlib.h>

int __cdecl fcn_004113d0(void* key, const char* name, char* out);

int __cdecl fcn_00411490(void* key, const char* name, float* out)
{
	float f;
	char buf[0x80];

	if (fcn_004113d0(key, name, buf)) {
		f = (float) atof(buf);
		if (f != 0.0f || errno == 0) {
			*out = f;
			return 1;
		}
	}
	return 0;
}
