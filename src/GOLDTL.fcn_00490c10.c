typedef struct ENT_490c10 ENT_490c10;
struct ENT_490c10 { unsigned char pad_000[0xac]; float fac; unsigned char pad_0b0[0xb4]; unsigned char f164; };
typedef struct BUF_490c10 BUF_490c10;
struct BUF_490c10 { char pad_00[0x18]; int idx; char pad_1c[8]; };
int __cdecl gm_MapEntityStatRange(int stat_id);
int __cdecl fcn_004f4830(int idx, void* dst);
/* ADDRESS: GOLDTL 0x00490c10 */
int __cdecl fcn_00490c10(ENT_490c10* a0, int unused, int* out)
{
    BUF_490c10 buf;
    int v;
    int t;

    gm_MapEntityStatRange((unsigned char) a0->f164);
    v = (int) ((a0->fac - *(float*) 0x662918) * *(float*) 0x662a98);
    if (v < 4) {
        t = v;
        if (t < 1) {
            t = 1;
        }
    } else {
        t = 4;
    }
    fcn_004f4830(7, &buf);
    if (t != buf.idx) {
        *out = t;
        return 1;
    }
    return 0;
}
