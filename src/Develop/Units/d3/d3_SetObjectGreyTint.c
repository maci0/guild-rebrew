

void __cdecl d3_SetObjectColorRgb(int, int, int, int);

void __cdecl d3_SetObjectGreyTint(int a1, int enabled)
{
	if (enabled != 0) {
		d3_SetObjectColorRgb(a1, 0x80, 0x80, 0x80);
	} else {
		d3_SetObjectColorRgb(a1, 0, 0, 0);
	}
}
