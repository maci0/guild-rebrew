#include <string.h>

#include "client_types.h"

extern pos14_7f4c00 g_7f4c00;
extern int g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;
extern char g_7f4ca4[];

char* __cdecl fcn_005463a0(int, int, int, int, int);
char* __cdecl he_fn_Handlung(void);
char* __cdecl fcn_004bcc50(char*, int);
char* __cdecl fcn_005049a0(unsigned char*);
char* __cdecl fcn_00502cd0(int, int, int, ...);
void __cdecl fcn_00529160(int, int, int, int);
void __cdecl fcn_004c5530(char*);

/* Message layout (0xf8 bytes).  The type byte at +4 selects the payload:
   +8/+0xc entity ids, +0x10 selection counter, +0x28..+0x36 stamp, +0x38
   entity id list, +0x58 count/length, +0x5a..+0x6c per-type fields. */
/* ADDRESS: GOLDTL 0x00487f90 */
void __cdecl fcn_00487f90(int* a0)
{
	char m[0xf8];
	char* e;
	char* rec;
	char* free_rec;
	int n;
	int base;
	int k;
	int v;

	if (a0[0] == 0x28) {
		base = *(int*) (*(int*) (a0[1] + 0x16c) + 0x71);
		if (a0[5] > 1 && a0[7] == 0) {
			n = a0[8] + a0[6] % a0[5] + a0[6] / a0[5];
		} else {
			n = a0[6] / a0[5] + a0[8];
		}
		for (rec = fcn_005463a0(2, 0, 0x28, 3,
		                        *(int*) (*(int*) (a0[1] + 0x16c) + 1));
		     rec != 0; rec = he_fn_Handlung()) {
			v = (int) fcn_004bcc50((char*) base, *(int*) (rec + 0xb8));
			if (v != 0 &&
			    *(unsigned short*) (v + 0xa) == *(int*) a0[2]) {
				n = n - 1;
			}
		}
		if (a0[8] < n) {
			for (e = (char*) 0x7f4e05;
			     (int) e <= 0x85a204 && a0[8] < base;
			     e += 0x21c) {
				if (*(short*) (e - 0x165) == -1 ||
				    *(int*) (e + 7) != *(int*) (a0[1] + 0x16c) ||
				    *e == 0 || *(int*) (e + 0x17) != 0 ||
				    *(int*) (e + 0x1f) == 0 ||
				    *(int*) (*(int*) (e + 0x1f) + 0x2c) !=
				        *(int*) (*(int*) (e + 7) + 1)) {
					continue;
				}
				free_rec = 0;
				for (k = 0; k < 0x40 && free_rec == 0; k++) {
					if (*(char*) ((char*) base + k * 0x18 + 0xd) > 1 &&
					    *(int*) ((char*) base + k * 0x18 + 0x10) == -1) {
						free_rec = (char*) base + k * 0x18;
					}
				}
				if (free_rec == 0) {
					return;
				}
				memset(m, 0, sizeof(m));
				m[4] = (char) a0[0];
				*(int*) (m + 8) = *(int*) (g_7f4ca4 +
				                           *(unsigned short*) (*(int*) (a0[1] + 0x16c) + 0x27) * 0x21c);
				*(int*) (m + 0xc) = *(int*) (*(int*) (a0[1] + 0x16c) + 1);
				*(int*) (m + 0x28) = *(int*) &g_7f4c00;
				*(int*) (m + 0x2c) = g_7f4c04;
				*(int*) (m + 0x30) = g_7f4c08;
				*(short*) (m + 0x34) = g_7f4c0c;
				*(int*) (m + 0x10) = 1;
				*(int*) (m + 0x14) = 0;
				m[0x36] = 1;
				*(int*) (m + 0x64) = *(int*) free_rec;
				*(int*) (m + 0x58) = *(int*) (*(int*) (a0[1] + 0x16c) + 1);
				*(int*) (m + 0x5c) = *(int*) (e + 4);
				fcn_004c5530(m);
				a0[8] = a0[8] + 1;
			}
		}
		a0[7] = a0[7] + 1;
		return;
	}
	if (a0[0] == 0x14) {
		if (a0[5] > 1 && a0[7] == 0) {
			n = a0[8] + a0[6] / a0[5] + a0[6] % a0[5];
		} else {
			n = a0[6] / a0[5] + a0[8];
		}
		memset(m, 0, sizeof(m));
		m[4] = (char) a0[0];
		*(int*) (m + 8) = *(int*) (g_7f4ca4 +
		                           *(unsigned short*) (*(int*) (a0[1] + 0x16c) + 0x27) * 0x21c);
		*(int*) (m + 0xc) = *(int*) (*(int*) (a0[1] + 0x16c) + 1);
		*(int*) (m + 0x10) = 0;
		*(int*) (m + 0x14) = 0;
		*(int*) (m + 0x28) = *(int*) &g_7f4c00;
		*(int*) (m + 0x2c) = g_7f4c04;
		*(int*) (m + 0x30) = g_7f4c08;
		*(short*) (m + 0x34) = g_7f4c0c;
		m[0x36] = 1;
		*(short*) (m + 0x5a) = *(short*) a0[2];
		*(int*) (m + 0x5c) =
		    *(int*) (fcn_005049a0((unsigned char*) *(int*) (a0[1] + 0x16c)) + 2);
		if (a0[8] < n) {
			for (e = (char*) 0x7f4e05; (int) e <= 0x85a204; e += 0x21c) {
				if (*(short*) (e - 0x165) != -1 &&
				    *(int*) (e + 7) == *(int*) (a0[1] + 0x16c) &&
				    *e != 0 && *(int*) (e + 0x17) == 0 &&
				    *(int*) (e + 0x1f) != 0 &&
				    *(int*) (*(int*) (e + 0x1f) + 0x2c) ==
				        *(int*) (*(int*) (e + 7) + 1)) {
					*(int*) (m + 0x38 + *(int*) (m + 0x10) * 4) =
					    *(int*) (e + 4);
					*(int*) (m + 0x10) = *(int*) (m + 0x10) + 1;
					a0[8] = a0[8] + 1;
				}
				if (a0[8] >= n) {
					break;
				}
			}
		}
		m[0x58] = (char) *(int*) (m + 0x10);
		if (*(int*) (m + 0x10) == 0) {
			a0[7] = a0[7] + 1;
			return;
		}
		if (*(short*) (m + 0x5a) == 0) {
			a0[7] = a0[7] + 1;
			return;
		}
		fcn_004c5530(m);
		a0[7] = a0[7] + 1;
		return;
	}
	if (a0[0] == 0x15) {
		if (a0[5] > 1 && a0[7] == 0) {
			n = a0[8] + a0[6] % a0[5] + a0[6] / a0[5];
		} else {
			n = a0[6] / a0[5] + a0[8];
		}
		rec = fcn_00502cd0(*(int*) (*(int*) (a0[1] + 0x16c) + 0x5d), 2, 6, 0,
		                   0xdd);
		memset(m, 0, sizeof(m));
		m[4] = (char) a0[0];
		*(int*) (m + 8) = *(int*) (g_7f4ca4 +
		                           *(unsigned short*) (*(int*) (a0[1] + 0x16c) + 0x27) * 0x21c);
		*(int*) (m + 0xc) = *(int*) (*(int*) (a0[1] + 0x16c) + 1);
		*(int*) (m + 0x10) = 0;
		*(int*) (m + 0x14) = 0;
		*(int*) (m + 0x28) = *(int*) &g_7f4c00;
		*(int*) (m + 0x2c) = g_7f4c04;
		*(int*) (m + 0x30) = g_7f4c08;
		*(short*) (m + 0x34) = g_7f4c0c;
		m[0x36] = 1;
		*(short*) (m + 0x5a) = *(short*) a0[2];
		if (rec != 0) {
			*(int*) (m + 0x60) = *(int*) (rec + 2);
		} else {
			rec = fcn_005049a0((unsigned char*) *(int*) (a0[1] + 0x16c));
			if (rec != 0) {
				*(int*) (m + 0x60) = *(int*) (rec + 2);
			} else {
				*(int*) (m + 0x60) = -1;
			}
		}
		if (a0[8] < n) {
			for (e = (char*) 0x7f4e05; (int) e <= 0x85a204; e += 0x21c) {
				if (*(short*) (e - 0x165) != -1 &&
				    *(int*) (e + 7) == *(int*) (a0[1] + 0x16c) &&
				    *e != 0 && *(int*) (e + 0x17) == 0 &&
				    *(int*) (e + 0x1f) != 0 &&
				    *(int*) (*(int*) (e + 0x1f) + 0x2c) ==
				        *(int*) (*(int*) (e + 7) + 1)) {
					*(int*) (m + 0x38 + *(int*) (m + 0x10) * 4) =
					    *(int*) (e + 4);
					*(int*) (m + 0x10) = *(int*) (m + 0x10) + 1;
					a0[8] = a0[8] + 1;
				}
				if (a0[8] >= n) {
					break;
				}
			}
		}
		m[0x58] = (char) *(int*) (m + 0x10);
		if (*(int*) (m + 0x10) == 0) {
			a0[7] = a0[7] + 1;
			return;
		}
		if (*(short*) (m + 0x5a) == 0) {
			a0[7] = a0[7] + 1;
			return;
		}
		fcn_004c5530(m);
		a0[7] = a0[7] + 1;
		return;
	}
	if (a0[0] == 0x8c) {
		fcn_00502cd0(*(int*) (*(int*) (a0[1] + 0x16c) + 0x5d), 1, 0, 0xfd);
		if (a0[5] > 1 && a0[7] == 0) {
			n = a0[8] + a0[6] % a0[5] + a0[6] / a0[5];
		} else {
			n = a0[6] / a0[5] + a0[8];
		}
		memset(m, 0, sizeof(m));
		m[4] = (char) a0[0];
		*(int*) (m + 8) = *(int*) (g_7f4ca4 +
		                           *(unsigned short*) (*(int*) (a0[1] + 0x16c) + 0x27) * 0x21c);
		*(int*) (m + 0xc) = *(int*) (*(int*) (a0[1] + 0x16c) + 1);
		*(int*) (m + 0x10) = 0;
		*(int*) (m + 0x14) = 0;
		*(int*) (m + 0x28) = *(int*) &g_7f4c00;
		*(int*) (m + 0x2c) = g_7f4c04;
		*(int*) (m + 0x30) = g_7f4c08;
		*(short*) (m + 0x34) = g_7f4c0c;
		m[0x36] = 1;
		*(short*) (m + 0x58) = *(short*) a0[2];
		if (a0[8] < n) {
			for (e = (char*) 0x7f4e05; (int) e <= 0x85a204; e += 0x21c) {
				if (*(short*) (e - 0x165) != -1 &&
				    *(int*) (e + 7) == *(int*) (a0[1] + 0x16c) &&
				    *e != 0 && *(int*) (e + 0x17) == 0 &&
				    *(int*) (e + 0x1f) != 0 &&
				    *(int*) (*(int*) (e + 0x1f) + 0x2c) ==
				        *(int*) (*(int*) (e + 7) + 1)) {
					*(int*) (m + 0x38 + *(int*) (m + 0x10) * 4) =
					    *(int*) (e + 4);
					*(int*) (m + 0x10) = *(int*) (m + 0x10) + 1;
					a0[8] = a0[8] + 1;
				}
				if (a0[8] >= n) {
					break;
				}
			}
		}
		if (*(int*) (m + 0x10) == 0) {
			a0[7] = a0[7] + 1;
			return;
		}
		if (*(short*) (m + 0x58) == 0) {
			a0[7] = a0[7] + 1;
			return;
		}
		fcn_004c5530(m);
		a0[7] = a0[7] + 1;
		return;
	}
	rec = fcn_005463a0(2, 0, a0[0], 3,
	                   *(int*) (*(int*) (a0[1] + 0x16c) + 1));
	while (rec != 0) {
		if (a0[0] == 4 &&
		    *(unsigned short*) (rec + 0xac) == *(int*) a0[2]) {
			break;
		}
		if (a0[0] == 8 &&
		    *(unsigned short*) (rec + 0xac) == *(int*) a0[2]) {
			break;
		}
		if (a0[0] == 3 &&
		    *(unsigned short*) (rec + 0xac) == *(int*) a0[2]) {
			break;
		}
		rec = he_fn_Handlung();
	}
	if (rec == 0) {
		memset(m, 0, sizeof(m));
		m[4] = (char) a0[0];
		*(int*) (m + 8) = *(int*) (g_7f4ca4 +
		                           *(unsigned short*) (*(int*) (a0[1] + 0x16c) + 0x27) * 0x21c);
		*(int*) (m + 0xc) = *(int*) (*(int*) (a0[1] + 0x16c) + 1);
		*(int*) (m + 0x28) = *(int*) &g_7f4c00;
		*(int*) (m + 0x2c) = g_7f4c04;
		*(int*) (m + 0x30) = g_7f4c08;
		*(int*) (m + 0x10) = 0;
		*(int*) (m + 0x14) = 0;
		*(short*) (m + 0x34) = g_7f4c0c;
		m[0x36] = 1;
		if (a0[0] == 4) {
			*(short*) (m + 0x58) = *(short*) a0[2];
			*(int*) (m + 0x5c) = -1;
			*(int*) (m + 0x68) = *(int*) (*(int*) (a0[1] + 0x16c) + 1);
			*(int*) (m + 0x6c) = *(int*) (a0[3] + 2);
		}
		if (a0[0] == 8) {
			*(short*) (m + 0x58) = *(short*) a0[2];
			*(int*) (m + 0x5c) = *(int*) (*(int*) (a0[1] + 0x16c) + 1);
			*(int*) (m + 0x60) = *(int*) (a0[4] + 2);
		}
		if (a0[0] == 3) {
			*(short*) (m + 0x58) = *(short*) a0[2];
			*(int*) (m + 0x64) = *(int*) (*(int*) (a0[1] + 0x16c) + 1);
			*(int*) (m + 0x6c) = *(int*) (a0[3] + 2);
			*(int*) (m + 0x68) = *(int*) (a0[4] + 2);
		}
		fcn_004c5530(m);
		a0[7] = a0[7] + 1;
		return;
	}
	if (a0[5] > 1 && a0[7] == 0) {
		n = a0[8] + a0[6] % a0[5] + a0[6] / a0[5];
	} else {
		n = a0[6] / a0[5] + a0[8];
	}
	v = 0;
	if (a0[0] == 8 || a0[0] == 3) {
		v = (int) fcn_00502cd0(*(int*) (*(int*) (a0[1] + 0x16c) + 0x5d), 1,
		                       0, 0x37);
	} else if (a0[0] == 4) {
		v = (int) fcn_005049a0((unsigned char*) *(int*) (a0[1] + 0x16c));
	}
	if (a0[8] < n) {
		for (e = (char*) 0x7f4e05; (int) e <= 0x85a204; e += 0x21c) {
			if (*(short*) (e - 0x165) != -1 &&
			    *(int*) (e + 7) == *(int*) (a0[1] + 0x16c) &&
			    *e != 0 && *(int*) (e + 0x17) == 0) {
				fcn_00529160(*(int*) (a0[1] + 0x16c), v,
				             *(short*) (e - 0x165), (int) rec);
				a0[8] = a0[8] + 1;
			}
			if (a0[8] >= n) {
				break;
			}
		}
	}
	a0[7] = a0[7] + 1;
	return;
}
