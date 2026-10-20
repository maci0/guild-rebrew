extern unsigned char* g_90e094;
extern int g_10058e0;
extern char* g_10058e4;

unsigned int __cdecl vfs_fwrite(void* buf, int size, int count, char* stream);
void* __cdecl realloc(void* p, unsigned int size);
int __cdecl fcn_004eed10(char* stream, char* rec);
int __cdecl fcn_004f3900(char* stream, char* rec);

/* ADDRESS: GOLDTL 0x0051ecf0 */
int __cdecl fcn_0051ecf0(char* file)
{
	int count;
	int i;
	int j;
	char* rec;

	count = 0;
	rec = (char*) g_90e094;
	for (i = 0x100; i != 0; i--) {
		if (*rec != 0) {
			count++;
		}
		rec += 0xa9;
	}
	if (vfs_fwrite(&count, 4, 1, file) <= 0) {
		return 0;
	}
	for (i = 0; i < 0x100; i++) {
			rec = (char*) g_90e094 + i * 0xa9;
			if (*rec == 0) {
				continue;
			}
			if (vfs_fwrite(rec, 1, 1, file) <= 0) {
				return 0;
			}
			if (vfs_fwrite(rec + 1, 4, 1, file) <= 0) {
				return 0;
			}
			if (vfs_fwrite(rec + 5, 0x20, 1, file) <= 0) {
				return 0;
			}
			if (vfs_fwrite(rec + 0x25, 2, 1, file) <= 0) {
				return 0;
			}
			if (vfs_fwrite(rec + 0x27, 2, 1, file) <= 0) {
				return 0;
			}
			if (vfs_fwrite(rec + 0x29, 2, 1, file) <= 0) {
				return 0;
			}
			if (vfs_fwrite(rec + 0x2b, 4, 1, file) <= 0) {
				return 0;
			}
			if (vfs_fwrite(rec + 0x2f, 1, 1, file) <= 0) {
				return 0;
			}
			if (vfs_fwrite(rec + 0x34, 1, 1, file) <= 0) {
				return 0;
			}
			if (vfs_fwrite(rec + 0x35, 4, 1, file) <= 0) {
				return 0;
			}
			if (vfs_fwrite(rec + 0x39, 4, 1, file) <= 0) {
				return 0;
			}
			if (vfs_fwrite(rec + 0x3d, 4, 1, file) <= 0) {
				return 0;
			}
			if (vfs_fwrite(rec + 0x41, 4, 1, file) <= 0) {
				return 0;
			}
			if (vfs_fwrite(rec + 0x45, 4, 1, file) <= 0) {
				return 0;
			}
			if (vfs_fwrite(rec + 0x49, 4, 1, file) <= 0) {
				return 0;
			}
			if (vfs_fwrite(rec + 0x4d, 4, 1, file) <= 0) {
				return 0;
			}
			if (vfs_fwrite(rec + 0x51, 4, 1, file) <= 0) {
				return 0;
			}
			if (vfs_fwrite(rec + 0x55, 4, 1, file) <= 0) {
				return 0;
			}
			if (vfs_fwrite(rec + 0x5a, 2, 1, file) <= 0) {
				return 0;
			}
			if (vfs_fwrite(rec + 0x5c, 1, 1, file) <= 0) {
				return 0;
			}
			if (*rec == 0x1e) {
				for (j = 0; j < 0x600; j += 0x18) {
					if (vfs_fwrite(j + *(char**)(rec + 0x71), 4, 1, file) <= 0) {
						return 0;
					}
					if (vfs_fwrite(j + *(char**)(rec + 0x71) + 4, 4, 1, file) <= 0) {
						return 0;
					}
					if (vfs_fwrite(j + *(char**)(rec + 0x71) + 8, 1, 1, file) <= 0) {
						return 0;
					}
					if (vfs_fwrite(j + *(char**)(rec + 0x71) + 9, 1, 1, file) <= 0) {
						return 0;
					}
					if (vfs_fwrite(j + *(char**)(rec + 0x71) + 0xa, 2, 1, file) <= 0) {
						return 0;
					}
					if (vfs_fwrite(j + *(char**)(rec + 0x71) + 0x10, 4, 1, file) <= 0) {
						return 0;
					}
					if (vfs_fwrite(j + *(char**)(rec + 0x71) + 0xc, 1, 1, file) <= 0) {
						return 0;
					}
					if (vfs_fwrite(j + *(char**)(rec + 0x71) + 0xd, 1, 1, file) <= 0) {
						return 0;
					}
				}
			} else if (*rec == 0x48 || *rec == 0x49 || *rec == 0x4a) {
				if (!fcn_004f3900(file, rec)) {
					return 0;
				}
			} else if (*rec == 0x4b || *rec == 0x4c || *rec == 0x4d) {
				if (!fcn_004eed10(file, rec)) {
					return 0;
				}
			} else {
				if (vfs_fwrite(rec + 0x65, 0x30, 1, file) <= 0) {
					return 0;
				}
			}
			if (vfs_fwrite(rec + 0x99, 0x10, 1, file) <= 0) {
				return 0;
			}
		}
	if (vfs_fwrite(&g_10058e0, 4, 1, file) <= 0) {
		return 0;
	}
	g_10058e4 = (char*) realloc(g_10058e4, g_10058e0 * 0x60);
	for (i = 0; i < g_10058e0; i++) {
		if (vfs_fwrite(g_10058e4 + i * 0x60, 0x40, 1, file) <= 0) {
			return 0;
		}
		if (vfs_fwrite(g_10058e4 + i * 0x60 + 0x40, 0x10, 1, file) <= 0) {
			return 0;
		}
		if (vfs_fwrite(g_10058e4 + i * 0x60 + 0x50, 0x10, 1, file) <= 0) {
			return 0;
		}
	}
	return 1;
}
