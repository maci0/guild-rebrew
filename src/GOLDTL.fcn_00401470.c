

int __cdecl fcn_004011f0(void* f, void* x);
int __cdecl fcn_00430a80(char* f, int off, int whence);
#include "Develop/Units/Error/error_message.h"
void* __cdecl m_alloc(int size, const char* tag);
int __cdecl fcn_004306b0(char* buf, int size, int count, char* f);

int __cdecl fcn_00401470(void* f, int count, void** out, const char* tag)
{
	int size;
	int n;

	fcn_004011f0(f, &size);
	fcn_004011f0(f, &n);
	if (n != count) {
		fcn_00430a80(f, n * size, 1);
		*out = 0;
		fcn_0041d9e0("array count mismatch");
		return 0;
	}
	*out = m_alloc(size * count, tag);
	fcn_004306b0(*out, count, size, f);
	return size;
}
