


#include "g_68e020.h"

extern Entry68e020 g_68e020[32];

int __cdecl vfs_fwrite(void* buf, int size, int count, int stream);

int __cdecl fcn_004ef040(int stream)
{
	unsigned int n;
	unsigned int i;

	n = 0x20;
	if (stream == 0) {
		return 0;
	}
	if (!vfs_fwrite(&n, 4, 1, stream)) {
		return 0;
	}
	for (i = 0; i < n; i++) {
		if (!vfs_fwrite((char*) g_68e020 + i * 244, 4, 1, stream)) {
			return 0;
		}
		if (!vfs_fwrite((char*) g_68e020 + 0xf2 + i * 244, 1, 1, stream)) {
			return 0;
		}
	}
	return 1;
}
