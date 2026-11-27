

void __cdecl d3_ReleaseTexture(int);
int __cdecl d3_LoadOrReuseTexture(int, int, int, int);
void __cdecl fcn_0045ce90(int);

void __cdecl d3_SetSkyLayerTexture(void* a1, int assetName)
{
	int asset;

	d3_ReleaseTexture(*(int*) ((char*) a1 + 0x1c));
	asset = d3_LoadOrReuseTexture(assetName, *(int*) ((char*) a1 + 0x24), 0, 0);
	*(int*) ((char*) a1 + 0x1c) = asset;
	if (asset != 0) {
		fcn_0045ce90(asset);
	}
}
