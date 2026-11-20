/* ADDRESS: GOLDTL 0x00413e00 */
int __cdecl fcn_00413e00(float *pointA, float *pointB, float *pointC, float *boxMin,
                         float *boxMax)
{
	float v[8];

	v[0] = ((*pointA < *pointB ? *pointA : *pointB) < *pointC) ? (*pointA < *pointB ? *pointA : *pointB) : *pointC;
	v[1] = ((double) pointC[1] > (double) ((double) pointA[1] < (double) pointB[1] ? pointA[1] : pointB[1])) ? ((double) pointA[1] < (double) pointB[1] ? pointA[1] : pointB[1]) : pointC[1];
	v[2] = ((double) pointC[2] > (double) ((double) pointA[2] < (double) pointB[2] ? pointA[2] : pointB[2])) ? ((double) pointA[2] < (double) pointB[2] ? pointA[2] : pointB[2]) : (double) pointC[2];
	v[3] = ((*pointA > *pointB ? *pointA : *pointB) > *pointC) ? (*pointA > *pointB ? *pointA : *pointB) : *pointC;
	v[6] = ((double) pointC[2] < (double) ((double) pointA[2] > (double) pointB[2] ? pointA[2] : pointB[2])) ? ((double) pointA[2] > (double) pointB[2] ? pointA[2] : pointB[2]) : (double) pointC[2];
	if (!(v[3] < *boxMin) && !(v[0] > *boxMax) && !(v[1] > boxMax[1]) && !(v[6] < boxMin[2]) &&
	    !(v[2] > boxMax[2]))
		return 1;
	return 0;
}
