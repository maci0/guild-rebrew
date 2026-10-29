void __cdecl fcn_00459be0(unsigned int flags);
int __cdecl fcn_00459c70(char* a);
int __cdecl fcn_00459cd0(char* a);
int __cdecl fcn_00459d00(char* a, int b);


/* Sums into *size the bytes the parts of o selected by flags occupy. */
/* ADDRESS: GOLDTL 0x00459ea0 */
unsigned char __cdecl fcn_00459ea0(char* o, unsigned int flags, int* size)
{
	unsigned char r;
	int i;
	int j;
	int n;
	char* p;

	r = 0;
	if (o != 0 && size != 0) {
		fcn_00459be0(flags);
		*size = 0;
		if (flags & 1) {
			*size = 0x228;
			if (*(int*) (o + 0x1e8) != 0) {
				*size = 0x3d4;
			}
		}
		if (*(char**) (o + 0x1ec) != 0) {
			if (flags & 1) {
				*size += 0x1640;
				for (i = 0; i < *(unsigned char*) (*(char**) (o + 0x1ec) + 0x163c); i++) {
					if (*(int*) (*(char**) (o + 0x1ec) + i * 0x4a4 + 0x410) != 0 &&
					    (p = *(char**) (*(char**) (o + 0x1ec) + i * 0x4a4 + 0x40c)) != 0) {
						*size += *(int*) (p + 0x1e4) * 4;
					}
				}
			}
			if (flags & 2) {
				for (i = 0; i < *(unsigned char*) (*(char**) (o + 0x1ec) + 0x163c); i++) {
					p = *(char**) (*(char**) (o + 0x1ec) + i * 0x4a4 + 0x40c);
					if (p != 0) {
						*size += fcn_00459c70(p);
					}
				}
				p = *(char**) (*(char**) (o + 0x1ec) + 0x11f8);
				if (p != 0) {
					*size += fcn_00459c70(p);
				}
			}
			if (flags & 8) {
				for (i = 0; i < *(unsigned char*) (*(char**) (o + 0x1ec) + 0x163c); i++) {
					if (*(*(char**) (o + 0x1ec) + i * 0x4a4 + 0x594) != 0) {
						for (j = 0; j < 3; j++) {
							p = *(char**) (*(char**) (o + 0x1ec) + i * 0x4a4 + j * 0x7c + 0x484);
							if (p != 0) {
								*size += fcn_00459cd0(p);
							}
						}
					}
				}
			}
			if (flags & 0x80) {
				for (i = 0; i < *(unsigned char*) (*(char**) (o + 0x1ec) + 0x163c); i++) {
					n = 0;
					if ((p = *(char**) (*(char**) (o + 0x1ec) + i * 0x4a4 + 0x40c)) != 0 &&
					    *(int*) (*(char**) (o + 0x1ec) + i * 0x4a4 + 0x410) != 0) {
						n = *(int*) (p + 0x1e4);
					}
					for (j = 0; j < n; j++) {
						*size += fcn_00459d00(
							(*(char***) (*(char**) (o + 0x1ec) + i * 0x4a4 + 0x410))[j], 1);
					}
				}
			}
		}
		if ((flags & 0x20) && *(int**) (o + 0x1d0) != 0) {
			*size += 0x44;
			*size += **(int**) (o + 0x1d0) * 0x58;
		}
		if ((flags & 0x40) && *(int*) (o + 0x1d4) != 0) {
			*size += 0x39c;
		}
		r = 1;
	}
	return r;
}
