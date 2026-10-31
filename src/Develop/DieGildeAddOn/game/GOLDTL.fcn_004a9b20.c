#include <string.h>

typedef struct {
	char text[0x21c];
	int found;
} sel_ctx;

unsigned short __cdecl gm_RandomMod(int);
char* __cdecl fcn_005463a0(int, int, int);
char* __cdecl he_fn_Handlung(void);
int __cdecl gm_LookupEntityRecordById(int);
int __cdecl fcn_004fa5b0(int, char*, int);
int __cdecl fcn_004a8880(char*, char*, int, char*, int);
int __cdecl fcn_004a8b70(char*, char*, int, char*, int);
int __cdecl fcn_004a8bf0(char*, char*, int, char*, int);
int __cdecl fcn_004a8d10(char*, char*, int, char*, int);
int __cdecl fcn_004a8d40(char*, char*, int, char*, int);
int __cdecl fcn_004a8da0(char*, char*, int, char*, int);
int __cdecl fcn_004a8e40(char*, char*, int, char*, int);
int __cdecl fcn_004a8ed0(char*, char*, int, char*, int);
int __cdecl fcn_004a9000(char*, char*, int, char*, int);
int __cdecl fcn_004a9040(char*, char*, int, char*, int);
int __cdecl fcn_004a9150(char*, char*, int, char*, int);
int __cdecl fcn_004a91a0(char*, char*, int, char*, int);
int __cdecl fcn_004a9270(char*, char*, int, char*, int);
int __cdecl fcn_004a96f0(char*, char*, int, char*, int);
int __cdecl fcn_004a9780(char*, char*, int, char*, int);
int __cdecl fcn_004a9820(char*, char*, int, char*, int);
int __cdecl fcn_004a99a0(char*, char*, int, char*, int);

/* ADDRESS: GOLDTL 0x004a9b20 */
int __cdecl fcn_004a9b20(char* a0, char* a1, int a2, char* a3, int a4)
{
	sel_ctx c;
	int ids1[19];
	int ids2[19];
	int* p;
	int n1;
	int n2;
	int id;
	int sel;
	char* e;

	memset(&c, 0, sizeof(c));
	if (*(int*) (a1 + 0x1c8) & 0x100) {
		e = fcn_005463a0(1, 0, 0x45);
		while (e != 0) {
			if (*(int*) (e + 0xac) == *(int*) (a1 + 4)) {
				c.found = gm_LookupEntityRecordById(*(int*) (e + 0xb0));
				break;
			}
			e = he_fn_Handlung();
		}
	}
	if (*a3 != 0) {
		if (*a3 != 0x10) {
			return 0;
		}
		id = *(int*) (a3 + 4);
		*(int*) c.text = 1;
		if (fcn_004fa5b0(id, a1, (int) &c) & 2) {
			*(int*) (a3 + 8) = 3;
		} else {
			*(int*) c.text = 2;
			if (!(fcn_004fa5b0(id, a1, (int) &c) & 2)) {
				return 0;
			}
			*(int*) (a3 + 8) = 4;
		}
	} else {
		*(int*) c.text = 1;
		n1 = 0;
		for (p = (int*) 0x67fa58; p < (int*) 0x67faa4; p++) {
			if (fcn_004fa5b0(*p, a1, (int) &c) & 2) {
				ids1[n1] = *p;
				n1++;
			}
		}
		n2 = 0;
		if (c.found != 0) {
			*(int*) c.text = 2;
			for (p = (int*) 0x67fa58; p < (int*) 0x67faa4; p++) {
				if (fcn_004fa5b0(*p, a1, (int) &c) & 2) {
					ids2[n2] = *p;
					n2++;
				}
			}
		}
		if (n1 != 0) {
			if (n2 != 0 && gm_RandomMod(2) != 0) {
				goto pick_second;
			}
			*(int*) c.text = 1;
			id = ids1[gm_RandomMod(n1)];
			sel = 3;
			if (!(fcn_004fa5b0(id, a1, (int) &c) & 2)) {
				return 0;
			}
		} else {
			if (n2 == 0) {
				return 0;
			}
pick_second:
			*(int*) c.text = 2;
			id = ids2[gm_RandomMod(n2)];
			sel = 4;
			if (!(fcn_004fa5b0(id, a1, (int) &c) & 2)) {
				return 0;
			}
		}
		*a3 = 0x10;
		*(int*) (a3 + 4) = id;
		*(int*) (a3 + 8) = sel;
	}
	if ((unsigned int) (id - 0x12) > 0x25) {
		return 0;
	}
	switch (id) {
	case 0x12:
		return fcn_004a8880(a0, a1, (int) &c, a3, a4);
	case 0x13:
	case 0x14:
		return fcn_004a8b70(a0, a1, (int) &c, a3, a4);
	case 0x1c:
		return fcn_004a8bf0(a0, a1, (int) &c, a3, a4);
	case 0x1d:
		return fcn_004a8d10(a0, a1, (int) &c, a3, a4);
	case 0x21:
		/* native 0x004a8d30 has no function inventory row */
		return ((int (__cdecl*) (char*, char*, int, char*, int)) 0x4a8d30)(a0, a1,
			(int) &c, a3, a4);
	case 0x24:
		return fcn_004a8d40(a0, a1, (int) &c, a3, a4);
	case 0x25:
		return fcn_004a8da0(a0, a1, (int) &c, a3, a4);
	case 0x27:
		return fcn_004a8e40(a0, a1, (int) &c, a3, a4);
	case 0x28:
		return fcn_004a8ed0(a0, a1, (int) &c, a3, a4);
	case 0x29:
		return fcn_004a9000(a0, a1, (int) &c, a3, a4);
	case 0x2a:
		return fcn_004a9040(a0, a1, (int) &c, a3, a4);
	case 0x2b:
		return fcn_004a9150(a0, a1, (int) &c, a3, a4);
	case 0x2c:
		return fcn_004a91a0(a0, a1, (int) &c, a3, a4);
	case 0x2d:
		return fcn_004a9270(a0, a1, (int) &c, a3, a4);
	case 0x31:
		return fcn_004a96f0(a0, a1, (int) &c, a3, a4);
	case 0x32:
		return fcn_004a9780(a0, a1, (int) &c, a3, a4);
	case 0x35:
		return fcn_004a9820(a0, a1, (int) &c, a3, a4);
	case 0x37:
		return fcn_004a99a0(a0, a1, (int) &c, a3, a4);
	}
	return 0;
}
