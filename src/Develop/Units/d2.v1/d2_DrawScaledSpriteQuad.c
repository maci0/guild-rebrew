int __cdecl d2_DrawBankSpriteScaled(int, int, int, void*, int, float);
void __cdecl d2_SetQuadVertexColor(int, unsigned char, unsigned char, unsigned char);


/* ADDRESS: GOLDTL 0x0047cc80 */
/* ADDRESS: GOLDDE 0x0046bc50 */
int __cdecl d2_DrawScaledSpriteQuad(int x, int y, int surf, void* shapeBank, int idx, float scale, int tint)
{
	int result;

	result = d2_DrawBankSpriteScaled(x, y, surf, shapeBank, idx, scale);
	if (tint != 0)
		d2_SetQuadVertexColor(result, 0xff, 0xff, 0xff);
	return 1;
}
