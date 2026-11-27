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
int __cdecl d3_ReadMatVTile(void *stream, VfsStream *ctx)
{
    return fcn_004011d0(stream, ctx->p16 + ctx->n8 * 224 + 0xd0);
}
