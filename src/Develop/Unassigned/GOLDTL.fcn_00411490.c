

#include <errno.h>
#include <stdlib.h>

int __cdecl io_ReadRegistryString(void* key, const char* name, char* out);

int __cdecl io_TryReadRegistryFloat(void* key, const char* name, float* out)
{
	float f;
	char buf[0x80];

	if (io_ReadRegistryString(key, name, buf)) {
		f = (float) atof(buf);
		if (f != 0.0f || errno == 0) {
			*out = f;
			return 1;
		}
	}
	return 0;
}
