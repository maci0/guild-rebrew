/* ADDRESS: GOLDTL 0x004eebb0 */
int __cdecl fcn_004eebb0(void *a, void *b)
{
    float t;

    t = *(float *)((char *)a + 0x10) + *(float *)((char *)b + 4);
    if (t > 0.0f && !(t < 1.0f)) {
        t = 1.0f;
    } else if (!(t > 0.0f)) {
        t = 0.0f;
    }
    *(float *)((char *)b + 4) = t;
    return 1;
}
