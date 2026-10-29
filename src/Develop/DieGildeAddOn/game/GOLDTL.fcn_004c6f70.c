int __cdecl fcn_004c4dc0(char*, int);
int __cdecl gm_ResolveEntityById(int*, char**, int*, int);
int __cdecl fcn_00502cd0(int, int, int, int);
int __cdecl gm_eval_SlotVoll(char*, int, int);
char* __cdecl fcn_0050d490(char*);
int __cdecl gm_CheckInventoryCapacity(int, int, int);
int __cdecl gm_QueryEntitySum(int, char);

/* ADDRESS: GOLDTL 0x004c6f70 */
int __cdecl fcn_004c6f70(char* a0)
{
	int v12;
	int v13;
	int v14;
	int id;
	int obj;
	char* p;
	unsigned short type;
	unsigned short w;

	if (*(int*) (a0 + 0x14) != -1) {
		id = fcn_004c4dc0(a0, *(int*) (a0 + 0x14));
		*(int*) (a0 + 0x14) = id;
		if (gm_ResolveEntityById(&v13, &a0, &v12, id) == 0) {
			return 1;
		}
		if (v13 != 0) {
			p = (char*) v13 + 0x5d;
		} else if (a0 != 0) {
			p = a0 + 0x14;
		} else {
			p = (char*) v12 + 0x178;
		}
		obj = fcn_00502cd0(*(int*) p, 1, 0, *(unsigned short*) (a0 + 0x18));
		if (obj == 0) {
			return 1;
		}
		if (*(int*) (obj + 0xe) < *(int*) (a0 + 0x1f)) {
			return 1;
		}
	}
	if (*(int*) (a0 + 0x10) != -1) {
		id = fcn_004c4dc0(a0, *(int*) (a0 + 0x10));
		*(int*) (a0 + 0x10) = id;
		if (gm_ResolveEntityById(&v14, &a0, &v12, id) == 0) {
			return 1;
		}
		if (v14 != 0) {
			if (*(unsigned short*) (v14 + 0x27) != 0xffff) {
				v12 = *(unsigned short*) (v14 + 0x27) * 0x21c + 0x7f4ca0;
			} else {
				v12 = 0;
			}
		} else if (a0 != 0) {
			type = *(unsigned short*) a0;
			if ((type == 0x2a || type == 0x116 || type == 0x1dd) &&
			    gm_eval_SlotVoll(a0, *(unsigned short*) (a0 + 0x18), *(int*) (a0 + 0x1f)) <
				    *(int*) (a0 + 0x1f)) {
				return 1;
			}
			v12 = (int) fcn_0050d490(a0);
		} else {
			if (gm_CheckInventoryCapacity(v12, *(unsigned short*) (a0 + 0x18), *(int*) (a0 + 0x1f)) <
			    *(int*) (a0 + 0x1f)) {
				return 1;
			}
		}
		if (*(int*) (a0 + 0x23) != 0 && v12 != 0) {
			if (gm_QueryEntitySum(*(int*) (v12 + 0x178), *(char*) (a0 + 0x1e)) <
			    *(int*) (a0 + 0x1f) * *(int*) (a0 + 0x23)) {
				return 1;
			}
		}
	}
	return 0;
}
