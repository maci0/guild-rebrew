

typedef struct D3_BIN_MESH_BUILD_CTX {
	int pad0[5];
	int f14;
	int pad18;
	int f1c;
	int pad20;
	int f24;
	int pad28;
	int f2c;
} D3_BIN_MESH_BUILD_CTX;
// SIZE 0x30

void __cdecl d3_FinalizeBinMeshSection(int unused, D3_BIN_MESH_BUILD_CTX* ctx)
{
	ctx->f1c += ctx->f14;
	ctx->f14 = 0;
	ctx->f2c += ctx->f24;
	ctx->f24 = 0;
}
