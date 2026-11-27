int __cdecl shp_Convert24To16(char*);
int __cdecl shp_Convert8To16(char*);

#ifdef REBREW_GOLD
#define fcn_00479330 fcn_0047c0d0
#define fcn_00479110 fcn_0047beb0
#endif


/* ADDRESS: GOLDTL 0x00479620 */
int __cdecl shp_ConvertTo16(char* p, int mode)
{
	if (p[0xc] == 2 && mode == 1)
		return shp_Convert24To16(p);
	if (p[0xc] == 0 && mode == 1)
		return shp_Convert8To16(p);
	return 0;
}
