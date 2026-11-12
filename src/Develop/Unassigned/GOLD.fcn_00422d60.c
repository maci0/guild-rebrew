__declspec(dllimport) long __stdcall CoInitialize(void*);

/* ADDRESS: GOLD 0x00422d60 */
int __cdecl fcn_00422d60(void)
{
    CoInitialize(0);
    *(int*) 0x14613fc = 0x29a;
    *(short*) 0x14613f8 = 0;
    return 1;
}
