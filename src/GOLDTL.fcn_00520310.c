extern unsigned int __cdecl vfs_fwrite(void* buf, int size, int count, char* stream);

/* ADDRESS: GOLDTL 0x00520310 */
unsigned int __cdecl fcn_00520310(unsigned int stream)
{
	unsigned int result;
	char* base;
	char* p;
	int count;
	int i;
	int j;

	count = 0x55;
	result = vfs_fwrite(&count, 4, 1, (char*) stream);
	if (result <= 0)
		return 0;
	for (i = 0; i < 5; i++) {
		base = (char*) (0x85ab80 + i * 0x2a90);
		if (vfs_fwrite(base, 4, 1, (char*) stream) <= 0)
			return 0;
		if (vfs_fwrite(base + 4, 4, 1, (char*) stream) <= 0)
			return 0;
		if (vfs_fwrite(base + 8, 4, 1, (char*) stream) <= 0)
			return 0;
		if (vfs_fwrite(base + 0x0c, 4, 1, (char*) stream) <= 0)
			return 0;
		p = base + 0x18;
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
		base = (char*) (0x868060 + i * 0x2f4);
		if (vfs_fwrite(base, 0x20, 1, (char*) stream) <= 0)
			return 0;
		if (vfs_fwrite(base + 0x40, 8, 1, (char*) stream) <= 0)
			return 0;
		if (vfs_fwrite(base + 0x48, 1, 1, (char*) stream) <= 0)
			return 0;
		if (vfs_fwrite(base + 0x4c, 4, 1, (char*) stream) <= 0)
			return 0;
		if (vfs_fwrite(base + 0x50, 4, 1, (char*) stream) <= 0)
			return 0;
		if (vfs_fwrite(base + 0x54, 2, 1, (char*) stream) <= 0)
			return 0;
		if (vfs_fwrite(base + 0x58, 8, 1, (char*) stream) <= 0)
			return 0;
		if (vfs_fwrite(base + 0x60, 1, 1, (char*) stream) <= 0)
			return 0;
		if (vfs_fwrite(base + 0x61, 1, 1, (char*) stream) <= 0)
			return 0;
		p = base + 0x64;
		for (k = 0; k < 10; k++) {
			if (vfs_fwrite(p, 8, 1, (char*) stream) <= 0)
				return 0;
			p += 8;
		}
		p = base + 0xb4;
		for (k = 0; k < 10; k++) {
			if (vfs_fwrite(p, 8, 1, (char*) stream) <= 0)
				return 0;
			p += 8;
		}
		if (vfs_fwrite(base + 0x104, 1, 1, (char*) stream) <= 0)
			return 0;
		if (vfs_fwrite(base + 0x105, 1, 1, (char*) stream) <= 0)
			return 0;
		p = base + 0x108;
		for (k = 0; k < 4; k++) {
			if (vfs_fwrite(p, 4, 1, (char*) stream) <= 0)
				return 0;
			p += 4;
		}
		p = base + 0x118;
		for (k = 0; k < 4; k++) {
			if (vfs_fwrite(p, 4, 1, (char*) stream) <= 0)
				return 0;
			p += 4;
		}
		if (vfs_fwrite(base + 0x128, 4, 1, (char*) stream) <= 0)
			return 0;
		p = base + 0x12c;
		for (k = 0; k < 0x0b; k++) {
			if (vfs_fwrite(p, 1, 1, (char*) stream) <= 0)
				return 0;
			p++;
		}
		if (vfs_fwrite(base + 0x137, 1, 1, (char*) stream) <= 0)
			return 0;
		p = base + 0x138;
		for (k = 0; k < 7; k++) {
			if (vfs_fwrite(p, 1, 1, (char*) stream) <= 0)
				return 0;
			p++;
		}
		if (vfs_fwrite(base + 0x13f, 1, 1, (char*) stream) <= 0)
			return 0;
		if (vfs_fwrite(base + 0x140, 1, 1, (char*) stream) <= 0)
			return 0;
		if (vfs_fwrite(base + 0x141, 1, 1, (char*) stream) <= 0)
			return 0;
		if (vfs_fwrite(base + 0x142, 1, 1, (char*) stream) <= 0)
			return 0;
		p = base + 0x144;
		for (k = 0; k < 8; k++) {
			if (vfs_fwrite(p, 0x12, 1, (char*) stream) <= 0)
				return 0;
			p += 0x12;
		}
		if (vfs_fwrite(base + 0x1d4, 4, 1, (char*) stream) <= 0)
			return 0;
		if (vfs_fwrite(base + 0x1d8, 4, 1, (char*) stream) <= 0)
			return 0;
		if (vfs_fwrite(base + 0x1dc, 0xd0, 1, (char*) stream) <= 0)
			return 0;
		if (vfs_fwrite(base + 0x2ec, 8, 1, (char*) stream) <= 0)
			return 0;
	}
	return 1;
}
