unsigned int __cdecl vfs_fwrite(void* buf, int size, int count, char* stream);

/* ADDRESS: GOLDTL 0x005208e0 */
int __cdecl fcn_005208e0(char* fp)
{
	char* p;
	char* q;
	int i;

	if (vfs_fwrite((void*) 0x99f5e0, 4, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) 0x99f5e4, 4, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) 0x99f5e8, 4, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) 0x99f5ec, 4, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) 0x99f5f0, 4, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) 0x99f5f4, 4, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) 0x99f5f8, 4, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) 0x99f5fc, 4, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) 0x99f600, 4, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) 0x99f604, 4, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) 0x99ec14, 4, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) 0x99f590, 4, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) 0x99f594, 2, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) 0x99f596, 4, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) 0x99f59a, 4, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) 0x773d4c, 4, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) 0x773d50, 4, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) 0x99f5a0, 4, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) 0x99f5a4, 4, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) 0x99f5a8, 4, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) 0x99f5ac, 4, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) 0x99f5b0, 4, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) 0x99f5b4, 4, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) 0x99f5b8, 4, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) 0x99f5bc, 4, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) 0x99f5c0, 4, 1, fp) <= 0) {
		return 0;
	}
	p = (char*) 0x99ec24;
	do {
		if (vfs_fwrite(p - 4, 4, 1, fp) <= 0) {
			return 0;
		}
		if (vfs_fwrite(p, 4, 1, fp) <= 0) {
			return 0;
		}
		if (vfs_fwrite(p + 4, 4, 1, fp) <= 0) {
			return 0;
		}
		if (vfs_fwrite(p + 8, 4, 1, fp) <= 0) {
			return 0;
		}
		if (vfs_fwrite(p + 0xc, 4, 1, fp) <= 0) {
			return 0;
		}
		p += 0x14;
	} while (p < (char*) 0x99ed64);
	if (vfs_fwrite((void*) 0x99f6a0, 0x44, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) 0x99f6e4, 0x44, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) 0x99f728, 0x44, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) 0x99f76c, 0x44, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) 0x99f7b0, 0x44, 1, fp) <= 0) {
		return 0;
	}
	p = (char*) 0x99ef82;
	do {
		i = 0;
		q = p;
		do {
			if (vfs_fwrite(q - 2, 2, 1, fp) <= 0) {
				return 0;
			}
			if (vfs_fwrite(q, 2, 1, fp) <= 0) {
				return 0;
			}
			if (vfs_fwrite(q + 2, 1, 1, fp) <= 0) {
				return 0;
			}
			if (vfs_fwrite(q + 6, 4, 1, fp) <= 0) {
				return 0;
			}
			i++;
			q += 0x18;
		} while (i < 8);
		p += 0xc0;
	} while (p < (char*) 0x99f582);
	return 1;
}
