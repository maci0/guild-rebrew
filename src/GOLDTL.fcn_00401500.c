

void __cdecl fcn_004011f0(int f, void* x);
void __cdecl fcn_00430a80(int f, int off, int whence);
#include "Develop/Units/Error/error_message.h"
void* __cdecl m_alloc(unsigned int size, const char* tag);
void __cdecl fcn_004306b0(void* buf, int size, int count, int f);

int __cdecl fcn_00401500(int f, int count, void** out)
{
	int size;
	int n;

	fcn_004011f0(f, &size);
	fcn_004011f0(f, &n);
	if (n != count) {
		fcn_00430a80(f, n * size, 1);
		*out = 0;
		fcn_0041d9e0("bio_rd_array_quick: Tried to load invalid array-sizes...");
		return 0;
	}
	*out = m_alloc(size * count, "bio:bio_rd_array_quick");
	fcn_004306b0(*out, count, size, f);
	return size;
}
