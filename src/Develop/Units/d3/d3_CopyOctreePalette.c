extern unsigned char d3_OctreePalette[3][0x100];
extern unsigned char d3_OctreePalette[3][0x100];
extern char d3_OctreePaletteGreen[];
extern char d3_OctreePaletteGreen[];
extern char d3_OctreePaletteBlue[];
extern char d3_OctreePaletteBlue[];

/* ADDRESS: GOLD 0x00420780 */
/* ADDRESS: GOLDTL 0x0041bd80 */
void __cdecl d3_CopyOctreePalette(char* out_palette)
{
	int i;

	for (i = 0; i < 0x100; i++) {
		out_palette[i] = *(char*) ((char*) d3_OctreePalette + i);
		out_palette[i + 0x100] = *(char*) (d3_OctreePaletteGreen + i);
		out_palette[i + 0x200] = *(char*) (d3_OctreePaletteBlue + i);
	}
}
#if defined(REBREW_SERVER) || defined(REBREW_GOLD)
unsigned char _dpad_6b6008[256];
unsigned char _dpad_6b6108[256];
#endif
