int __cdecl evt_RegisterScriptCommand(char* name, int a1, int a2, int n, ...);

/* 62 straight-line fcn_0042b5b0 calls: name string, handler address, then the
 * argument list. DATA TODO: the name strings
 * (0x5f2cc0..0x5f30f8) and handlers (0x40d680..0x40f8f0) are raw addresses. */
/* ADDRESS: GOLD 0x0040f960 */
void __cdecl evt_RegisterSceneCommands(void)
{
	evt_RegisterScriptCommand((char*) 0x005f30f8, 0x0040d8d0, 1, 4, 7, 7, 7, 6);
	evt_RegisterScriptCommand((char*) 0x005f30e4, 0x0040d940, 1, 2, 6, 1);
	evt_RegisterScriptCommand((char*) 0x005f30c8, 0x0040d9a0, 1, 2, 6, 1);
	evt_RegisterScriptCommand((char*) 0x005f30bc, 0x0040da10, 5, 1, 1);
	evt_RegisterScriptCommand((char*) 0x005f30b4, 0x0040da50, 5, 4, 1, 7, 7, 7);
	evt_RegisterScriptCommand((char*) 0x005f30a8, 0x0040dab0, 5, 4, 1, 7, 7, 7);
	evt_RegisterScriptCommand((char*) 0x005f309c, 0x0040db30, 5, 5, 1, 1, 1, 1, 1);
	evt_RegisterScriptCommand((char*) 0x005f308c, 0x0040dbb0, 5, 5, 1, 1, 1, 1, 1);
	evt_RegisterScriptCommand((char*) 0x005f3078, 0x0040dc30, 5, 5, 1, 1, 1, 1, 1);
	evt_RegisterScriptCommand((char*) 0x005f3060, 0x0040dcb0, 5, 5, 1, 1, 1, 1, 1);
	evt_RegisterScriptCommand((char*) 0x005f3054, 0x0040dd50, 5, 3, 1, 1, 1);
	evt_RegisterScriptCommand((char*) 0x005f3048, 0x0040dd90, 5, 1, 1);
	evt_RegisterScriptCommand((char*) 0x005f3038, 0x0040ddb0, 1, 2, 1, 6);
	evt_RegisterScriptCommand((char*) 0x005f302c, 0x0040ddf0, 5, 1, 6);
	evt_RegisterScriptCommand((char*) 0x005f3020, 0x0040de30, 1, 3, 1, 6, 1);
	evt_RegisterScriptCommand((char*) 0x005f3014, 0x0040dfc0, 1, 2, 1, 6);
	evt_RegisterScriptCommand((char*) 0x005f3000, 0x0040e0e0, 1, 3, 1, 6, 1);
	evt_RegisterScriptCommand((char*) 0x005f2fe8, 0x0040e430, 1, 4, 6, 6, 1, 1);
	evt_RegisterScriptCommand((char*) 0x005f2fd4, 0x0040e4f0, 5, 1, 6);
	evt_RegisterScriptCommand((char*) 0x005f2fc4, 0x0040d680, 1, 1, 6);
	evt_RegisterScriptCommand((char*) 0x005f2fb0, 0x0040d730, 1, 1, 6);
	evt_RegisterScriptCommand((char*) 0x005f2f98, 0x0040d7b0, 1, 2, 1, 6);
	evt_RegisterScriptCommand((char*) 0x005f2f84, 0x0040d860, 1, 2, 1, 6);
	evt_RegisterScriptCommand((char*) 0x005f2f74, 0x0040e620, 5, 1, 1);
	evt_RegisterScriptCommand((char*) 0x005f2f68, 0x0040e640, 5, 1, 1);
	evt_RegisterScriptCommand((char*) 0x005f2f5c, 0x0040e670, 5, 3, 1, 1, 1);
	evt_RegisterScriptCommand((char*) 0x005f2f4c, 0x0040e6f0, 5, 3, 1, 6, 6);
	evt_RegisterScriptCommand((char*) 0x005f2f3c, 0x0040ea00, 5, 2, 1, 6);
	evt_RegisterScriptCommand((char*) 0x005f2f24, 0x0040e750, 5, 7, 1, 6, 6, 6, 6, 6, 6);
	evt_RegisterScriptCommand((char*) 0x005f2f14, 0x0040e810, 5, 7, 1, 6, 6, 6, 6, 6, 6);
	evt_RegisterScriptCommand((char*) 0x005f2f04, 0x0040e8b0, 5, 7, 1, 1, 6, 6, 6, 6, 6);
	evt_RegisterScriptCommand((char*) 0x005f2ef8, 0x0040ea90, 1, 1, 1);
	evt_RegisterScriptCommand((char*) 0x005f2eec, 0x0040eaa0, 1, 1, 1);
	evt_RegisterScriptCommand((char*) 0x005f2edc, 0x0040ec70, 5, 1, 1);
	evt_RegisterScriptCommand((char*) 0x005f2ecc, 0x0040edc0, 5, 1, 1);
	evt_RegisterScriptCommand((char*) 0x005f2eb8, 0x0040ee10, 5, 1, 6);
	evt_RegisterScriptCommand((char*) 0x005f2ea4, 0x0040eea0, 5, 0);
	evt_RegisterScriptCommand((char*) 0x005f2e94, 0x0040eec0, 1, 2, 1, 6);
	evt_RegisterScriptCommand((char*) 0x005f2e88, 0x0040eef0, 1, 2, 1, 1);
	evt_RegisterScriptCommand((char*) 0x005f2e78, 0x0040ef40, 1, 2, 1, 1);
	evt_RegisterScriptCommand((char*) 0x005f2e68, 0x0040ef90, 1, 7, 1, 1, 1, 1, 6, 1, 1);
	evt_RegisterScriptCommand((char*) 0x005f2e5c, 0x0040f0c0, 1, 1, 1);
	evt_RegisterScriptCommand((char*) 0x005f2e48, 0x0040f110, 1, 6, 1, 1, 1, 1, 1, 1);
	evt_RegisterScriptCommand((char*) 0x005f2e30, 0x0040f1b0, 1, 6, 1, 1, 1, 1, 1, 1);
	evt_RegisterScriptCommand((char*) 0x005f2e1c, 0x0040f250, 1, 4, 1, 1, 1, 1);
	evt_RegisterScriptCommand((char*) 0x005f2e0c, 0x0040f2c0, 1, 4, 1, 1, 1, 1);
	evt_RegisterScriptCommand((char*) 0x005f2df8, 0x0040f320, 1, 4, 1, 1, 1, 1);
	evt_RegisterScriptCommand((char*) 0x005f2de0, 0x0040f390, 1, 4, 1, 1, 1, 1);
	evt_RegisterScriptCommand((char*) 0x005f2dc8, 0x0040f400, 1, 4, 1, 1, 1, 1);
	evt_RegisterScriptCommand((char*) 0x005f2db8, 0x0040f470, 1, 5, 1, 1, 1, 1, 1);
	evt_RegisterScriptCommand((char*) 0x005f2da0, 0x0040f4f0, 1, 5, 1, 1, 1, 1, 1);
	evt_RegisterScriptCommand((char*) 0x005f2d90, 0x0040f560, 1, 5, 1, 1, 1, 1, 1);
	evt_RegisterScriptCommand((char*) 0x005f2d80, 0x0040f5d0, 1, 7, 1, 1, 1, 1, 1, 1, 1);
	evt_RegisterScriptCommand((char*) 0x005f2d6c, 0x0040f690, 1, 2, 1, 1);
	evt_RegisterScriptCommand((char*) 0x005f2d54, 0x0040f6f0, 1, 2, 1, 1);
	evt_RegisterScriptCommand((char*) 0x005f2d3c, 0x0040f750, 1, 2, 1, 1);
	evt_RegisterScriptCommand((char*) 0x005f2d28, 0x0040f7a0, 1, 2, 1, 1);
	evt_RegisterScriptCommand((char*) 0x005f2d10, 0x0040f800, 1, 2, 1, 1);
	evt_RegisterScriptCommand((char*) 0x005f2cf8, 0x0040f850, 1, 2, 1, 1);
	evt_RegisterScriptCommand((char*) 0x005f2ce8, 0x0040f8a0, 1, 1, 1);
	evt_RegisterScriptCommand((char*) 0x005f2cd8, 0x0040f8f0, 1, 4, 1, 1, 1, 1);
	evt_RegisterScriptCommand((char*) 0x005f2cc0, 0x0040e5a0, 1, 2, 6, 1);
}
