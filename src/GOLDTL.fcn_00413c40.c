int __cdecl fcn_00413870(void* obj, void* a, void* b, void* c, void* d, void* e);

/* Two probes of the same helper. When either probe misses, copy one
 * endpoint into each output; when both miss, keep the lesser first
 * coordinate and the greater second. A hit on both returns 1.
 * The volatile reads are the original pointer bits: the helper
 * overwrites those slots, and the second probe still needs the
 * originals. p5 stays in eax; p6 and p4 are read after it so they
 * land in esi and edi. */
/* ADDRESS: GOLDTL 0x00413c40 */

int __cdecl fcn_00413c40(void* obj, float* outA, float* outB, float* p4, float* p5, float* p6, float* p7)
{
	float* a5;
	float* a6;
	float* a4;
	void* o;
	int r1;
	int r2;

	a5 = *(float* volatile*) &p5;
	a6 = *(float* volatile*) &p6;
	a4 = *(float* volatile*) &p4;
	o = *(void* volatile*) &obj;
	r1 = fcn_00413870(o, &p6, &p5, a4, a5, a6);
	r2 = fcn_00413870(o, &p4, &obj, a6, p7, a4);
	if (r1 != 0) {
		if (r2 == 0) {
			*outA = *(float*) &p4;
			*outB = *(float*) &obj;
			return 0;
		}
		return 1;
	}
	if (r2 != 0) {
		*outA = *(float*) &p6;
		*outB = *(float*) &p5;
		return 0;
	}
	*outA = *(float*) &p6 < *(float*) &p4 ? *(float*) &p6 : *(float*) &p4;
	*outB = *(float*) &p5 > *(float*) &obj ? *(float*) &p5 : *(float*) &obj;
	return 0;
}
