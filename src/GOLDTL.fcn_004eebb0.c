/* ADDRESS: GOLDTL 0x004eebb0 */
int __cdecl fcn_004eebb0(void *a, void *b)
{
    float t;

    t = *(float *)((char *)a + 0x10) + *(float *)((char *)b + 4);
    if (t > 0.0f) {
        if (t < 1.0f)
            *(float *)((char *)b + 4) = t;
        else
            *(float *)((char *)b + 4) = 1.0f;
    } else {
        *(float *)((char *)b + 4) = 0.0f;
    }
    return 1;
}
