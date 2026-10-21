int __cdecl fcn_00413870(void* o, void** a, void** b, void* c, void* d, void* e);

/* The helper writes two floats through its first pointer pair and reads one
 * 3-float point from each of its three value slots. Two probes run over the
 * same argument slots; when a probe misses, its slot pair holds the endpoint
 * pair and the code picks those, otherwise it takes the componentwise
 * extremes of the two missing endpoints. */
/* ADDRESS: GOLDTL 0x00413c40 */
int __cdecl fcn_00413c40(void* obj, float* outA, float* outB, void* p4, void* p5, void* p6, void* p7)
{
    void* a6;
    int r1;
    int r2;

    a6 = p6;
    r1 = fcn_00413870(obj, &p6, &p5, p4, p5, a6);
    r2 = fcn_00413870(obj, &p4, &obj, a6, p7, p4);
    if (r1 != 0) {
        if (r2 != 0)
            return 1;
        *outA = *(float*) &p4;
        *outB = *(float*) &obj;
        return 0;
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
