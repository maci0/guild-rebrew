extern unsigned char g_slot_table[];
int __cdecl fcn_004f9850(void);
extern float g_773d4c, g_773d50;
/* ADDRESS: GOLD 0x004f9020 */
int __cdecl fcn_004f9020(char* src)
{
    int totals[5] = {0, 0, 0, 0, 0};
    int count;
    int sum;
    int i;
    float a;
    float b;
    unsigned char* e;
    count = 0;
    *(int*) 0x91b4c0 = *(int*) src;
    src += 0x2c;
    *(int*) 0x91b4c4 = *(int*) (src - 0x28);
    *(int*) 0x91b4c8 = *(int*) (src - 0x24);
    *(int*) 0x91b4cc = *(int*) (src - 0x20);
    *(int*) 0x91b4d0 = *(int*) (src - 0x1c);
    sum = 0;
    a = *(float*) (src - 0x18);
    *(float*) 0x91b4d4 = a;
    b = *(float*) (src - 0x14);
    *(float*) 0x91b4d8 = b;
    *(int*) 0x91b4dc = *(int*) (src - 0x10);
    *(int*) 0x91b4e0 = *(int*) (src - 0xc);
    *(int*) 0x91b4e4 = *(int*) (src - 0x8);
    *(int*) 0x91aaf4 = *(int*) (src - 0x4);
    *(int*) 0x91b470 = *(int*) src;
    *(int*) 0x91b474 = *(int*) (src + 0x4);
    *(int*) 0x91b478 = *(int*) (src + 0x8);
    *(unsigned short*) 0x91b47c = *(unsigned short*) (src + 0xc);
    g_773d4c = b;
    g_773d50 = a;
    for (e = g_slot_table + 2;
         (int) e < (int) g_slot_table + 0x65402; e += 0x21c) {
        if (*(unsigned short*) (e - 2) != 0xffff && e[0] < 10 && e[6] > 0) {
            count++;
            sum += e[0xb] * 5;
            for (i = 0; i < 5; i++)
                totals[i] += e[0x7e + i];
        }
    }
    for (i = 0; i < 5; i++)
        ((unsigned char*) 0x91b460)[i] = (unsigned char) (int) ((float) totals[i] / count);
    *(unsigned char*) 0x91b465 = (unsigned char) (int) ((float) sum / count);
    return fcn_004f9850();
}
