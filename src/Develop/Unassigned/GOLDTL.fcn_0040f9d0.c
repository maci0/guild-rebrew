extern int __cdecl rand(void);

typedef struct
{
    float x00;
    float x04;
    float x08;
    int   pad0c;
    float x10;
    float x14;
    float x18;
    int   pad1c;
    int   pad20;
    int   pad24;
    int   pad28;
    int   pad2c;
    int   x30;
    int   pad34;
    float x38;
    float x3c;
    float x40;
    int   pad44;
    float x48;
    unsigned char x4c;
    unsigned char x4d;
    unsigned char x4e;
    unsigned char x4f;
    unsigned char unknown50[4];
} PARTICLE;

typedef struct
{
    unsigned char pad00[0x28];
    PARTICLE *items;
    unsigned char pad2c[0xd8 - 0x2c];
    int count;
    unsigned char pade0[0xe4 - 0xdc];
    int xE4;
} PARTICLE_CTX;

/* ADDRESS: GOLDTL 0x0040f9d0 */
void __cdecl fcn_0040f9d0(PARTICLE_CTX *ctx, int arg)
{
    int i;

    double f;



    for (i = 0; i < ctx->count; i++)
    {

        f = (unsigned int)(arg - ctx->items[i].x30) * 0.001;
        ctx->items[i].x38 = ctx->items[i].x10 + ctx->items[i].x00;
        ctx->items[i].x3c = ctx->items[i].x14 + ctx->items[i].x04;
        ctx->items[i].x40 = ctx->items[i].x18 + ctx->items[i].x08;
        ctx->items[i].x48 = (float)(f + f + ctx->items[i].x48);
        ctx->items[i].x04 = (float)(ctx->items[i].x04 - f);
        if (ctx->items[i].x3c < 0.0)
        {
            ctx->items[i].x38 = 0.0f;
            ctx->items[i].x3c = 100.0f;
            ctx->items[i].x40 = 0.0f;
            ctx->items[i].x00 = (float)(rand() * 3.051851e-05f * 0.2 - 0.1);
            ctx->items[i].x04 = (float)(0.1 - (rand() * 3.051851e-05f + 1.0) * 0.2);
            ctx->items[i].x08 = (float)(-0.5 - ctx->items[i].x04);
            ctx->items[i].x30 = arg;
            ctx->items[i].x48 = *(float *)&ctx->xE4;
        }
        ctx->items[i].x10 = ctx->items[i].x38;
        ctx->items[i].x14 = ctx->items[i].x3c;
        ctx->items[i].x18 = ctx->items[i].x40;
        ctx->items[i].x4f = (unsigned char)
            (0.0 > ctx->items[i].x3c * 1.5 - 20.0
             ? 0.0 : ctx->items[i].x3c * 1.5 - 20.0);

    }
}
