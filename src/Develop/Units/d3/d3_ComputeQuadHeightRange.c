int __cdecl d3_ComputeTriangleHeightRange(void* o, void* a, void* b, void* c, void* d, void* e);

/* The helper writes two floats through its first pointer pair and reads one
 * 3-float point from each of its three value slots. Two probes run over the
 * same argument slots; when a probe misses, its slot pair holds the endpoint
 * pair and the code picks those, otherwise it takes the componentwise
 * extremes of the two missing endpoints. */
/* ADDRESS: GOLDTL 0x00413c40 */
/* ADDRESS: GOLDDE 0x004121f0 */
int __cdecl d3_ComputeQuadHeightRange(void* obj, float* outA, float* outB, void* p4, void* p5, void* p6, void* p7)
{
    void* thirdPoint;
    void* first;
    void* object;
    int r1;
    int r2;

    object = obj;
    first = p4;
    thirdPoint = p6;
    r1 = d3_ComputeTriangleHeightRange(obj, &p6, &p5, p4, p5, thirdPoint);
    r2 = d3_ComputeTriangleHeightRange(object, &p4, &obj, thirdPoint, p7, first);
    if (r1 != 0 && r2 != 0)
        return 1;
    if (r1 == 0) {
        if (r2 == 0) {
            *outA = *(float*) &p6 < *(float*) &p4 ? *(float*) &p6 : *(float*) &p4;
            *outB = *(float*) &p5 > *(float*) &obj ? *(float*) &p5 : *(float*) &obj;
            return 0;
        }
        *outA = *(float*) &p6;
        *outB = *(float*) &p5;
        return 0;
    }
    *outA = *(float*) &p4;
    *outB = *(float*) &obj;
    return 0;
}
