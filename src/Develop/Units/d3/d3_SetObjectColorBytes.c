

void __cdecl d3_SetObjectColorRgb(char*, char, char, char);

/* ADDRESS: GOLDDE 0x00413220 */
char __cdecl d3_SetObjectColorBytes(char* object, char* rgb)
{
	d3_SetObjectColorRgb(object, rgb[0], rgb[1], rgb[2]);
	return 1;
}
