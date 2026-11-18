extern int __cdecl fcn_004f4830(int idx, void* dst);
extern void __cdecl fcn_004a4410(unsigned int* a0, unsigned int* a1,
    unsigned int a2, unsigned char* a3, unsigned int a4, unsigned int a5,
    unsigned int a6);
extern void __cdecl fcn_004a4680(unsigned int* a0, unsigned int* a1,
    unsigned int a2, unsigned char* a3, void* rec);

/* ADDRESS: GOLDTL 0x004995b0 */
void __cdecl fcn_004995b0(unsigned int* outFirst, unsigned int* outSecond, unsigned int a2,
    unsigned char* record, unsigned int a4, unsigned int a5, unsigned int a6)
{
    int rec[9];

    *outFirst = 0;
    *outSecond = 0;
    fcn_004f4830(0x15, rec);
    if (rec[6] && (record[2] != 5 || !(record[0x1c8] & 2))) {
        fcn_004a4680(outFirst, outSecond, a2, record, rec);
        return;
    }
    fcn_004a4410(outFirst, outSecond, a2, record, a4, a5, a6);
}
