extern char g_6b7d7c[];

// fcn_00427370 — if(*0x6b7d7c) fcn_0042b780(*0x6b7d7c, arg).

int __cdecl fcn_0042b780(int, int);

void __cdecl sb_SetMasterVolume(int volume)
{
	int driver_handle;
	driver_handle = *(int*) &g_6b7d7c;
	if (driver_handle != 0) {
		fcn_0042b780(driver_handle, volume);
	}
}
