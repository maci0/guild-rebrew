extern char g_6b7e98[];
extern char g_676b0c[];
extern char g_662a2c[];
int __cdecl fcn_0041dd90(void*);
void __cdecl evt_LogScriptError(void*, int, char*);


/* ADDRESS: GOLDTL 0x004102a0 */
/* ADDRESS: GOLDDE 0x0040f0a0 */
int __cdecl SetEmitterAcceleration(void** emitter, int* x, int* y, int* z)
{
    char* p;
    float scaledY, scaledZ, scaledX;

    p = (char*) *emitter;
    if (!fcn_0041dd90(p)) {
        evt_LogScriptError(*(void**) &g_6b7e98,
            *(int*) ((char*) *(void**) &g_6b7e98 + 0x118),
            (char*) &g_676b0c);
        return 0;
    }
    scaledY = (float) *y * *(float*) &g_662a2c;
    scaledZ = (float) *z * *(float*) &g_662a2c;
    scaledX = (float) *x * *(float*) &g_662a2c;
    *(float*) (p + 0x98) = scaledX;
    *(float*) (p + 0x9c) = scaledY;
    *(float*) (p + 0xa0) = scaledZ;
    return 0;
}
