

void __cdecl d3_ReloadFloorTextureSlots(int);

void __cdecl d3_ReloadFloorTextures(int floor)
{
	if (floor == 0) {
		return;
	}
	d3_ReloadFloorTextureSlots(floor);
}
