extern char* d3_TextureBank;

char __cdecl d3_ReloadTexture(char* a);

/* ADDRESS: GOLDTL 0x0045d090 */
/* ADDRESS: GOLDDE 0x00452040 */
char __cdecl d3_SetTextureFormatAndReload(char* a, int v)
{
	if (a != 0) {
		if ((a[0x54] & 2) != 0) {
			a = d3_TextureBank + *(int*) (a + 0x44) * 0x70;
		}
		if (*(int*) (a + 0x60) != v) {
			*(int*) (a + 0x60) = v;
			return d3_ReloadTexture(a);
		}
	}
	return 0;
}
