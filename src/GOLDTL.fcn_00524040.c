#include <string.h>

extern int g_6a23ac;
#include "client_town.h"
extern char g_868060[];
extern char* g_14a5320[];

#include "Develop/DieGildeAddOn/loadsave/loadsave.h"
int sprintf(char* buf, const char* fmt, ...);
int __cdecl fcn_0042dc90(const char* name);

/* ADDRESS: GOLDTL 0x00524040 */
int __cdecl fcn_00524040(void* stream)
{
	char buf[256];
	int count;
	int ptr2;
	int ptr;

	count = 0x3e;
	if (g_6a23ac >= 0x10048) {
		if (!ls_ReadVfsDataChecked(&count, 4, 1, stream)) {
			return 0;
		}
	}

	for (ptr = (int)g_85ab80 + 8; ptr < (int)g_85ab80 + 0xd4d8; ptr += 0x2a90) {
		char* inner;
		int i;
		char* hdr;

		hdr = (char*)(ptr - 8);
		if (!ls_ReadVfsDataChecked(hdr, 4, 1, stream)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(hdr + 4, 4, 1, stream)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(hdr + 8, 4, 1, stream)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(hdr + 0xc, 4, 1, stream)) {
			return 0;
		}

		i = 0;
		if (count > 0) {
			inner = (char*)(ptr + 0x10);
			do {
				char* r;

				r = inner - 8;
				if (!ls_ReadVfsDataChecked(r, 2, 1, stream)) {
					return 0;
				}
				if (!ls_ReadVfsDataChecked(r + 4, 4, 1, stream)) {
					return 0;
				}
				if (!ls_ReadVfsDataChecked(r + 8, 4, 1, stream)) {
					return 0;
				}
				if (!ls_ReadVfsDataChecked(r + 0xc, 4, 1, stream)) {
					return 0;
				}
				if (!ls_ReadVfsDataChecked(r + 0x20, 4, 1, stream)) {
					return 0;
				}
				if (!ls_ReadVfsDataChecked(r + 0x24, 4, 1, stream)) {
					return 0;
				}
				if (!ls_ReadVfsDataChecked(r + 0x30, 4, 1, stream)) {
					return 0;
				}
				if (!ls_ReadVfsDataChecked(r + 0x34, 4, 1, stream)) {
					return 0;
				}
				if (!ls_ReadVfsDataChecked(r + 0x38, 4, 1, stream)) {
					return 0;
				}
				if (!ls_ReadVfsDataChecked(r + 0x3c, 2, 1, stream)) {
					return 0;
				}
				if (!ls_ReadVfsDataChecked(r + 0x2c, 4, 1, stream)) {
					return 0;
				}
				i++;
				inner += 0x80;
			} while (i < count);
		}
	}

	ptr2 = (int)(g_868060 + 0x48);
	while (ptr2 < (int)(g_868060 + 0xc18)) {
		char* q;
		char* b;
		char* inner;
		int i;

		q = (char*)(ptr2 - 8);
		b = (char*)(ptr2 - 0x48);
		if (!ls_ReadVfsDataChecked(q - 0x40, 0x20, 1, stream)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(q, 8, 1, stream)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(q + 8, 1, 1, stream)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(q + 0xc, 4, 1, stream)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(q + 0x10, 4, 1, stream)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(q + 0x14, 2, 1, stream)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(q + 0x18, 8, 1, stream)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(q + 0x20, 1, 1, stream)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(q + 0x21, 1, 1, stream)) {
			return 0;
		}

		i = 0;
		inner = (char*)(ptr2 + 0x1c);
		do {
			if (!ls_ReadVfsDataChecked(inner, 8, 1, stream)) {
				return 0;
			}
			i++;
			inner += 8;
		} while (i < 10);

		i = 0;
		inner = b + 0xb4;
		do {
			if (!ls_ReadVfsDataChecked(inner, 8, 1, stream)) {
				return 0;
			}
			i++;
			inner += 8;
		} while (i < 10);

		if (!ls_ReadVfsDataChecked(b + 0x104, 1, 1, stream)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(b + 0x105, 1, 1, stream)) {
			return 0;
		}

		i = 0;
		inner = b + 0x108;
		do {
			if (!ls_ReadVfsDataChecked(inner, 4, 1, stream)) {
				return 0;
			}
			i++;
			inner += 4;
		} while (i < 4);

		i = 0;
		inner = b + 0x118;
		do {
			if (!ls_ReadVfsDataChecked(inner, 4, 1, stream)) {
				return 0;
			}
			i++;
			inner += 4;
		} while (i < 4);

		if (!ls_ReadVfsDataChecked(b + 0x128, 4, 1, stream)) {
			return 0;
		}

		for (i = 0; i < 0xb; i++) {
			if (!ls_ReadVfsDataChecked(b + 0x12c + i, 1, 1, stream)) {
				return 0;
			}
		}

		if (!ls_ReadVfsDataChecked(b + 0x137, 1, 1, stream)) {
			return 0;
		}

		for (i = 0; i < 7; i++) {
			if (!ls_ReadVfsDataChecked(b + 0x138 + i, 1, 1, stream)) {
				return 0;
			}
		}

		if (!ls_ReadVfsDataChecked(b + 0x13f, 1, 1, stream)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(b + 0x140, 1, 1, stream)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(b + 0x141, 1, 1, stream)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(b + 0x142, 1, 1, stream)) {
			return 0;
		}

		i = 0;
		inner = b + 0x144;
		do {
			if (!ls_ReadVfsDataChecked(inner, 0x12, 1, stream)) {
				return 0;
			}
			i++;
			inner += 0x12;
		} while (i < 8);

		if (!ls_ReadVfsDataChecked(b + 0x1d4, 4, 1, stream)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(b + 0x1d8, 4, 1, stream)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(b + 0x1dc, 0xd0, 1, stream)) {
			return 0;
		}
		if (g_6a23ac >= 0x10037) {
			if (!ls_ReadVfsDataChecked(b + 0x2ec, 8, 1, stream)) {
				return 0;
			}
		}
		ptr2 += 0x2f4;
	}

	sprintf(buf, "_STADTAUSWAHL_%s_INFO+0", g_868060);
	_strupr(buf);
	ptr = fcn_0042dc90(buf);
	if (ptr != -1) {
		int delta;
		char* s;
		char c;

		delta = (int)(g_868060 + 0x20);
		s = g_14a5320[ptr];
		delta = delta - (int)s;
		do {
			c = *s;
			*(char*)((int)s + delta) = c;
			s++;
		} while (c != 0);
		return 1;
	}
	{
		char* s;
		char* d;

		s = g_868060;
		d = s + 0x20;
		strcpy(d, s);
	}
	return 1;
}
