extern char sb_WaveDriver[];

// fcn_00427370 — if(*0x6b7d7c) fcn_0042b780(*0x6b7d7c, arg).

int __cdecl fcn_0042b780(int, int);

/* ADDRESS: GOLDDE 0x00420660 */
void __cdecl sb_SetMasterVolume(int volume)
{
	int driver_handle;
	driver_handle = *(int*) &sb_WaveDriver;
	if (driver_handle != 0) {
		fcn_0042b780(driver_handle, volume);
	}
}
