extern char* d2_OverlaySprites[];

void __cdecl d3_SafeReleaseSceneResource(void* p);
void __cdecl m_FreeTracked(void* p);

/* ADDRESS: GOLDTL 0x00473150 */
/* ADDRESS: GOLDDE 0x00466160 */
void __cdecl d2_ReleaseOverlaySprite(char* p)
{
	int i;

	for (i = 0; i < 32; i++) {
		if (d2_OverlaySprites[i] == p) {
			d2_OverlaySprites[i] = 0;
			if (*(void**) (p + 0x60) != 0) {
				d3_SafeReleaseSceneResource(*(void**) (p + 0x60));
			}
			m_FreeTracked(p);
			return;
		}
	}
}
