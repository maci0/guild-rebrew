typedef struct VfsStream VfsStream;

int __cdecl fcn_004011d0(void *a, void *b);

struct VfsStream {
    int f0;
    int f4;
    int n8;
    int f12;
    char *p16;
};

/* ADDRESS: GOLDTL 0x0044dc30 */
int __cdecl fcn_0044dc30(void *a, VfsStream *b)
{
    return fcn_004011d0(a, b->p16 + b->n8 * 224 + 0xd0);
}
