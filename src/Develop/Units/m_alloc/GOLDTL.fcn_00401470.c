

int __cdecl fcn_004011f0(void* f, void* x);
int __cdecl vfs_fseek(char* f, int off, int whence);
#include "Develop/Units/Error/error_message.h"
void* __cdecl m_alloc(int size, const char* tag);
int __cdecl vfs_ReadData(char* buf, int size, int count, char* f);

int __cdecl bio_rd_array_debug(void* f, int count, void** out, const char* tag)
{
	int size;
	int n;

	fcn_004011f0(f, &size);
	fcn_004011f0(f, &n);
	if (n != count) {
		vfs_fseek(f, n * size, 1);
		*out = 0;
		ReportClientMessage("array count mismatch");
		return 0;
	}
	*out = m_alloc(size * count, tag);
	vfs_ReadData(*out, count, size, f);
	return size;
}
