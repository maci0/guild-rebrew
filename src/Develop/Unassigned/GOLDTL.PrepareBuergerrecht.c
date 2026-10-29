extern unsigned char g_773d75;

int __cdecl fcn_0050d320(char*, char);

int __cdecl PrepareBuergerrecht(void* kontext, char* objekt, int modus, char* ergebnis)
{
    (void)kontext;
    if (modus != 1) {
        if (modus != 0)
            return 0;
    } else {
        if ((unsigned char)ergebnis[0] != 0x0d || *(int*)(ergebnis + 4) != 2)
            return 0;
    }
    if ((unsigned char)objekt[0x0d] >= 2)
        return 0;
    if ((*(unsigned int*)(objekt + 0x1c8) & 0x4000) == 0)
        return 0;
    modus = fcn_0050d320(objekt, g_773d75);
    if (modus < 0)
        return 0;
    if (modus * 0.44f < 16000.0f)
        return 0;
    ergebnis[0] = 0x0d;
    *(int*)(ergebnis + 4) = 2;
    *(int*)(ergebnis + 8) = 1;
    return 0x19;
}
