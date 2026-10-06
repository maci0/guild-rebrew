// FUNCTION: GOLD 0x0050b010
// FUNCTION: GOLDTL 0x0050e4a0

void* __cdecl fcn_00503fe0(int a, int b, int c);

void* __cdecl fcn_0050e4a0(int k)
{
	void* r;

	r = 0;
	switch (k) {
	case 1:
		r = fcn_00503fe0(1, 5, 0xf);
		break;
	case 6:
	case 7:
		r = 0;
		break;
	case 2:
		r = fcn_00503fe0(1, 5, 0x17);
		break;
	case 3:
		r = fcn_00503fe0(1, 5, 0x18);
		break;
	case 4:
		r = fcn_00503fe0(1, 5, 0x19);
		break;
	case 5:
		r = fcn_00503fe0(1, 5, 0x1a);
		break;
	}
	return r;
}
