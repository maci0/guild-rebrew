#include <string.h>

typedef struct
{
	char pad00[0x80];
	char name[0x40];
	char pad0c0[0xe0 - 0xc0];
} D3_AGI_MATERIAL;
// SIZE 0xe0

typedef struct
{
	int pad00[2];
	int n;
	int pad0c;
	D3_AGI_MATERIAL* recs;
} D3_MAT_PARSER_CTX;
// SIZE 0x14

extern char s_662d1c[];

char* __cdecl fcn_0064f026(char* s, char* delim);
char* __cdecl fcn_0064d1a0(char* s, int c);
void __cdecl d3_ValidateTextureDimensions(char* name, int flag);

/* ADDRESS: GOLDTL 0x0044d010 */
/* ADDRESS: GOLDDE 0x00442e00 */
void __cdecl d3_ParseMatEnvMap(void* stream, D3_MAT_PARSER_CTX* ctx)
{
	char* tok;
	char* dot;

	tok = fcn_0064f026(0, s_662d1c);
	dot = fcn_0064d1a0(tok, '.');
	if (dot != 0) {
		*dot = 0;
	}
	strcpy(ctx->recs[ctx->n].name, tok);
	d3_ValidateTextureDimensions(ctx->recs[ctx->n].name, 1);
}
