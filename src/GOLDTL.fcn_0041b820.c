void __cdecl fcn_0041b870(void);

/* ADDRESS: GOLDTL 0x0041b820 */
void __cdecl fcn_0041b820(float* a, float* b, float* c)
{
	float* p;
	float* q;
	float* r;
	int i;

	p = (float*) 0x6b5df8;
	q = (float*) 0x6777b0;
	r = (float*) 0x6777bc;
	for (i = 0; i < 3; i++) {
		p[i] = a[i];
		q[i] = b[i];
		r[i] = c[i];
	}
	fcn_0041b870();
}
