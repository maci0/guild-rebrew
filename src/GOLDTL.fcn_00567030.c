// FUNCTION: GOLDTL 0x567030
// SIZE: 313

int __cdecl gm_CheckEntityType(char*);
char* __cdecl fcn_005049a0(char*);
char* __cdecl fcn_00502cd0(int, int, int, int);

int __cdecl fcn_00567030(char* h, int* out1, int* out2)
{
	int id;
	char* q;
	unsigned char k;

	id = -1;
	if (h == 0 || h[2] == 0xd || h[2] == 0xe || *(char**) (h + 0x16c) == 0 || *(char**) (h + 0x184) == 0) {
		return 0;
	}
	k = h[0x180];
	if (k == 0x3f || k == 0x40 || k == 0x48 || k == 0x3c || k == 0x49 || k == 0x44 || k == 0x62 || k == 0x61
	    || k == 0x65 || k == 0x64 || k == 0x14 || k == 0x75 || k == 0x1a || k == 0x18 || k == 0xa1) {
		return 0;
	}
	if (h[0x1b1] != 0) {
		return 0;
	}
	if (gm_CheckEntityType(*(char**) (h + 0x16c)) == 0) {
		if (*(int*) (*(char**) (h + 0x184) + 0x2c) == *(int*) (*(char**) (h + 0x16c) + 1)
		    || (q = fcn_005049a0(*(char**) (h + 0x16c))) == 0) {
			return 0;
		}
	} else {
		if (h[0x180] == 3 || h[0x180] == 8 || h[0x180] == 9) {
			q = fcn_00502cd0(*(int*) (*(char**) (h + 0x16c) + 0x5d), 1, 0, 0x37);
		} else {
			q = fcn_00502cd0(*(int*) (*(char**) (h + 0x16c) + 0x5d), 1, 0, 0xfd);
		}
		if (q == 0) {
			goto out;
		}
		if (*(int*) (q + 2) == *(int*) (*(char**) (h + 0x184) + 0x30)) {
			return 0;
		}
		if (*(short*) q == 0xfd) {
			goto out;
		}
	}
	id = *(int*) (q + 2);
out:
	*out1 = *(int*) (*(char**) (h + 0x16c) + 1);
	*out2 = id;
	return 1;
}
