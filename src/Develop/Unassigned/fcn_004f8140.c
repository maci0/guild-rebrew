int __cdecl fcn_004f4980(void* p, int a, int* out);
void __cdecl fcn_004f5110(void* p, int v);
int __cdecl fcn_005d6540(void* a, void* b);

/* ADDRESS: GOLDTL 0x004f8140 */
int __cdecl fcn_004f8140(int a1, int a2)
{
	int local[9];
	int st;
	int r;
	int v;

	r = 0;
	st = *(int*) a2;
	if (st == 3 || st == 1) {
		if (*(unsigned char*) (a1 + 0x166) == 0)
			return 1;
		if (fcn_004f4980((void*) a1, 1, local) == 0)
			return 1;
		if (*(unsigned char*) (a1 + 2) == 6) {
			fcn_004f5110((void*) (a2 + 0x14), local[0] & 0xff);
		}
		v = *(int*) (a1 + 0x1c8);
		if ((v & 0x200) != 0)
			return 9;
		if ((v & 0x80000) != 0)
			return 1;
		*(int*) (a2 + 4) = local[0] & 0xff;
		if (*(int*) a2 == 3) {
			*(int*) (a2 + 0x214) = 1;
			r = fcn_005d6540((void*) a1, (void*) a2);
		}
		return r | 2;
	}
	if (st != 4 && st != 2)
		return 1;
	if ((*(int*) (a1 + 0x1c8) & 0x100) == 0)
		return 1;
	v = *(int*) (a2 + 0x21c);
	if (v == 0)
		return 1;
	if (*(unsigned char*) (v + 0x166) == 0)
		return 1;
	if ((*(int*) (v + 0x1c8) & 0x80000) != 0)
		return 1;
	if (fcn_004f4980((void*) v, 1, local) == 0)
		return 1;
	*(int*) (a2 + 4) = local[0] & 0xff;
	if (*(int*) a2 == 4) {
		*(int*) (a2 + 0x214) = 1;
		r = fcn_005d6540((void*) a1, (void*) a2);
	} else if (*(unsigned char*) (a1 + 2) == 6) {
		fcn_004f5110((void*) (a2 + 0x14), local[0] & 0xff);
	}
	return r | 0xa;
}
