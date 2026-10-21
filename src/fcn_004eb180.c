extern int __cdecl fcn_005463a0(int, int, int);
extern void __cdecl fcn_004eab40(int);
extern void* __cdecl fcn_00503fe0(int, int, int);

/* ADDRESS: GOLDTL 0x004eb180 */
int __cdecl fcn_004eb180(int v)
{
	int w;
	void* p;

	if (fcn_005463a0(1, 0, 0x80) != 0) {
		fcn_004eab40(0x1e);
		fcn_004eab40(0x1f);
		fcn_004eab40(0x20);
		fcn_004eab40(0x21);
		return 0;
	}
	switch (v) {
	case 1:
		w = 0x18;
		break;
	case 2:
		w = 0x19;
		break;
	case 3:
		w = 0x1a;
		break;
	case 4:
		w = 0x17;
		break;
	case 5:
		return 0;
	default:
		goto ret0;
	}
	p = fcn_00503fe0(1, 5, w);
	if (p == 0 || (((unsigned char*) p)[0x5a] & 1))
		return 0;
	return 1;
ret0:
	return 0;
}
