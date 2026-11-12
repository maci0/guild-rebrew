extern int g_770b80[];
int __cdecl fcn_004f9850(void);

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

    *(int*) 0x91b4c0 = *(int*) src;
    *(int*) 0x91b4c4 = *(int*) (src + 4);
    *(int*) 0x91b4c8 = *(int*) (src + 8);
    *(int*) 0x91b4cc = *(int*) (src + 0xc);
    *(int*) 0x91b4d0 = *(int*) (src + 0x10);
    a = *(float*) (src + 0x14);
    *(float*) 0x91b4d4 = a;
    b = *(float*) (src + 0x18);
    *(float*) 0x91b4d8 = b;
    *(int*) 0x91b4dc = *(int*) (src + 0x1c);
    *(int*) 0x91b4e0 = *(int*) (src + 0x20);
    *(int*) 0x91b4e4 = *(int*) (src + 0x24);
    *(int*) 0x91aaf4 = *(int*) (src + 0x28);
    *(int*) 0x91b470 = *(int*) (src + 0x2c);
    *(int*) 0x91b474 = *(int*) (src + 0x30);
    *(int*) 0x91b478 = *(int*) (src + 0x34);
    *(unsigned short*) 0x91b47c = *(unsigned short*) (src + 0x38);
    *(float*) 0x6f1b9c = b;
    *(float*) 0x6f1ba0 = a;
    count = 0;
    sum = 0;
    for (e = (unsigned char*) g_770b80;
         e < (unsigned char*) g_770b80 + 0x65400; e += 0x21c) {
        if (*(unsigned short*) e != 0xffff && e[2] < 10 && e[8] > 0) {
            count++;
            sum += e[0xd] * 5;
            for (i = 0; i < 5; i++)
                totals[i] += e[0x80 + i];
        }
    }
    for (i = 0; i < 5; i++)
        ((unsigned char*) 0x91b460)[i] = (unsigned char) (int) ((float) totals[i] / count);
    *(unsigned char*) 0x91b465 = (unsigned char) (int) ((float) sum / count);
    return fcn_004f9850();
}
