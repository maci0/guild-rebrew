
/* Calls fcn_0043f270, then zeroes g_00633748. */
extern int g_00633748; /* 0x00633748 */
void __cdecl d3_ShutdownFloorTileCache(void);

void __cdecl d3_ShutdownFloorTiles(void)
{
    d3_ShutdownFloorTileCache();
    g_00633748 = 0;
}
