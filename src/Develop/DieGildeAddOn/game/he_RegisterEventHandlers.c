int __cdecl he_RegisterHandler(int, void*, void*);
int __cdecl he_RegisterActionMeta(int, char*, int, int, int);
void __cdecl fcn_00549b50(void);
void __cdecl fcn_00549b80(void);
void __cdecl he_StartElectionCampaign(void);
void __cdecl he_RunElectionCampaign(void);
void __cdecl he_AllocPredigt(void);
void __cdecl he_RunPredigt(void);
void __cdecl he_StartCourtTrial(void);
void __cdecl he_StartCourtAction(void);
void __cdecl he_StartAction0x2e(void);
void __cdecl he_HandleAction0x2e(void);
void __cdecl he_StartSkillDuelEvent(void);
void __cdecl he_RunSkillDuelEvent(void);
void __cdecl he_StartFreeActionStub(void);
void __cdecl he_StartFest(void);
void __cdecl he_UpdateFest(void);
void __cdecl he_InitInvitation(void);
void __cdecl he_RunInvitation(void);
void __cdecl he_RunAction53(void);
void __cdecl he_StartCourtship(void);
void __cdecl he_RunCourtship(void);
void __cdecl he_StartRandomEvent(void);
void __cdecl he_InitStreife(void);
void __cdecl he_UpdateRobberyAction(void);
void __cdecl he_StartRazzia(void);
void __cdecl he_RunRazzia(void);
void __cdecl he_StartDuellChallenge(void);
void __cdecl he_RunDuellChallenge(void);
void __cdecl he_InitDuellIntro(void);
void __cdecl he_RunDuellIntro(void);
void __cdecl he_RunDuellCutscene(void);
void __cdecl he_AllocRndGeselle(void);
void __cdecl he_RunHireJourneymanAction(void);
void __cdecl he_StartAction0x4b(void);
void __cdecl he_HandleAction0x4b(void);
void __cdecl he_InitAction0x52(void);
void __cdecl he_RunAction0x52(void);
void __cdecl he_InitEvent053(void);
void __cdecl he_RunEvent053(void);
void __cdecl he_RunMeisterpruefungPrompt(void);
void __cdecl he_InitMeisterpruefDialog(void);
void __cdecl he_RunMeisterpruefungExam(void);
void __cdecl he_InitAction0x56(void);
void __cdecl he_RunGambleBet(void);
void __cdecl he_AllocSellObjekt(void);
void __cdecl he_AllocBuildingDamageEvent(void);
void __cdecl he_RunBuildingDamageEvent(void);
void __cdecl he_ScheduleDelayedAction(void);
void __cdecl he_RunAction0x5a(void);
void __cdecl he_StartPeriodicStipend(void);
void __cdecl he_RunPeriodicStipend(void);
void __cdecl he_RunPeriodicApDrain(void);
void __cdecl he_InitAction0x5d(void);
void __cdecl he_RunChildBirth(void);
void __cdecl he_AllocLevelTraining(void);
void __cdecl he_RunLevelTraining(void);
void __cdecl he_AllocApTraitAction(void);
void __cdecl he_RunApTraitAction(void);
void __cdecl he_AllocTalentBoost(void);
void __cdecl he_RunTalentBoost(void);
void __cdecl he_AllocPlagueEvent(void);
void __cdecl he_RunPlagueEvent(void);
void __cdecl he_StartTaschendieb(void);
void __cdecl he_RunTaschendieb(void);
void __cdecl he_InitSchutzgeld(void);
void __cdecl he_RunSchutzgeld(void);
void __cdecl he_AllocBetriebsPruefung(void);
void __cdecl he_RunBetriebsPruefung(void);
void __cdecl he_AllocMultiActorAction(void);
void __cdecl he_RunUmlandPatrol(void);
void __cdecl he_StartSimUnfall(void);
void __cdecl RunSimUnfall(void);
void __cdecl he_StartPacht(void);
void __cdecl he_RunPacht(void);
void __cdecl he_InitAction0x69(void);
void __cdecl he_RunTitleGrantEvent(void);
void __cdecl he_InitSimulateWirtshaus(void);
void __cdecl gm_SimulateWirtshaus(void);
void __cdecl he_StartTalentLevelAction(void);
void __cdecl d2_HandleTalentLevelDialog(void);
void __cdecl he_InitAction0x6bGedicht(void);
void __cdecl he_RunBardeEvent(void);
void __cdecl he_InitAction0x6d(void);
void __cdecl he_RunCityPopulationEvent(void);
void __cdecl he_RunAction0x6f(void);
void __cdecl he_InitSimKrankheiten(void);
void __cdecl RunSimKrankheiten(void);
void __cdecl he_InitDunkleEcke(void);
void __cdecl he_RunDunkleEcke(void);
void __cdecl he_AllocSmokeEffect(void);
void __cdecl he_RunTimedEffectAction(void);
void __cdecl he_AllocUnkendunk(void);
void __cdecl he_RunUnkendunk(void);
void __cdecl he_PickNextSensenmannTarget(void);
void __cdecl he_InitAction0x79Report(void);
void __cdecl he_BroadcastLeaderboard(void);
void __cdecl he_InitPoliticians(void);
void __cdecl he_RunPoliticians(void);
void __cdecl fcn_0055a020(void);
void __cdecl he_InitOfficeAudit(void);
void __cdecl he_RunOfficeAudit(void);
void __cdecl he_StartMeisterpruefungNotice(void);
void __cdecl he_RunMeisterpruefungNoticePrompt(void);
void __cdecl he_AllocAction0x7f(void);
void __cdecl he_RunAction0x7f(void);
void __cdecl he_StartCountdownAction(void);
void __cdecl he_RunCountdownAction(void);
void __cdecl he_StartSideChange(void);
void __cdecl he_RunAction0x81(void);
void __cdecl he_StartAction0x82SkillModifier(void);
void __cdecl he_HandleAction0x82SkillModifier(void);
void __cdecl he_AllocDailyCouncilEvent(void);
void __cdecl he_RunDailyCouncilEvent(void);
void __cdecl he_StartTutorialEvent(void);
void __cdecl he_UpdateTutorialEvent(void);
void __cdecl he_InitTitleAward(void);
void __cdecl d2_ShowTitleAward(void);

