typedef struct
{
	char pad0000[0x2c];
	int f02c;
	int f030;
	int f034;
	int f038;
} fcn_00472fe0_Ctx;
// SIZE 0x3c

extern int g_772568;

void* __cdecl d2_GetResourceData(int bild);
void __cdecl fcn_0047a040(int a, int b, int c, int d);
void __cdecl fcn_0047cba0(int x, int y, int surf, char* font, int c);

/* ADDRESS: GOLDTL 0x00472fe0 */
void __cdecl fcn_00472fe0(int x, int y, int bild, fcn_00472fe0_Ctx* ctx)
{
	char* font;

	font = (char*) d2_GetResourceData(bild);
	fcn_0047a040(ctx->f02c, ctx->f030, ctx->f034, ctx->f038);
	fcn_0047cba0(x, y, (int) ctx, font, g_772568);
}
