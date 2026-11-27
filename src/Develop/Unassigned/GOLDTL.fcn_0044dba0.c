typedef struct
{
	char pad00[0xc8];
	char fc8;
	char padc9[0xe0 - 0xc9];
} D3_BIN_MAT_SCROLL_REC;
// SIZE 0xe0

typedef struct
{
	int pad00[2];
	int n;
	int pad0c;
	D3_BIN_MAT_SCROLL_REC* recs;
} fcn_0044dba0_Ctx;
// SIZE 0x14

int __cdecl vfs_ReadByte(void* stream, void* dst);

/* ADDRESS: GOLDTL 0x0044dba0 */
void __cdecl d3_ReadMatScrollMode(void* stream, fcn_0044dba0_Ctx* ctx)
{
	vfs_ReadByte(stream, &ctx->recs[ctx->n].fc8);
}