/* ADDRESS: GOLDTL 0x0055b3e0 */
int __cdecl he_RegisterEventHandlers(void)
{
	if (he_RegisterHandler(34, (void*) 0x549b30, (void*) 0x549b40) != 0) {
		return 1;
	}
	if (he_RegisterHandler(41, (void*) fcn_00549b50, (void*) fcn_00549b80) != 0) {
		return 1;
	}
	if (he_RegisterHandler(42, (void*) he_StartElectionCampaign, (void*) he_RunElectionCampaign) != 0) {
		return 1;
	}
	if (he_RegisterHandler(43, (void*) he_AllocPredigt, (void*) he_RunPredigt) != 0) {
		return 1;
	}
	if (he_RegisterHandler(44, (void*) he_StartCourtTrial, (void*) 0x0054ac70) != 0) {
		return 1;
	}
	if (he_RegisterHandler(45, (void*) he_StartCourtAction, (void*) 0x54b140) != 0) {
		return 1;
	}
	if (he_RegisterHandler(46, (void*) he_StartAction0x2e, (void*) he_HandleAction0x2e) != 0) {
		return 1;
	}
	if (he_RegisterHandler(47, (void*) he_StartSkillDuelEvent, (void*) he_RunSkillDuelEvent) != 0) {
		return 1;
	}
	if (he_RegisterHandler(48, (void*) he_StartFreeActionStub, (void*) 0x54b810) != 0) {
		return 1;
	}
	if (he_RegisterHandler(55, (void*) he_StartFest, (void*) he_UpdateFest) != 0) {
		return 1;
	}
	if (he_RegisterHandler(54, (void*) he_InitInvitation, (void*) he_RunInvitation) != 0) {
		return 1;
	}
	if (he_RegisterHandler(53, (void*) 0x0054c240, (void*) he_RunAction53) != 0) {
		return 1;
	}
	if (he_RegisterHandler(65, (void*) he_StartCourtship, (void*) he_RunCourtship) != 0) {
		return 1;
	}
	if (he_RegisterHandler(66, (void*) he_StartRandomEvent, (void*) 0x0054d810) != 0) {
		return 1;
	}
	if (he_RegisterHandler(67, (void*) he_InitStreife, (void*) he_UpdateRobberyAction) != 0) {
		return 1;
	}
	he_RegisterActionMeta(67, 0, 0, 1287, -1);
	if (he_RegisterHandler(68, (void*) he_StartRazzia, (void*) he_RunRazzia) != 0) {
		return 1;
	}
	if (he_RegisterHandler(69, (void*) he_StartDuellChallenge, (void*) he_RunDuellChallenge) != 0) {
		return 1;
	}
	if (he_RegisterHandler(70, (void*) he_InitDuellIntro, (void*) he_RunDuellIntro) != 0) {
		return 1;
	}
	if (he_RegisterHandler(71, (void*) 0x0054f910, (void*) he_RunDuellCutscene) != 0) {
		return 1;
	}
	if (he_RegisterHandler(74, (void*) he_AllocRndGeselle, (void*) he_RunHireJourneymanAction) != 0) {
		return 1;
	}
	if (he_RegisterHandler(75, (void*) he_StartAction0x4b, (void*) he_HandleAction0x4b) != 0) {
		return 1;
	}
	if (he_RegisterHandler(81, (void*) 0x550480, (void*) 0x5504c0) != 0) {
		return 1;
	}
	if (he_RegisterHandler(82, (void*) he_InitAction0x52, (void*) he_RunAction0x52) != 0) {
		return 1;
	}
	if (he_RegisterHandler(83, (void*) he_InitEvent053, (void*) he_RunEvent053) != 0) {
		return 1;
	}
	if (he_RegisterHandler(84, (void*) 0x00550770, (void*) he_RunMeisterpruefungPrompt) != 0) {
		return 1;
	}
	if (he_RegisterHandler(85, (void*) he_InitMeisterpruefDialog, (void*) he_RunMeisterpruefungExam) != 0) {
		return 1;
	}
	if (he_RegisterHandler(86, (void*) he_InitAction0x56, (void*) he_RunGambleBet) != 0) {
		return 1;
	}
	if (he_RegisterHandler(87, (void*) he_AllocSellObjekt, (void*) 0x00550de0) != 0) {
		return 1;
	}
	if (he_RegisterHandler(88, (void*) he_AllocBuildingDamageEvent, (void*) he_RunBuildingDamageEvent) != 0) {
		return 1;
	}
	if (he_RegisterHandler(90, (void*) he_ScheduleDelayedAction, (void*) he_RunAction0x5a) != 0) {
		return 1;
	}
	if (he_RegisterHandler(91, (void*) he_StartPeriodicStipend, (void*) he_RunPeriodicStipend) != 0) {
		return 1;
	}
	if (he_RegisterHandler(92, (void*) 0x5512f0, (void*) he_RunPeriodicApDrain) != 0) {
		return 1;
	}
	if (he_RegisterHandler(93, (void*) he_InitAction0x5d, (void*) he_RunChildBirth) != 0) {
		return 1;
	}
	if (he_RegisterHandler(94, (void*) he_AllocLevelTraining, (void*) he_RunLevelTraining) != 0) {
		return 1;
	}
	if (he_RegisterHandler(95, (void*) he_AllocApTraitAction, (void*) he_RunApTraitAction) != 0) {
		return 1;
	}
	if (he_RegisterHandler(96, (void*) he_AllocTalentBoost, (void*) he_RunTalentBoost) != 0) {
		return 1;
	}
	if (he_RegisterHandler(89, (void*) he_AllocPlagueEvent, (void*) he_RunPlagueEvent) != 0) {
		return 1;
	}
	if (he_RegisterHandler(97, (void*) he_StartTaschendieb, (void*) he_RunTaschendieb) != 0) {
		return 1;
	}
	he_RegisterActionMeta(97, 0, 0, 1287, -1);
	if (he_RegisterHandler(99, (void*) 0x005530d0, (void*) 0x00553110) != 0) {
		return 1;
	}
	if (he_RegisterHandler(98, (void*) he_InitSchutzgeld, (void*) he_RunSchutzgeld) != 0) {
		return 1;
	}
	he_RegisterActionMeta(98, 0, 0, 1294, -1);
	if (he_RegisterHandler(100, (void*) he_AllocBetriebsPruefung, (void*) he_RunBetriebsPruefung) != 0) {
		return 1;
	}
	he_RegisterActionMeta(100, 0, 0, 1287, -1);
	if (he_RegisterHandler(101, (void*) he_AllocMultiActorAction, (void*) he_RunUmlandPatrol) != 0) {
		return 1;
	}
	he_RegisterActionMeta(101, 0, 0, 1287, -1);
	if (he_RegisterHandler(102, (void*) he_StartSimUnfall, (void*) RunSimUnfall) != 0) {
		return 1;
	}
	if (he_RegisterHandler(103, (void*) he_StartPacht, (void*) he_RunPacht) != 0) {
		return 1;
	}
	if (he_RegisterHandler(104, (void*) he_InitSimulateWirtshaus, (void*) gm_SimulateWirtshaus) != 0) {
		return 1;
	}
	if (he_RegisterHandler(105, (void*) he_InitAction0x69, (void*) he_RunTitleGrantEvent) != 0) {
		return 1;
	}
	if (he_RegisterHandler(106, (void*) he_StartTalentLevelAction, (void*) d2_HandleTalentLevelDialog) != 0) {
		return 1;
	}
	if (he_RegisterHandler(107, (void*) he_InitAction0x6bGedicht, (void*) he_RunBardeEvent) != 0) {
		return 1;
	}
	if (he_RegisterHandler(109, (void*) he_InitAction0x6d, (void*) he_RunCityPopulationEvent) != 0) {
		return 1;
	}
	if (he_RegisterHandler(111, (void*) 0x556a20, (void*) he_RunAction0x6f) != 0) {
		return 1;
	}
	if (he_RegisterHandler(112, (void*) he_InitSimKrankheiten, (void*) RunSimKrankheiten) != 0) {
		return 1;
	}
	if (he_RegisterHandler(116, (void*) he_InitDunkleEcke, (void*) he_RunDunkleEcke) != 0) {
		return 1;
	}
	if (he_RegisterHandler(118, (void*) he_AllocSmokeEffect, (void*) he_RunTimedEffectAction) != 0) {
		return 1;
	}
	if (he_RegisterHandler(119, (void*) he_AllocUnkendunk, (void*) he_RunUnkendunk) != 0) {
		return 1;
	}
	if (he_RegisterHandler(120, (void*) he_PickNextSensenmannTarget, (void*) 0x00558e80) != 0) {
		return 1;
	}
	if (he_RegisterHandler(121, (void*) he_InitAction0x79Report, (void*) he_BroadcastLeaderboard) != 0) {
		return 1;
	}
	if (he_RegisterHandler(122, (void*) he_InitPoliticians, (void*) he_RunPoliticians) != 0) {
		return 1;
	}
	if (he_RegisterHandler(123, (void*) fcn_0055a020, (void*) 0x55a030) != 0) {
		return 1;
	}
	if (he_RegisterHandler(125, (void*) he_InitOfficeAudit, (void*) he_RunOfficeAudit) != 0) {
		return 1;
	}
	if (he_RegisterHandler(126, (void*) he_StartMeisterpruefungNotice, (void*) he_RunMeisterpruefungNoticePrompt) != 0) {
		return 1;
	}
	if (he_RegisterHandler(127, (void*) he_AllocAction0x7f, (void*) he_RunAction0x7f) != 0) {
		return 1;
	}
	if (he_RegisterHandler(128, (void*) he_StartCountdownAction, (void*) he_RunCountdownAction) != 0) {
		return 1;
	}
	if (he_RegisterHandler(129, (void*) he_StartSideChange, (void*) he_RunAction0x81) != 0) {
		return 1;
	}
	if (he_RegisterHandler(130, (void*) he_StartAction0x82SkillModifier, (void*) he_HandleAction0x82SkillModifier) != 0) {
		return 1;
	}
	if (he_RegisterHandler(134, (void*) he_AllocDailyCouncilEvent, (void*) he_RunDailyCouncilEvent) != 0) {
		return 1;
	}
	if (he_RegisterHandler(135, (void*) he_StartTutorialEvent, (void*) he_UpdateTutorialEvent) != 0) {
		return 1;
	}
	return he_RegisterHandler(165, (void*) he_InitTitleAward, (void*) d2_ShowTitleAward) != 0;
}
