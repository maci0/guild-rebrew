extern float g_6628a0;
extern float g_6628a8;

/* ADDRESS: GOLDTL 0x00459980 */
void __cdecl fcn_00459980(void *a0, void *a1, char a2, float a3)
{
    char c;
    float inv;

    if (a0 == 0 || a1 == 0)
        return;
    c = *(char *)((char *)a1 + 0x2a);
    *(char *)((char *)a1 + 0x28) = c;
    if (a3 != g_6628a8) {
        inv = g_6628a0 / a3;
        *(float *)((char *)a1 + 0xc) = 0.0f;
        *(char *)((char *)a1 + 0x29) = a2;
        *(float *)((char *)a1 + 0x10) = inv;
    } else {
        *(float *)((char *)a1 + 0xc) = 1.0f;
        *(float *)((char *)a1 + 0x10) = 0.0f;
        *(char *)((char *)a1 + 0x29) = c;
    }
}
