

extern int g_6b71a0;
extern int msx_TrackDriver;
extern int msx_AmbientDriver;
void __cdecl msx_CloseAllStreams(void);
int __cdecl fcn_0042a2d0(int);

void __cdecl msx_ShutdownDrivers(void)
{
	g_6b71a0 = 1;
	if (msx_TrackDriver != 0) {
		msx_CloseAllStreams();
		fcn_0042a2d0(msx_TrackDriver);
		msx_TrackDriver = 0;
	}
	if (msx_AmbientDriver != 0) {
		fcn_0042a2d0(msx_AmbientDriver);
		msx_AmbientDriver = 0;
	}
}
