void __cdecl fcn_00500bb0(char*, int, int, int);

/* ADDRESS: GOLDTL 0x005512f0 */
void __cdecl fcn_005512f0(char* a1)
{
    int* d;

    d = (int*) (void*) (a1 + 0x52);
    d[0] = *(int*) 0x7f4c00;
    d[1] = *(int*) 0x7f4c04;
    d[2] = *(int*) 0x7f4c08;
    ((short*) d)[6] = *(short*) 0x7f4c0c;
    fcn_00500bb0((char*) d, 0, 5, 0);
}
