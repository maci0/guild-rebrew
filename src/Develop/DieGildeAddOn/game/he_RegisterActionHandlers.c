void __cdecl he_StartUpgradeDummy();
void __cdecl he_RunUpgradeDummy();
void __cdecl he_StartHireWorkerJob();
void __cdecl he_RunHireWorkerJob();
void __cdecl he_InitAction0x07Kugel();
void __cdecl he_RunHireMasterJob();
void __cdecl he_AllocTransport();
void __cdecl he_RunTransport();
void __cdecl he_StartReparatur();
void __cdecl he_RunObjektReparatur();
void __cdecl he_StartEventMessagebox();
void __cdecl he_RunEventMessagebox();
void __cdecl he_StartBuildingExpansion();
void __cdecl he_RunBuildingExpansion();
void __cdecl he_StartLagerErweitern();
void __cdecl he_RunLagerErweitern();
void __cdecl he_StartKraeuter();
void __cdecl he_RunKraeuter();
void __cdecl he_StartGetier();
void __cdecl he_RunGetier();
void __cdecl he_InitTrainieren();
void __cdecl he_RunTrainierenSkill();
void __cdecl he_InitAction0x17();
void __cdecl he_RunAction0x17();
void __cdecl he_ScheduleSabotage();
void __cdecl he_RunSabotage();
void __cdecl he_InitSpionage();
void __cdecl he_RunSpionage();
void __cdecl he_AllocPruegelAction();
void __cdecl he_RunPruegel();
void __cdecl he_StartGebVerkaufen();
void __cdecl he_RunBuildingOfferAction();
void __cdecl he_StartGebaeudeReparieren();
void __cdecl he_RunGebaeudeReparieren();
void __cdecl he_StartAction0x1e();
void __cdecl he_RunSetGebUpgrade();
void __cdecl he_StartGebAbreissen();
void __cdecl he_UpdateGebAbreissen();
void __cdecl he_StartGebaeudeKaufangebot();
void __cdecl he_RunGebaeudeKaufangebot();
void __cdecl he_StartSellGebaeudeObjekt();
void __cdecl he_RunSellGebaeudeObjekt();
void __cdecl he_AllocKredit();
void __cdecl he_RunKredit();
void __cdecl he_ResetActionEndTime();
void __cdecl he_RunMeisterpruefungFinish();
void __cdecl he_InitMeisterpruefungNotice();
void __cdecl he_RunMeisterpruefungNotice();
void __cdecl he_InitMeisterpruefungPassed();
void __cdecl he_RunMeisterpruefungPassed();
void __cdecl he_StartAction0x27();
void __cdecl he_RunAction0x27();
void __cdecl he_StartErnten();
void __cdecl he_UpdateErnten();
void __cdecl he_InitEntlassen();
void __cdecl he_HandleEntlassen();
void __cdecl he_StartBefoerdern();
void __cdecl he_RunBefoerdern();
void __cdecl he_RunWorkerQuitAction();
void __cdecl he_StartWorkerStealAction();
void __cdecl he_RunWorkerStealAction();
void __cdecl he_InitAction0x38();
void __cdecl he_RunWorkerBonus();
void __cdecl he_StartCaptiveReleaseOffer();
void __cdecl he_RunCaptiveReleaseOffer();
void __cdecl he_RunDailyRoutine();
void __cdecl he_StartMarktSupervisor();
void __cdecl he_RunMarktSupervisor();
void __cdecl he_StartEntfuehren();
void __cdecl he_RunEntfuehren();
void __cdecl he_InitAction0x3d();
void __cdecl he_RunEntfuehrungHostage();
void __cdecl he_StartLoesegeld();
void __cdecl gm_HandleLoesegeld();
void __cdecl he_StartEinbruch();
void __cdecl he_RunEinbruch();
void __cdecl he_InitGebSpionage();
void __cdecl he_RunGebSpionage();
void __cdecl he_StartUeberfall();
void __cdecl he_RunUeberfall();
void __cdecl he_InitAngriff();
void __cdecl he_RunAngriff();
void __cdecl he_StartFireEvent();
void __cdecl he_RunFireEvent();
void __cdecl he_StartHausbrand();
void __cdecl he_RunHausbrand();
void __cdecl he_StartWeatherStorm();
void __cdecl he_RunWeatherStorm();
void __cdecl he_StartHeilen();
void __cdecl he_RunHeilen();
void __cdecl he_StartInitBetrieb();
void __cdecl he_RunInitBetrieb();
void __cdecl he_AllocDiePlayer();
void __cdecl he_RunDeathAnimation();
void __cdecl he_AllocKillPlayer();
void __cdecl he_RunCharacterDeath();
void __cdecl he_RunNightWatchmanAnnouncements();
void __cdecl he_InitRaubzug();
void __cdecl he_RunRaubzug();
void __cdecl he_InitAction0x7c();
void __cdecl he_RunEntityFatigue();
void __cdecl he_OpenProfessionHelpEvents();
void __cdecl he_RunEvent0x83TextQueue();
void __cdecl he_InitEvent0x84Rumors();
void __cdecl he_RunEvent0x84Rumors();
void __cdecl he_StartEvent0x85();
void __cdecl he_RunEvent0x85();
void __cdecl he_StartTradeCartRoutes();
extern char g_77e020[];
extern char s_6a6510[];
extern char s_6a6ed8[];
extern char s_6a6ed0[];

