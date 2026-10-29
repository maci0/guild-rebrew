int __cdecl fcn_004379a0(int, int, int, int, int);
void __cdecl fcn_00445e40(int);

/* ADDRESS: GOLDTL 0x00445ec0 */
void __cdecl fcn_00445ec0(unsigned idx, int arg, char flag)
{
	int base;
	int t1;

	if (idx >= 7) {
		return;
	}
	fcn_004379a0(*(int*) 0x67a370, 0, arg, 0x445d60, idx);
	t1 = *(int*) 0x67bbe0;
	base = idx * 96;
	*(int*) (base + 0x1041d80) = *(int*) 0x67bbdc;
	*(int*) (base + 0x1041d84) = t1;
	*(int*) (base + 0x1041d88) = *(int*) 0x67bbe4;
	*(int*) (base + 0x1041d8c) = *(int*) 0x6b86c4;
	*(int*) (base + 0x1041d90) = *(int*) 0x6b86c8;
	*(int*) (base + 0x1041d94) = *(int*) 0x6b86cc;
	if (flag) {
		fcn_00445e40(idx);
	}
}
