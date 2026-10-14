extern int g_677188;
extern int g_67718c;
extern int g_677190;
extern int g_677194;
extern int g_677198;
extern int g_67719c;
extern int g_6771a0;
extern int g_6771a4;

int __cdecl fcn_00410ed0();
int __cdecl fcn_00410ef0();
int __cdecl fcn_00410f10();
int __cdecl fcn_00410f50();
int __cdecl fcn_00410fc0();
int __cdecl fcn_00411040();
int __cdecl fcn_00411060();
int __cdecl fcn_00411070();
int __cdecl fcn_00411090();
int __cdecl fcn_004110e0();
void __cdecl fcn_00429ed0(const char*, void*, ...);
void __cdecl fcn_00425d90(const char*, void*, ...);

/* ADDRESS: GOLDTL 0x00411130 */

/* Registers the sound script commands and constants. */
void __cdecl fcn_00411130(void)
{
	fcn_00429ed0("LoadSampleBank", fcn_00410ed0, 1, 1, 6);
	fcn_00429ed0("KillSampleBank", fcn_00410ef0, 1, 1, 1);
	fcn_00429ed0("PlaySampleHandle", fcn_00410f10, 1, 2, 1, 6);
	fcn_00429ed0("PlaySample", fcn_00410f50, 1, 2, 6, 1);
	fcn_00429ed0("PlaySample3D", fcn_00410fc0, 1, 4, 1, 1, 6, 1);
	fcn_00429ed0("StopSample", fcn_00411040, 1, 1, 1);
	fcn_00429ed0("GetSampleBankHandle", fcn_00411060, 1, 1, 6);
	fcn_00429ed0("GetSampleHandle", fcn_00411070, 1, 2, 1, 6);
	fcn_00429ed0("SpeechQueued", fcn_00411090, 1, 5, 1, 1, 6, 1, 1);
	fcn_00429ed0("WaitForSample", fcn_004110e0, 5, 1, 1);
	fcn_00425d90("SND_W2", &g_677188, 1);
	fcn_00425d90("SND_W1", &g_67718c, 1);
	fcn_00425d90("SND_M1", &g_677198, 1);
	fcn_00425d90("SND_M2", &g_677194, 1);
	fcn_00425d90("SND_M3", &g_677190, 1);
	fcn_00425d90("SND_HS", &g_67719c, 1);
	fcn_00425d90("SND_NONE", &g_6771a0, 1);
	fcn_00425d90("SND_VAR", &g_6771a4, 1);
}
