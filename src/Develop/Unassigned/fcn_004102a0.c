int __cdecl fcn_0041dd90(void*);
void __cdecl fcn_00425bf0(void*, int, char*);


/* ADDRESS: GOLDTL 0x004102a0 */
int __cdecl fcn_004102a0(void** a1, int* v1, int* v2, int* v3)
{
    char* p;
    float t1, t2, t3;

    p = (char*) *a1;
    if (!fcn_0041dd90(p)) {
        fcn_00425bf0(*(void**) 0x6b7e98,
            *(int*) ((char*) *(void**) 0x6b7e98 + 0x118),
            (char*) 0x676b0c);
        return 0;
    }
    t1 = (float) *v2 * *(float*) 0x662a2c;
    t2 = (float) *v3 * *(float*) 0x662a2c;
    t3 = (float) *v1 * *(float*) 0x662a2c;
    *(float*) (p + 0x98) = t3;
    *(float*) (p + 0x9c) = t1;
    *(float*) (p + 0xa0) = t2;
    return 0;
}
