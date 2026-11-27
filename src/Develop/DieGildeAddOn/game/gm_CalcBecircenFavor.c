


int __cdecl amt_GetEffectiveRoleLevel(unsigned short id, int a2);

int __cdecl gm_CalcBecircenFavor(unsigned short* a, unsigned short* b, int k)
{
	int d;

	d = amt_GetEffectiveRoleLevel(*a, 0);
	d = (d - amt_GetEffectiveRoleLevel(*b, 0) + 10) * k * 3;
	return (int) (d * 0.33333334f);
}
