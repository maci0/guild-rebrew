extern int __cdecl fcn_004f4830(int idx, void* dst);
extern void __cdecl fcn_004a4410(unsigned int* a0, unsigned int* a1,
    unsigned int a2, unsigned char* a3, unsigned int a4, unsigned int a5,
    unsigned int a6);
extern void __cdecl ai_ComputeActionScore(unsigned int* a0, unsigned int* a1,
    unsigned int a2, unsigned char* a3, void* rec);

/* ADDRESS: GOLDTL 0x004995b0 */
void __cdecl ai_ScoreVerpruegeln(unsigned int* outFirst, unsigned int* outSecond, unsigned int methodIndex,
    unsigned char* entity, unsigned int extra1, unsigned int extra2, unsigned int extra3)
{
    int actionDef[9];

    *outFirst = 0;
    *outSecond = 0;
    fcn_004f4830(0x15, actionDef);
    if (actionDef[6] && (entity[2] != 5 || !(entity[0x1c8] & 2))) {
        ai_ComputeActionScore(outFirst, outSecond, methodIndex, entity, actionDef);
        return;
    }
    fcn_004a4410(outFirst, outSecond, methodIndex, entity, extra1, extra2, extra3);
}
