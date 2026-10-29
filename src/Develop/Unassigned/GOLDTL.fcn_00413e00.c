/* ADDRESS: GOLDTL 0x00413e00 */
int __cdecl fcn_00413e00(float *a0, float *a1, float *a2, float *a3,
                         float *a4)
{
	float v1;
	float v2;
	float v3;
	float v4;
	float v5;

	if (*a0 < *a1)
		v2 = *a0;
	else
		v2 = *a1;
	if (*a2 < v2)
		v1 = *a2;
	else if (*a0 < *a1)
		v1 = *a0;
	else
		v1 = *a1;
	if (a0[1] >= a1[1])
		v2 = a1[1];
	else
		v2 = a0[1];
	if (a2[1] <= v2)
		v2 = a2[1];
	else if (a0[1] >= a1[1])
		v2 = a1[1];
	else
		v2 = a0[1];
	if (a0[2] >= a1[2])
		v3 = a1[2];
	else
		v3 = a0[2];
	if (a2[2] <= v3)
		v3 = a2[2];
	else if (a0[2] >= a1[2])
		v3 = a1[2];
	else
		v3 = a0[2];
	if (*a1 >= *a0)
		v4 = *a1;
	else
		v4 = *a0;
	if (v4 <= *a2)
		v4 = *a2;
	else if (*a1 >= *a0)
		v4 = *a1;
	else
		v4 = *a0;
	if (a1[2] >= a0[2])
		v5 = a1[2];
	else
		v5 = a0[2];
	if (v5 <= a2[2])
		v5 = a2[2];
	else if (a1[2] >= a0[2])
		v5 = a1[2];
	else
		v5 = a0[2];
	if (*a3 <= v4 && v1 <= *a4 && v2 <= a4[1] && a3[2] <= v5 &&
	    v3 <= a4[2])
		return 1;
	return 0;
}
