

void __cdecl d3_ReleaseTexture(int);

void __cdecl d3_SafeReleaseSceneResource(int resource)
{
	if (resource == 0) {
		return;
	}
	d3_ReleaseTexture(resource);
}
