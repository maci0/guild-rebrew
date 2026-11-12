#include "client_town.h"
extern char g_868060[];
extern unsigned int __cdecl vfs_fwrite(void* buf, int size, int count, char* stream);

/* ADDRESS: GOLDTL 0x00520310 */
unsigned int __cdecl fcn_00520310(unsigned int stream)
{
	unsigned int result;
	int offset;
	char* p;
	int count;
	int i;
	int j;

	count = 0x55;
	result = vfs_fwrite(&count, 4, 1, (char*) stream);
	if (result <= 0)
		return 0;
	for (i = 0; i < 5; i++) {
		offset = i * 0x2a90;
		if (vfs_fwrite(((char*) g_85ab80 + offset), 4, 1, (char*) stream) <= 0)
			return 0;
		if (vfs_fwrite(((char*) g_85ab80 + offset) + 4, 4, 1, (char*) stream) <= 0)
			return 0;
		if (vfs_fwrite(((char*) g_85ab80 + offset) + 8, 4, 1, (char*) stream) <= 0)
			return 0;
		if (vfs_fwrite(((char*) g_85ab80 + offset) + 0x0c, 4, 1, (char*) stream) <= 0)
			return 0;
		p = ((char*) g_85ab80 + offset) + 0x18;
		for (j = 0; j < 0x55; j++) {
			if (vfs_fwrite(p - 8, 2, 1, (char*) stream) <= 0)
				return 0;
			if (vfs_fwrite(p - 4, 4, 1, (char*) stream) <= 0)
				return 0;
			if (vfs_fwrite(p, 4, 1, (char*) stream) <= 0)
				return 0;
			if (vfs_fwrite(p + 4, 4, 1, (char*) stream) <= 0)
				return 0;
			if (vfs_fwrite(p + 0x18, 4, 1, (char*) stream) <= 0)
				return 0;
			if (vfs_fwrite(p + 0x1c, 4, 1, (char*) stream) <= 0)
				return 0;
			if (vfs_fwrite(p + 0x28, 4, 1, (char*) stream) <= 0)
				return 0;
			if (vfs_fwrite(p + 0x2c, 4, 1, (char*) stream) <= 0)
				return 0;
			if (vfs_fwrite(p + 0x30, 4, 1, (char*) stream) <= 0)
				return 0;
			if (vfs_fwrite(p + 0x34, 2, 1, (char*) stream) <= 0)
				return 0;
			if (vfs_fwrite(p + 0x24, 4, 1, (char*) stream) <= 0)
				return 0;
			p += 0x80;
		}
	}
	for (i = 0; i < 4; i++) {
		int k;
		offset = i * 0x2f4;
		if (vfs_fwrite((g_868060 + offset), 0x20, 1, (char*) stream) <= 0)
			return 0;
		if (vfs_fwrite((g_868060 + offset) + 0x40, 8, 1, (char*) stream) <= 0)
			return 0;
		if (vfs_fwrite((g_868060 + offset) + 0x48, 1, 1, (char*) stream) <= 0)
			return 0;
		if (vfs_fwrite((g_868060 + offset) + 0x4c, 4, 1, (char*) stream) <= 0)
			return 0;
		if (vfs_fwrite((g_868060 + offset) + 0x50, 4, 1, (char*) stream) <= 0)
			return 0;
		if (vfs_fwrite((g_868060 + offset) + 0x54, 2, 1, (char*) stream) <= 0)
			return 0;
		if (vfs_fwrite((g_868060 + offset) + 0x58, 8, 1, (char*) stream) <= 0)
			return 0;
		if (vfs_fwrite((g_868060 + offset) + 0x60, 1, 1, (char*) stream) <= 0)
			return 0;
		if (vfs_fwrite((g_868060 + offset) + 0x61, 1, 1, (char*) stream) <= 0)
			return 0;
		p = (g_868060 + offset) + 0x64;
		for (k = 0; k < 10; k++) {
			if (vfs_fwrite(p, 8, 1, (char*) stream) <= 0)
				return 0;
			p += 8;
		}
		p = (g_868060 + offset) + 0xb4;
		for (k = 0; k < 10; k++) {
			if (vfs_fwrite(p, 8, 1, (char*) stream) <= 0)
				return 0;
			p += 8;
		}
		if (vfs_fwrite((g_868060 + offset) + 0x104, 1, 1, (char*) stream) <= 0)
			return 0;
		if (vfs_fwrite((g_868060 + offset) + 0x105, 1, 1, (char*) stream) <= 0)
			return 0;
		p = (g_868060 + offset) + 0x108;
		for (k = 0; k < 4; k++) {
			if (vfs_fwrite(p, 4, 1, (char*) stream) <= 0)
				return 0;
			p += 4;
		}
		p = (g_868060 + offset) + 0x118;
		for (k = 0; k < 4; k++) {
			if (vfs_fwrite(p, 4, 1, (char*) stream) <= 0)
				return 0;
			p += 4;
		}
		if (vfs_fwrite((g_868060 + offset) + 0x128, 4, 1, (char*) stream) <= 0)
			return 0;

		for (k = 0; k < 0x0b; k++) {
			if (vfs_fwrite(g_868060 + offset + 0x12c + k, 1, 1, (char*) stream) <= 0)
				return 0;

		}
		if (vfs_fwrite((g_868060 + offset) + 0x137, 1, 1, (char*) stream) <= 0)
			return 0;

		for (k = 0; k < 7; k++) {
			if (vfs_fwrite(g_868060 + offset + 0x138 + k, 1, 1, (char*) stream) <= 0)
				return 0;

		}
		if (vfs_fwrite((g_868060 + offset) + 0x13f, 1, 1, (char*) stream) <= 0)
			return 0;
		if (vfs_fwrite((g_868060 + offset) + 0x140, 1, 1, (char*) stream) <= 0)
			return 0;
		if (vfs_fwrite((g_868060 + offset) + 0x141, 1, 1, (char*) stream) <= 0)
			return 0;
		if (vfs_fwrite((g_868060 + offset) + 0x142, 1, 1, (char*) stream) <= 0)
			return 0;
		p = (g_868060 + offset) + 0x144;
		for (k = 0; k < 8; k++) {
			if (vfs_fwrite(p, 0x12, 1, (char*) stream) <= 0)
				return 0;
			p += 0x12;
		}
		if (vfs_fwrite((g_868060 + offset) + 0x1d4, 4, 1, (char*) stream) <= 0)
			return 0;
		if (vfs_fwrite((g_868060 + offset) + 0x1d8, 4, 1, (char*) stream) <= 0)
			return 0;
		if (vfs_fwrite((g_868060 + offset) + 0x1dc, 0xd0, 1, (char*) stream) <= 0)
			return 0;
		if (vfs_fwrite((g_868060 + offset) + 0x2ec, 8, 1, (char*) stream) <= 0)
			return 0;
	}
	return 1;
}