unsigned int __cdecl he_RegisterHandler(int, unsigned int, unsigned int);
unsigned int __cdecl he_RegisterActionMeta(unsigned int, char *, unsigned int, unsigned int, unsigned int);
void __cdecl gm_GenerateShuffledIndices(unsigned int, unsigned int);

/* ADDRESS: GOLDTL 0x00570960 */
/* ADDRESS: GOLDDE 0x00556920 */
unsigned int __cdecl he_RegisterActionHandlers(void)
{
	if (he_RegisterHandler(2, (int) he_StartUpgradeDummy, (int) he_RunUpgradeDummy)) {
		return 1;
	}
	if (he_RegisterHandler(6, (int) he_StartHireWorkerJob, (int) he_RunHireWorkerJob)) {
		return 1;
	}
	if (he_RegisterHandler(7, (int) he_InitAction0x07Kugel, (int) he_RunHireMasterJob)) {
		return 1;
	}
	if (he_RegisterHandler(0xf, (int) he_AllocTransport, (int) he_RunTransport)) {
		return 1;
	}
	if (he_RegisterHandler(0x10, (int) he_StartReparatur, (int) he_RunObjektReparatur)) {
		return 1;
	}
	if (he_RegisterHandler(0x11, (int) he_StartEventMessagebox, (int) he_RunEventMessagebox)) {
		return 1;
	}
	if (he_RegisterHandler(0x12, (int) he_StartBuildingExpansion, (int) he_RunBuildingExpansion)) {
		return 1;
	}
	if (he_RegisterHandler(0x13, (int) he_StartLagerErweitern, (int) he_RunLagerErweitern)) {
		return 1;
	}
	if (he_RegisterHandler(0x14, (int) he_StartKraeuter, (int) he_RunKraeuter)) {
		return 1;
	}
	he_RegisterActionMeta(0x14, 0, 1, 0x500, 0xae);
	if (he_RegisterHandler(0x15, (int) he_StartGetier, (int) he_RunGetier)) {
		return 1;
	}
	he_RegisterActionMeta(0x15, s_6a6510, 1, 0x500, 0xae);
	if (he_RegisterHandler(0x16, (int) he_InitTrainieren, (int) he_RunTrainierenSkill)) {
		return 1;
	}
	he_RegisterActionMeta(0x16, s_6a6ed8, 0, 0x509, -1);
	if (he_RegisterHandler(0x17, (int) he_InitAction0x17, (int) he_RunAction0x17)) {
		return 1;
	}
	if (he_RegisterHandler(0x19, (int) he_ScheduleSabotage, (int) he_RunSabotage)) {
		return 1;
	}
	if (he_RegisterHandler(0x18, (int) he_InitSpionage, (int) he_RunSpionage)) {
		return 1;
	}
	if (he_RegisterHandler(0x1a, (int) he_AllocPruegelAction, (int) he_RunPruegel)) {
		return 1;
	}
	if (he_RegisterHandler(0x1b, (int) he_StartGebVerkaufen, (int) he_RunBuildingOfferAction)) {
		return 1;
	}
	if (he_RegisterHandler(0x1c, (int) he_StartGebaeudeReparieren, (int) he_RunGebaeudeReparieren)) {
		return 1;
	}
	if (he_RegisterHandler(0x1e, (int) he_StartAction0x1e, (int) he_RunSetGebUpgrade)) {
		return 1;
	}
	if (he_RegisterHandler(0x20, (int) he_StartGebAbreissen, (int) he_UpdateGebAbreissen)) {
		return 1;
	}
	if (he_RegisterHandler(0x21, (int) he_StartGebaeudeKaufangebot, (int) he_RunGebaeudeKaufangebot)) {
		return 1;
	}
	if (he_RegisterHandler(0x1f, (int) he_StartSellGebaeudeObjekt, (int) he_RunSellGebaeudeObjekt)) {
		return 1;
	}
	if (he_RegisterHandler(0x23, (int) he_AllocKredit, (int) he_RunKredit)) {
		return 1;
	}
	if (he_RegisterHandler(0x24, (int) he_ResetActionEndTime, (int) he_RunMeisterpruefungFinish)) {
		return 1;
	}
	if (he_RegisterHandler(0x25, (int) he_InitMeisterpruefungNotice, (int) he_RunMeisterpruefungNotice)) {
		return 1;
	}
	if (he_RegisterHandler(0x26, (int) he_InitMeisterpruefungPassed, (int) he_RunMeisterpruefungPassed)) {
		return 1;
	}
	if (he_RegisterHandler(0x27, (int) he_StartAction0x27, (int) he_RunAction0x27)) {
		return 1;
	}
	if (he_RegisterHandler(0x28, (int) he_StartErnten, (int) he_UpdateErnten)) {
		return 1;
	}
	he_RegisterActionMeta(0x28, 0, 1, 0x4ff, 0xbc);
	if (he_RegisterHandler(0x31, (int) he_InitEntlassen, (int) he_HandleEntlassen)) {
		return 1;
	}
	if (he_RegisterHandler(0x32, (int) he_StartBefoerdern, (int) he_RunBefoerdern)) {
		return 1;
	}
	if (he_RegisterHandler(0x33, 0x5666b0, (int) he_RunWorkerQuitAction)) {
		return 1;
	}
	if (he_RegisterHandler(0x34, (int) he_StartWorkerStealAction, (int) he_RunWorkerStealAction)) {
		return 1;
	}
	if (he_RegisterHandler(0x38, (int) he_InitAction0x38, (int) he_RunWorkerBonus)) {
		return 1;
	}
	if (he_RegisterHandler(0x39, (int) he_StartCaptiveReleaseOffer, (int) he_RunCaptiveReleaseOffer)) {
		return 1;
	}
	if (he_RegisterHandler(0x3a, 0x566fa0, (int) he_RunDailyRoutine)) {
		return 1;
	}
	if (he_RegisterHandler(0x3b, (int) he_StartMarktSupervisor, (int) he_RunMarktSupervisor)) {
		return 1;
	}
	if (he_RegisterHandler(0x3c, (int) he_StartEntfuehren, (int) he_RunEntfuehren)) {
		return 1;
	}
	he_RegisterActionMeta(0x3c, 0, 0, 0x504, -1);
	if (he_RegisterHandler(0x3d, (int) he_InitAction0x3d, (int) he_RunEntfuehrungHostage)) {
		return 1;
	}
	if (he_RegisterHandler(0x3e, (int) he_StartLoesegeld, (int) gm_HandleLoesegeld)) {
		return 1;
	}
	if (he_RegisterHandler(0x3f, (int) he_StartEinbruch, (int) he_RunEinbruch)) {
		return 1;
	}
	he_RegisterActionMeta(0x3f, 0, 0, 0x50a, -1);
	if (he_RegisterHandler(0x40, (int) he_InitGebSpionage, (int) he_RunGebSpionage)) {
		return 1;
	}
	he_RegisterActionMeta(0x40, 0, 0, 0x503, -1);
	if (he_RegisterHandler(0x48, (int) he_StartUeberfall, (int) he_RunUeberfall)) {
		return 1;
	}
	he_RegisterActionMeta(0x48, 0, 0, 0x502, -1);
	if (he_RegisterHandler(0x49, (int) he_InitAngriff, (int) he_RunAngriff)) {
		return 1;
	}
	he_RegisterActionMeta(0x49, 0, 0, 0x50a, -1);
	if (he_RegisterHandler(0x4e, (int) he_StartFireEvent, (int) he_RunFireEvent)) {
		return 1;
	}
	if (he_RegisterHandler(0x4f, (int) he_StartHausbrand, (int) he_RunHausbrand)) {
		return 1;
	}
	if (he_RegisterHandler(0x50, (int) he_StartWeatherStorm, (int) he_RunWeatherStorm)) {
		return 1;
	}
	if (he_RegisterHandler(0x6c, (int) he_StartHeilen, (int) he_RunHeilen)) {
		return 1;
	}
	he_RegisterActionMeta(0x6c, s_6a6ed0, 0, 0x505, -1);
	if (he_RegisterHandler(0x6e, (int) he_StartInitBetrieb, (int) he_RunInitBetrieb)) {
		return 1;
	}
	if (he_RegisterHandler(0x71, (int) he_AllocDiePlayer, (int) he_RunDeathAnimation)) {
		return 1;
	}
	if (he_RegisterHandler(0x72, (int) he_AllocKillPlayer, (int) he_RunCharacterDeath)) {
		return 1;
	}
	if (he_RegisterHandler(0x73, 0x56e8e0, (int) he_RunNightWatchmanAnnouncements)) {
		return 1;
	}
	if (he_RegisterHandler(0x75, (int) he_InitRaubzug, (int) he_RunRaubzug)) {
		return 1;
	}
	he_RegisterActionMeta(0x75, 0, 0, 0x502, -1);
	if (he_RegisterHandler(0x7c, (int) he_InitAction0x7c, (int) he_RunEntityFatigue)) {
		return 1;
	}
	if (he_RegisterHandler(0x83, (int) he_OpenProfessionHelpEvents, (int) he_RunEvent0x83TextQueue)) {
		return 1;
	}
	if (he_RegisterHandler(0x84, (int) he_InitEvent0x84Rumors, (int) he_RunEvent0x84Rumors)) {
		return 1;
	}
	if (he_RegisterHandler(0x85, (int) he_StartEvent0x85, (int) he_RunEvent0x85)) {
		return 1;
	}
	if (he_RegisterHandler(0xa6, (int) he_StartTradeCartRoutes, 0x570870)) {
		return 1;
	}
	gm_GenerateShuffledIndices(0x1a, (int) &g_77e020);
	return 0;
}
