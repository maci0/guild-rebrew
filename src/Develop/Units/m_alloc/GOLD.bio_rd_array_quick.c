int __cdecl fcn_004011d0(void* stream, void* dst);
int __cdecl fcn_00430a80(char* f, int off, int whence);
#include "Develop/Units/Error/error_message.h"
void* __cdecl m_alloc(unsigned int size, const char* tag);
int __cdecl fcn_00430bd0(void* buf, int size, int count, void* stream);

/* ADDRESS: GOLD 0x00401380 */
int __cdecl bio_rd_array_quick(void* f, int count, void** out)
{
	void* stream;
	int n;

	stream = f;
	fcn_004011d0(stream, &f);
	fcn_004011d0(stream, &n);
	if (n != count) {
		fcn_00430a80(stream, n * *(int*)&f, 1);
		*out = 0;
		fcn_0041d9e0("bio_rd_array_quick: Tried to load invalid array-sizes...");
		return 0;
	}
	*out = m_alloc(*(int*)&f * count, "bio:bio_rd_array_quick");
	fcn_00430bd0(*out, count, *(int*)&f, stream);
	return *(int*)&f;
}
