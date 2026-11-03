int __cdecl fcn_004379a0(int, int, int, int, int);
void __cdecl fcn_00445e40(int);

/* ADDRESS: GOLDTL 0x00445ec0 */
void __cdecl fcn_00445ec0(unsigned idx, int arg, char flag)
{
	int base;
	int t1;
	int t2;

	if (idx >= 7) {
		return;
	}
	fcn_004379a0(*(int*) 0x67a370, 0, arg, 0x445d60, idx);
	base = idx * 96;
	t1 = *(int*) 0x67bbdc;
	t2 = *(int*) 0x67bbe0;
	*(int*) (base + 0x1041d80) = t1;
	t1 = *(int*) 0x67bbe4;
	*(int*) (base + 0x1041d84) = t2;
	t2 = *(int*) 0x6b86c4;
	*(int*) (base + 0x1041d88) = t1;
	t1 = *(int*) 0x6b86c8;
	*(int*) (base + 0x1041d8c) = t2;
	t2 = *(int*) 0x6b86cc;
	*(int*) (base + 0x1041d90) = t1;
	*(int*) (base + 0x1041d94) = t2;
	if (flag) {
		fcn_00445e40(idx);
	}
}
