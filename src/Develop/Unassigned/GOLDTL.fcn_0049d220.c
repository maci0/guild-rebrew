extern double g_662a48;
extern double g_664360;
extern float g_6628b0;

float __cdecl fcn_004fc460(char* p);
int __cdecl fcn_004a4410(float* a0, float* a1, int a2, char* a3, int a4,
    int a5, int a6);
int __cdecl ai_CalculateMatchingMethodEffects(float* a0, float* a1, int a2, char* a3, int a4,
    int a5, int a6);

/* ADDRESS: GOLDTL 0x0049d220 */
int __cdecl ai_ScoreBuergermeister(float* scoreFirst, float* scoreSecond, int a2, char* candidateRecord, int a4,
    int a5, int a6)
{
    float buf[10];
    float t;

    if (candidateRecord[0x166] != 0xf) {
        *scoreFirst = -1e30f;
        *scoreSecond = -1e30f;
        return 0;
    }
    *scoreFirst = 0.0f;
    *scoreSecond = 0.0f;
    fcn_004fc460((char*) buf);
    if ((float) ((*(float*) (candidateRecord + 0x100) - 2.0) * g_664360) < buf[3]) {
        ai_CalculateMatchingMethodEffects(scoreFirst, scoreSecond, a2, candidateRecord, a4, a5, a6);
        t = *scoreFirst;
        *scoreFirst = t * g_6628b0;
        t = *scoreSecond;
        *scoreSecond = t * g_6628b0;
        return 1;
    }
    return fcn_004a4410(scoreFirst, scoreSecond, a2, candidateRecord, a4, a5, a6);
}
