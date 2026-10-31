

int __cdecl fcn_004011f0(void* f, void* x);
int __cdecl fcn_00430a80(char* f, int off, int whence);
#include "Develop/Units/Error/error_message.h"
void* __cdecl m_alloc(unsigned int size, const char* tag);
int __cdecl vfs_ReadData(char* buf, int size, int count, char* f);

int __cdecl fcn_00401500(void* f, int count, void** out)
{
	int size;
	int n;

	fcn_004011f0(f, &size);
	fcn_004011f0(f, &n);
	if (n != count) {
		fcn_00430a80(f, n * size, 1);
		*out = 0;
		ReportClientMessage("bio_rd_array_quick: Tried to load invalid array-sizes...");
		return 0;
	}
	*out = m_alloc(size * count, "bio:bio_rd_array_quick");
	vfs_ReadData(*out, count, size, f);
	return size;
}
