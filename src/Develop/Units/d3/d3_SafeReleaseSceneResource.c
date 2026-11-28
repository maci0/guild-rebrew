

void __cdecl d3_ReleaseTexture(int);

/* ADDRESS: GOLDDE 0x0046be20 */
void __cdecl d3_SafeReleaseSceneResource(int resource)
{
	if (resource == 0) {
		return;
	}
	d3_ReleaseTexture(resource);
}
