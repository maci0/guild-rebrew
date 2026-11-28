typedef struct
{
	char pad00[0xc0];
	char fc0;
	char padc1[0xe0 - 0xc1];
} D3_BIN_MAT_ALPHA_REC;
// SIZE 0xe0

typedef struct
{
	int pad00[2];
	int n;
	int pad0c;
	D3_BIN_MAT_ALPHA_REC* recs;
} D3_BIN_MAT_ALPHA_CTX;
// SIZE 0x14

int __cdecl vfs_ReadByte(void* stream, void* dst);

/* ADDRESS: GOLDTL 0x0044da30 */
/* ADDRESS: GOLDDE 0x00443770 */
void __cdecl d3_ReadMatAlphaType(void* stream, D3_BIN_MAT_ALPHA_CTX* ctx)
{
	vfs_ReadByte(stream, &ctx->recs[ctx->n].fc0);
}
