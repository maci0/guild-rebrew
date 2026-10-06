extern unsigned char* g_868050;

int __cdecl gm_CheckEntityType(char*);
char* __cdecl fcn_00500480(char*, int*, int*);
char* __cdecl gm_FindRecordById(int);
int __cdecl fcn_005155e0(char*);
int __cdecl fcn_00515540(char*);
char* __cdecl fcn_00502cd0(int, int, int, int);
char* __cdecl sim_StartEntityQueryByType(char*);

// FUNCTION: GOLDTL 0x567170
int __cdecl fcn_00567170(char* h, int* out1, int* out2, int* out3)
{
	char* q;
	char* t;
	char* e;
	char* r;
	int id;
	unsigned char k;
	unsigned char* ty;

	q = 0;
	t = 0;
	id = -1;
	if (h[2] == 0xd || h[2] == 0xe) {
		return 0;
	}
	if (*(unsigned char**) (h + 0x16c) != 0) {
		ty = g_868050 + **(unsigned char**) (h + 0x16c) * 0x24d;
		if (*ty == 4 || *ty == 0x10 || *ty == 0x13 || *ty == 0x1d || *ty == 0x1e) {
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
	}
	if (*(char**) (h + 0x170) == 0) {
		e = fcn_00500480(h, out1, out2);
		if (e == 0) {
			return 0;
		}
		if (out3 != 0) {
			r = gm_FindRecordById(*out2);
			if (gm_CheckEntityType(e) != 0) {
				*out3 = fcn_005155e0(e);
				return 1;
			}
			if (r != 0) {
				*out3 = fcn_00515540(r);
				return 1;
			}
			*out3 = 0;
			return 1;
		}
	} else {
		if (*(char**) (h + 0x16c) != 0 && gm_CheckEntityType(*(char**) (h + 0x16c)) != 0) {
			q = fcn_00502cd0(*(int*) (*(char**) (h + 0x16c) + 0x5d), 1, 0, 0x2c);
			if (q == 0) {
				q = fcn_00502cd0(*(int*) (*(char**) (h + 0x16c) + 0x5d), 1, 0, 0x109);
				if (q == 0) {
					return 0;
				}
			}
			t = *(char**) (h + 0x16c);
		}
		if (q == 0 && *(char**) (h + 0x170) != 0
		    && (*(char**) (h + 0x16c) == 0 || gm_CheckEntityType(*(char**) (h + 0x16c)) == 0)) {
			q = sim_StartEntityQueryByType(*(char**) (h + 0x170));
			t = *(char**) (h + 0x170);
		}
		if (t == 0) {
			return 0;
		}
		if (q != 0) {
			id = *(int*) (q + 2);
		}
		if (out3 != 0) {
			if (gm_CheckEntityType(t) != 0) {
				*out3 = fcn_005155e0(t);
			} else if (q != 0) {
				*out3 = fcn_00515540(q);
			} else {
				*out3 = -1;
			}
		}
		*out1 = *(int*) (t + 1);
		*out2 = id;
	}
	return 1;
}
