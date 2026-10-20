/* Location record: 0x24d-byte entries in the g_868050 table. */
typedef struct Loc {
	unsigned char kind;      /* 0x000 */
	char pad1[0x0c];
	unsigned char xd;        /* 0x00d */
	char pad_e[0x159];       /* 0x00e..0x166 */
	unsigned char x166;      /* 0x166 */
	char pad167[0xbc];       /* 0x167..0x222 */
	unsigned char list[6];   /* 0x223 */
	char pad229[0x24];       /* 0x229..0x24c */
} Loc;
// SIZE 0x24d

extern char* g_868050;
extern int g_774800;

int __cdecl fcn_00504bd0(int id);
int __cdecl fcn_00507910(unsigned char kind);
int __cdecl fcn_005074e0(int id, int kind);
int __cdecl fcn_00504ef0(unsigned char kind, int* out);

/* ADDRESS: GOLDTL 0x00504f30 */
unsigned int __cdecl fcn_00504f30(int a0, int a1)
{
	Loc* rec;
	unsigned char* rb;
	int arr[8];
	int type;
	int loc;
	int n;
	int j;
	int i;
	unsigned char c;

	type = fcn_00504bd0(a0);
	rec = (Loc*) (g_868050 + a0 * 0x24d);
	loc = fcn_005074e0(a1, fcn_00507910(rec->kind));
	if (a1 == 0xffff) {
		return 0;
	}
	rb = (unsigned char*) (a1 * 0x21c + 0x7f4ca0);
	if (g_774800 != 0 && (rb[2] == 6 || rb[2] == 7)) {
		return 1;
	}
	if (type == 1) {
		for (i = 0; i < 6; i++) {
			c = rec->list[i];
			if (c == 0) {
				break;
			}
			if ((unsigned char) loc == c) {
				return 1;
			}
		}
		n = fcn_00504ef0(rec->kind, arr);
		for (j = 0; j < n; j++) {
			rb = (unsigned char*) (g_868050 + arr[j] * 0x24d);
			for (i = 0; i < 6; i++) {
				c = rb[0x223 + i];
				if (c == 0) {
					break;
				}
				if ((unsigned char) loc == c) {
					return 2;
				}
			}
		}
		return 0;
	}
	if (type == 2) {
		return 0;
	}
	if (type == 3) {
		if (rb[0x166] == 0x0f) {
			if (rec->kind == 1 || rec->kind == 0x0f || rec->kind == 6) {
				return 1;
			}
		}
		if (rb[0x166] == 0x0a && rec->kind == 3) {
			return 1;
		}
		return 0;
	}
	if (type == 7) {
		if (rec->kind != 0x13) {
			return 0;
		}
		for (i = 0; i < 6; i++) {
			c = rec->list[i];
			if (c == 0) {
				break;
			}
			if ((unsigned char) loc == c) {
				return 1;
			}
		}
		n = fcn_00504ef0(0x13, arr);
		for (j = 0; j < n; j++) {
			rb = (unsigned char*) (g_868050 + arr[j] * 0x24d);
			for (i = 0; i < 6; i++) {
				c = rb[0x223 + i];
				if (c == 0) {
					break;
				}
				if ((unsigned char) loc == c) {
					return 2;
				}
			}
		}
		return 0;
	}
	if (type == 4) {
		for (i = 0; i < 6; i++) {
			c = rec->list[i];
			if (c == 0) {
				break;
			}
			if ((unsigned char) loc == c) {
				return 1;
			}
		}
		return 0;
	}
	if (type == 6) {
		if ((unsigned int) (a0 - 4) <= 0x49) {
			switch (a0) {
			case 4:
				return (rb[0x0d] < 1) + 1;
			case 5:
				return (rb[0x0d] < 3) + 1;
			case 6:
			case 75:
			case 76:
			case 77:
				return (rb[0x0d] < 4) + 1;
			case 7:
				return (rb[0x0d] < 5) + 1;
			}
		}
		return 1;
	}
	if (type == 8) {
		for (i = 0; i < 6; i++) {
			c = rec->list[i];
			if (c == 0) {
				break;
			}
			if ((unsigned char) loc == c) {
				return 1;
			}
		}
		n = fcn_00504ef0(rec->kind, arr);
		for (j = 0; j < n; j++) {
			rb = (unsigned char*) (g_868050 + arr[j] * 0x24d);
			for (i = 0; i < 6; i++) {
				c = rb[0x223 + i];
				if (c == 0) {
					break;
				}
				if ((unsigned char) loc == c) {
					return 2;
				}
			}
		}
		return 0;
	}
	return 1;
}
