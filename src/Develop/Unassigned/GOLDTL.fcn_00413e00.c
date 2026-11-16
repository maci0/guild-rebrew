/* ADDRESS: GOLDTL 0x00413e00 */
int __cdecl fcn_00413e00(float *a0, float *a1, float *a2, float *a3,
                         float *a4)
{
	float v[7];

	if (*a0 < *a1)
		v[1] = *a0;
	else
		v[1] = *a1;
	if (!(v[1] < *a2))
		v[0] = *a2;
	else if (*a0 < *a1)
		v[0] = *a0;
	else
		v[0] = *a1;
	if (!(a1[1] > a0[1]))
		v[1] = a1[1];
	else
		v[1] = a0[1];
	if (!(v[1] < a2[1]))
		v[1] = a2[1];
	else if (!(a1[1] > a0[1]))
		v[1] = a1[1];
	else
		v[1] = a0[1];
	if (!(a1[2] > a0[2]))
		v[2] = a1[2];
	else
		v[2] = a0[2];
	if (!(v[2] < a2[2]))
		v[2] = a2[2];
	else if (!(a1[2] > a0[2]))
		v[2] = a1[2];
	else
		v[2] = a0[2];
	if (!(*a0 > *a1))
		v[3] = *a1;
	else
		v[3] = *a0;
	if (!(v[3] > *a2))
		v[3] = *a2;
	else if (!(*a0 > *a1))
		v[3] = *a1;
	else
		v[3] = *a0;
	if (!(a1[2] < a0[2]))
		v[6] = a1[2];
	else
		v[6] = a0[2];
	if (!(v[6] > a2[2]))
		v[6] = a2[2];
	else if (!(a1[2] < a0[2]))
		v[6] = a1[2];
	else
		v[6] = a0[2];
	if (!(v[3] < *a3) && !(v[0] > *a4) && !(v[1] > a4[1]) && !(v[6] < a3[2]) &&
	    !(v[2] > a4[2]))
		return 1;
	return 0;
}
