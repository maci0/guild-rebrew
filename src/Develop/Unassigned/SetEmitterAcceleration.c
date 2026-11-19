int __cdecl fcn_0041dd90(void*);
void __cdecl evt_LogScriptError(void*, int, char*);


/* ADDRESS: GOLDTL 0x004102a0 */
int __cdecl SetEmitterAcceleration(void** emitter, int* x, int* y, int* z)
{
    char* p;
    float scaledY, scaledZ, scaledX;

    p = (char*) *emitter;
    if (!fcn_0041dd90(p)) {
        evt_LogScriptError(*(void**) 0x6b7e98,
            *(int*) ((char*) *(void**) 0x6b7e98 + 0x118),
            (char*) 0x676b0c);
        return 0;
    }
    scaledY = (float) *y * *(float*) 0x662a2c;
    scaledZ = (float) *z * *(float*) 0x662a2c;
    scaledX = (float) *x * *(float*) 0x662a2c;
    *(float*) (p + 0x98) = scaledX;
    *(float*) (p + 0x9c) = scaledY;
    *(float*) (p + 0xa0) = scaledZ;
    return 0;
}
