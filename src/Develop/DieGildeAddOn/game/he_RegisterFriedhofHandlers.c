


int __cdecl he_RegisterHandler(int, void (__cdecl*)(char*), void (__cdecl*)(char*));
int __cdecl he_RegisterActionMeta(int, char*, int, int, int);
void __cdecl he_StartAction0x88(void);
void __cdecl he_RunHeimsuchung(void);
void __cdecl he_StartHauchDesVerfalls(void);
void __cdecl he_RunHauchDesVerfalls(void);
void __cdecl he_StartRohstoffsuchen(void);
void __cdecl he_RunRohstoffsuchen(void);
void __cdecl he_StartGrabpflege(void);
void __cdecl he_RunGrabpflege(void);
void __cdecl he_StartDeathPact(void);
void __cdecl he_RunDeathPact(void);
void __cdecl fcn_00579320(void);
void __cdecl he_HandleDeathPactPrompt(void);
void __cdecl he_StartAction0x8e(void);
void __cdecl he_RunDeathPactCollection(void);
void __cdecl he_StartUpgraden(void);
void __cdecl he_RunUpgraden(void);
void __cdecl he_StartAction0x90(void);
void __cdecl he_RunAction0x90(void);
void __cdecl he_StartNecromancerFog(void);
void __cdecl he_UpdateNecromancerFog(void);
void __cdecl he_StartAction0x93(void);
void __cdecl he_RunAction0x93(void);
void __cdecl he_StartFriedhofStealAction(char*);
void __cdecl he_RunFriedhofStealAction(char*);
void __cdecl he_StartMeisterpruefung(void);
void __cdecl he_RunMeisterpruefung(void);

int __cdecl he_RegisterFriedhofHandlers(void)
{
	if (he_RegisterHandler(0x88, he_StartAction0x88, he_RunHeimsuchung) || he_RegisterHandler(0x89, he_StartHauchDesVerfalls, he_RunHauchDesVerfalls)
	    || he_RegisterHandler(0x8c, he_StartRohstoffsuchen, he_RunRohstoffsuchen) || he_RegisterHandler(0x8d, he_StartGrabpflege, he_RunGrabpflege)
	    || he_RegisterHandler(0x8a, he_StartDeathPact, he_RunDeathPact) || he_RegisterHandler(0x8b, fcn_00579320, he_HandleDeathPactPrompt)
	    || he_RegisterHandler(0x8d, he_StartGrabpflege, he_RunGrabpflege) || he_RegisterHandler(0x8e, he_StartAction0x8e, he_RunDeathPactCollection)
	    || he_RegisterHandler(0x8f, he_StartUpgraden, he_RunUpgraden) || he_RegisterHandler(0x90, he_StartAction0x90, he_RunAction0x90)
	    || he_RegisterHandler(0x91, he_StartNecromancerFog, he_UpdateNecromancerFog) || he_RegisterHandler(0x93, he_StartAction0x93, he_RunAction0x93)
	    || he_RegisterHandler(0x94, he_StartFriedhofStealAction, he_RunFriedhofStealAction) || he_RegisterHandler(0x92, he_StartMeisterpruefung, he_RunMeisterpruefung)) {
		return 1;
	}
	he_RegisterActionMeta(0x8d, "grabpflege", 1, 0x513, -1);
	he_RegisterActionMeta(0x8c, "Rohstoffsuchen", 1, 0x500, 0xac);
	he_RegisterActionMeta(0x8f, "Upgraden", 0, 0x512, -1);
	he_RegisterActionMeta(0x8a, 0, 0, 0x514, -1);
	he_RegisterActionMeta(0x88, 0, 0, 0x511, -1);
	return 0;
}
