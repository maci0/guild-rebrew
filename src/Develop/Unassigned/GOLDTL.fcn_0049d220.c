extern double g_662a48;
extern double g_664360;
extern float g_6628b0;

float __cdecl fcn_004fc460(char* p);
int __cdecl fcn_004a4410(float* a0, float* a1, int a2, char* a3, int a4,
    int a5, int a6);
int __cdecl fcn_004a4550(float* a0, float* a1, int a2, char* a3, int a4,
    int a5, int a6);

/* ADDRESS: GOLDTL 0x0049d220 */
int __cdecl fcn_0049d220(float* a0, float* a1, int a2, char* a3, int a4,
    int a5, int a6)
{
    float buf[10];
    float t;

    if (a3[0x166] != 0xf) {
        *a0 = -1e30f;
        *a1 = -1e30f;
        return 0;
    }
    *a0 = 0.0f;
    *a1 = 0.0f;
    fcn_004fc460((char*) buf);
    if ((float) ((*(float*) (a3 + 0x100) - g_662a48) * g_664360) < buf[3]) {
        fcn_004a4550(a0, a1, a2, a3, a4, a5, a6);
        t = *a0;
        *a0 = t * g_6628b0;
        t = *a1;
        *a1 = t * g_6628b0;
        return 1;
    }
    return fcn_004a4410(a0, a1, a2, a3, a4, a5, a6);
}
