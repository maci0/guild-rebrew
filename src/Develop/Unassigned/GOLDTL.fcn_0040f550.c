

void __cdecl d3_BlendSceneLightingPreset(int, float, float, int);

int __cdecl SetLightSet(int* a1)
{
	d3_BlendSceneLightingPreset(a1[0], 1.0f, 1.0f, 0);
	return 1;
}
