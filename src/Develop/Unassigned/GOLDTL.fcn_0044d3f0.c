typedef struct
{
	char pad00[0x18];
	int a;
	int b;
	int c;
	char pad24[0x38 - 0x24];
} D3_MESH_FACE_REC;
// SIZE 0x38

typedef struct
{
	char pad00[0x18];
	int n;
	int pad1c;
	D3_MESH_FACE_REC* recs;
	char pad24[0x2c - 0x24];
	int base;
} fcn_0044d3f0_Ctx;
// SIZE 0x30

extern char s_662d18[];

char* __cdecl fcn_0064f026(char* s, char* delim);
int __cdecl atoi(char* s);

/* ADDRESS: GOLDTL 0x0044d3f0 */
void __cdecl d3_ParseMeshFaceIndex(void* stream, fcn_0044d3f0_Ctx* ctx)
{
	char* tok;

	tok = fcn_0064f026(0, s_662d18);
	ctx->recs[ctx->n].a = atoi(tok) + ctx->base;
	tok = fcn_0064f026(0, s_662d18);
	ctx->recs[ctx->n].b = atoi(tok) + ctx->base;
	tok = fcn_0064f026(0, s_662d18);
	ctx->recs[ctx->n].c = atoi(tok) + ctx->base;
}
