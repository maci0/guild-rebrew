int __cdecl d2_DrawBankSpriteScaled(int, int, int, void*, int, float);
void __cdecl d2_SetQuadVertexColor(int, unsigned char, unsigned char, unsigned char);


/* ADDRESS: GOLDTL 0x0047cc80 */
int __cdecl d2_DrawScaledSpriteQuad(int a1, int a2, int a3, void* s, int idx, float scale, int tint)
{
	int result;

	result = d2_DrawBankSpriteScaled(a1, a2, a3, s, idx, scale);
	if (tint != 0)
		d2_SetQuadVertexColor(result, 0xff, 0xff, 0xff);
	return 1;
}
