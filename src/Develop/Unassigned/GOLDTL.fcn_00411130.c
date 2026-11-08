extern int g_677188;
extern int g_67718c;
extern int g_677190;
extern int g_677194;
extern int g_677198;
extern int g_67719c;
extern int g_6771a0;
extern int g_6771a4;

int __cdecl LoadSampleBank();
int __cdecl KillSampleBank();
int __cdecl PlaySampleHandle();
int __cdecl PlaySample();
int __cdecl PlaySample3D();
int __cdecl StopSample();
int __cdecl GetSampleBankHandle();
int __cdecl GetSampleHandle();
int __cdecl SpeechQueued();
int __cdecl WaitForSample();
void __cdecl evt_ImportCommand(const char*, void*, ...);
void __cdecl fcn_00425d90(const char*, void*, ...);


/* Registers the sound script commands and constants. */
/* ADDRESS: GOLDTL 0x00411130 */
void __cdecl fcn_00411130(void)
{
	evt_ImportCommand("LoadSampleBank", LoadSampleBank, 1, 1, 6);
	evt_ImportCommand("KillSampleBank", KillSampleBank, 1, 1, 1);
	evt_ImportCommand("PlaySampleHandle", PlaySampleHandle, 1, 2, 1, 6);
	evt_ImportCommand("PlaySample", PlaySample, 1, 2, 6, 1);
	evt_ImportCommand("PlaySample3D", PlaySample3D, 1, 4, 1, 1, 6, 1);
	evt_ImportCommand("StopSample", StopSample, 1, 1, 1);
	evt_ImportCommand("GetSampleBankHandle", GetSampleBankHandle, 1, 1, 6);
	evt_ImportCommand("GetSampleHandle", GetSampleHandle, 1, 2, 1, 6);
	evt_ImportCommand("SpeechQueued", SpeechQueued, 1, 5, 1, 1, 6, 1, 1);
	evt_ImportCommand("WaitForSample", WaitForSample, 5, 1, 1);
	fcn_00425d90("SND_W2", &g_677188, 1);
	fcn_00425d90("SND_W1", &g_67718c, 1);
	fcn_00425d90("SND_M1", &g_677198, 1);
	fcn_00425d90("SND_M2", &g_677194, 1);
	fcn_00425d90("SND_M3", &g_677190, 1);
	fcn_00425d90("SND_HS", &g_67719c, 1);
	fcn_00425d90("SND_NONE", &g_6771a0, 1);
	fcn_00425d90("SND_VAR", &g_6771a4, 1);
}
