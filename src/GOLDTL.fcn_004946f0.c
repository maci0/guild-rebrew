


int __cdecl fcn_00508eb0(unsigned short id, int a2);

int __cdecl fcn_004946f0(unsigned short* a, unsigned short* b, int k)
{
	int d;

	d = fcn_00508eb0(*a, 0);
	d = (d - fcn_00508eb0(*b, 0) + 10) * k * 3;
	return (int) (d * 0.33333334f);
}
