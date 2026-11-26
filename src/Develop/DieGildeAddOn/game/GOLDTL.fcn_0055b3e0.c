int __cdecl he_RegisterHandler(int, void*, void*);
int __cdecl fcn_00530ab0(int, char*, int, int, int);
void __cdecl fcn_00549b50(void);
void __cdecl fcn_00549b80(void);
void __cdecl fcn_00549b90(void);
void __cdecl fcn_0054a210(void);
void __cdecl he_AllocPredigt(void);
void __cdecl fcn_0054a6a0(void);
void __cdecl fcn_0054aa70(void);
void __cdecl fcn_0054b130(void);
void __cdecl fcn_0054b150(void);
void __cdecl he_HandleAction0x2e(void);
void __cdecl fcn_0054b420(void);
void __cdecl fcn_0054b450(void);
void __cdecl fcn_0054b800(void);
void __cdecl fcn_0054b820(void);
void __cdecl he_UpdateFest(void);
void __cdecl fcn_0054bc40(void);
void __cdecl fcn_0054bc90(void);
void __cdecl he_RunAction53(void);
void __cdecl fcn_0054c800(void);
void __cdecl fcn_0054ca10(void);
void __cdecl he_StartAction0x42EntityMsg(void);
void __cdecl he_InitStreife(void);
void __cdecl fcn_0054da10(void);
void __cdecl he_StartRazzia(void);
void __cdecl fcn_0054e390(void);
void __cdecl fcn_0054ee10(void);
void __cdecl fcn_0054f0c0(void);
void __cdecl fcn_0054f340(void);
void __cdecl fcn_0054f600(void);
void __cdecl fcn_0054fd60(void);
void __cdecl he_AllocRndGeselle(void);
void __cdecl he_RunHireJourneymanAction(void);
void __cdecl he_StartAction0x4b(void);
void __cdecl he_HandleAction0x4b(void);
void __cdecl fcn_005504f0(void);
void __cdecl fcn_00550540(void);
void __cdecl he_InitEvent053(void);
void __cdecl fcn_005505b0(void);
void __cdecl fcn_005507a0(void);
void __cdecl fcn_00550940(void);
void __cdecl fcn_00550980(void);
void __cdecl fcn_00550ba0(void);
void __cdecl fcn_00550be0(void);
void __cdecl he_AllocSellObjekt(void);
void __cdecl fcn_00551010(void);
void __cdecl fcn_00551050(void);
void __cdecl fcn_00551160(void);
void __cdecl fcn_005511a0(void);
void __cdecl fcn_00551210(void);
void __cdecl fcn_00551250(void);
void __cdecl fcn_00551330(void);
void __cdecl fcn_005513c0(void);
void __cdecl fcn_005513d0(void);
void __cdecl fcn_00551650(void);
void __cdecl fcn_005516e0(void);
void __cdecl he_AllocApTraitAction(void);
void __cdecl fcn_00551a20(void);
void __cdecl fcn_00551c20(void);
void __cdecl fcn_00551d50(void);
void __cdecl he_AllocPlagueEvent(void);
void __cdecl he_RunPlagueEvent(void);
void __cdecl he_StartTaschendieb(void);
void __cdecl fcn_00552a60(void);
void __cdecl he_InitSchutzgeld(void);
void __cdecl fcn_00553490(void);
void __cdecl he_AllocBetriebsPruefung(void);
void __cdecl fcn_00553cd0(void);
void __cdecl he_AllocMultiActorAction(void);
void __cdecl fcn_00554170(void);
void __cdecl fcn_00554770(void);
void __cdecl RunSimUnfall(void);
void __cdecl he_StartAction0x67(void);
void __cdecl fcn_00554b90(void);
void __cdecl fcn_00554ed0(void);
void __cdecl fcn_00554f00(void);
void __cdecl fcn_00555440(void);
void __cdecl gm_SimulateWirtshaus(void);
void __cdecl he_StartTalentLevelAction(void);
void __cdecl d2_HandleTalentLevelDialog(void);
void __cdecl fcn_00555cd0(void);
void __cdecl fcn_00555d30(void);
void __cdecl fcn_00556110(void);
void __cdecl fcn_00556170(void);
void __cdecl fcn_00556b40(void);
void __cdecl fcn_00556e30(void);
void __cdecl RunSimKrankheiten(void);
void __cdecl he_InitDunkleEcke(void);
void __cdecl fcn_00557460(void);
void __cdecl he_AllocSmokeEffect(void);
void __cdecl he_RunTimedEffectAction(void);
void __cdecl he_AllocUnkendunk(void);
void __cdecl fcn_00558220(void);
void __cdecl fcn_00558d10(void);
void __cdecl fcn_005591c0(void);
void __cdecl fcn_00559200(void);
void __cdecl fcn_005595e0(void);
void __cdecl he_RunPoliticians(void);
void __cdecl fcn_0055a020(void);
void __cdecl fcn_0055a040(void);
void __cdecl fcn_0055a0b0(void);
void __cdecl fcn_0055a380(void);
void __cdecl fcn_0055a3d0(void);
void __cdecl fcn_0055a540(void);
void __cdecl fcn_0055a5b0(void);
void __cdecl fcn_0055a820(void);
void __cdecl he_RunCountdownAction(void);
void __cdecl fcn_0055a8e0(void);
void __cdecl fcn_0055a920(void);
void __cdecl he_StartAction0x82SkillModifier(void);
void __cdecl he_HandleAction0x82SkillModifier(void);
void __cdecl fcn_0055ac00(void);
void __cdecl fcn_0055aca0(void);
void __cdecl fcn_0055af10(void);
void __cdecl he_UpdateTutorialEvent(void);
void __cdecl fcn_0055afb0(void);
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
	if (he_RegisterHandler(42, (void*) fcn_00549b90, (void*) fcn_0054a210) != 0) {
		return 1;
	}
	if (he_RegisterHandler(43, (void*) he_AllocPredigt, (void*) fcn_0054a6a0) != 0) {
		return 1;
	}
	if (he_RegisterHandler(44, (void*) fcn_0054aa70, (void*) 0x0054ac70) != 0) {
		return 1;
	}
	if (he_RegisterHandler(45, (void*) fcn_0054b130, (void*) 0x54b140) != 0) {
		return 1;
	}
	if (he_RegisterHandler(46, (void*) fcn_0054b150, (void*) he_HandleAction0x2e) != 0) {
		return 1;
	}
	if (he_RegisterHandler(47, (void*) fcn_0054b420, (void*) fcn_0054b450) != 0) {
		return 1;
	}
	if (he_RegisterHandler(48, (void*) fcn_0054b800, (void*) 0x54b810) != 0) {
		return 1;
	}
	if (he_RegisterHandler(55, (void*) fcn_0054b820, (void*) he_UpdateFest) != 0) {
		return 1;
	}
	if (he_RegisterHandler(54, (void*) fcn_0054bc40, (void*) fcn_0054bc90) != 0) {
		return 1;
	}
	if (he_RegisterHandler(53, (void*) 0x0054c240, (void*) he_RunAction53) != 0) {
		return 1;
	}
	if (he_RegisterHandler(65, (void*) fcn_0054c800, (void*) fcn_0054ca10) != 0) {
		return 1;
	}
	if (he_RegisterHandler(66, (void*) he_StartAction0x42EntityMsg, (void*) 0x0054d810) != 0) {
		return 1;
	}
	if (he_RegisterHandler(67, (void*) he_InitStreife, (void*) fcn_0054da10) != 0) {
		return 1;
	}
	fcn_00530ab0(67, 0, 0, 1287, -1);
	if (he_RegisterHandler(68, (void*) he_StartRazzia, (void*) fcn_0054e390) != 0) {
		return 1;
	}
	if (he_RegisterHandler(69, (void*) fcn_0054ee10, (void*) fcn_0054f0c0) != 0) {
		return 1;
	}
	if (he_RegisterHandler(70, (void*) fcn_0054f340, (void*) fcn_0054f600) != 0) {
		return 1;
	}
	if (he_RegisterHandler(71, (void*) 0x0054f910, (void*) fcn_0054fd60) != 0) {
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
	if (he_RegisterHandler(82, (void*) fcn_005504f0, (void*) fcn_00550540) != 0) {
		return 1;
	}
	if (he_RegisterHandler(83, (void*) he_InitEvent053, (void*) fcn_005505b0) != 0) {
		return 1;
	}
	if (he_RegisterHandler(84, (void*) 0x00550770, (void*) fcn_005507a0) != 0) {
		return 1;
	}
	if (he_RegisterHandler(85, (void*) fcn_00550940, (void*) fcn_00550980) != 0) {
		return 1;
	}
	if (he_RegisterHandler(86, (void*) fcn_00550ba0, (void*) fcn_00550be0) != 0) {
		return 1;
	}
	if (he_RegisterHandler(87, (void*) he_AllocSellObjekt, (void*) 0x00550de0) != 0) {
		return 1;
	}
	if (he_RegisterHandler(88, (void*) fcn_00551010, (void*) fcn_00551050) != 0) {
		return 1;
	}
	if (he_RegisterHandler(90, (void*) fcn_00551160, (void*) fcn_005511a0) != 0) {
		return 1;
	}
	if (he_RegisterHandler(91, (void*) fcn_00551210, (void*) fcn_00551250) != 0) {
		return 1;
	}
	if (he_RegisterHandler(92, (void*) 0x5512f0, (void*) fcn_00551330) != 0) {
		return 1;
	}
	if (he_RegisterHandler(93, (void*) fcn_005513c0, (void*) fcn_005513d0) != 0) {
		return 1;
	}
	if (he_RegisterHandler(94, (void*) fcn_00551650, (void*) fcn_005516e0) != 0) {
		return 1;
	}
	if (he_RegisterHandler(95, (void*) he_AllocApTraitAction, (void*) fcn_00551a20) != 0) {
		return 1;
	}
	if (he_RegisterHandler(96, (void*) fcn_00551c20, (void*) fcn_00551d50) != 0) {
		return 1;
	}
	if (he_RegisterHandler(89, (void*) he_AllocPlagueEvent, (void*) he_RunPlagueEvent) != 0) {
		return 1;
	}
	if (he_RegisterHandler(97, (void*) he_StartTaschendieb, (void*) fcn_00552a60) != 0) {
		return 1;
	}
	fcn_00530ab0(97, 0, 0, 1287, -1);
	if (he_RegisterHandler(99, (void*) 0x005530d0, (void*) 0x00553110) != 0) {
		return 1;
	}
	if (he_RegisterHandler(98, (void*) he_InitSchutzgeld, (void*) fcn_00553490) != 0) {
		return 1;
	}
	fcn_00530ab0(98, 0, 0, 1294, -1);
	if (he_RegisterHandler(100, (void*) he_AllocBetriebsPruefung, (void*) fcn_00553cd0) != 0) {
		return 1;
	}
	fcn_00530ab0(100, 0, 0, 1287, -1);
	if (he_RegisterHandler(101, (void*) he_AllocMultiActorAction, (void*) fcn_00554170) != 0) {
		return 1;
	}
	fcn_00530ab0(101, 0, 0, 1287, -1);
	if (he_RegisterHandler(102, (void*) fcn_00554770, (void*) RunSimUnfall) != 0) {
		return 1;
	}
	if (he_RegisterHandler(103, (void*) he_StartAction0x67, (void*) fcn_00554b90) != 0) {
		return 1;
	}
	if (he_RegisterHandler(104, (void*) fcn_00555440, (void*) gm_SimulateWirtshaus) != 0) {
		return 1;
	}
	if (he_RegisterHandler(105, (void*) fcn_00554ed0, (void*) fcn_00554f00) != 0) {
		return 1;
	}
	if (he_RegisterHandler(106, (void*) he_StartTalentLevelAction, (void*) d2_HandleTalentLevelDialog) != 0) {
		return 1;
	}
	if (he_RegisterHandler(107, (void*) fcn_00555cd0, (void*) fcn_00555d30) != 0) {
		return 1;
	}
	if (he_RegisterHandler(109, (void*) fcn_00556110, (void*) fcn_00556170) != 0) {
		return 1;
	}
	if (he_RegisterHandler(111, (void*) 0x556a20, (void*) fcn_00556b40) != 0) {
		return 1;
	}
	if (he_RegisterHandler(112, (void*) fcn_00556e30, (void*) RunSimKrankheiten) != 0) {
		return 1;
	}
	if (he_RegisterHandler(116, (void*) he_InitDunkleEcke, (void*) fcn_00557460) != 0) {
		return 1;
	}
	if (he_RegisterHandler(118, (void*) he_AllocSmokeEffect, (void*) he_RunTimedEffectAction) != 0) {
		return 1;
	}
	if (he_RegisterHandler(119, (void*) he_AllocUnkendunk, (void*) fcn_00558220) != 0) {
		return 1;
	}
	if (he_RegisterHandler(120, (void*) fcn_00558d10, (void*) 0x00558e80) != 0) {
		return 1;
	}
	if (he_RegisterHandler(121, (void*) fcn_005591c0, (void*) fcn_00559200) != 0) {
		return 1;
	}
	if (he_RegisterHandler(122, (void*) fcn_005595e0, (void*) he_RunPoliticians) != 0) {
		return 1;
	}
	if (he_RegisterHandler(123, (void*) fcn_0055a020, (void*) 0x55a030) != 0) {
		return 1;
	}
	if (he_RegisterHandler(125, (void*) fcn_0055a040, (void*) fcn_0055a0b0) != 0) {
		return 1;
	}
	if (he_RegisterHandler(126, (void*) fcn_0055a380, (void*) fcn_0055a3d0) != 0) {
		return 1;
	}
	if (he_RegisterHandler(127, (void*) fcn_0055a540, (void*) fcn_0055a5b0) != 0) {
		return 1;
	}
	if (he_RegisterHandler(128, (void*) fcn_0055a820, (void*) he_RunCountdownAction) != 0) {
		return 1;
	}
	if (he_RegisterHandler(129, (void*) fcn_0055a8e0, (void*) fcn_0055a920) != 0) {
		return 1;
	}
	if (he_RegisterHandler(130, (void*) he_StartAction0x82SkillModifier, (void*) he_HandleAction0x82SkillModifier) != 0) {
		return 1;
	}
	if (he_RegisterHandler(134, (void*) fcn_0055ac00, (void*) fcn_0055aca0) != 0) {
		return 1;
	}
	if (he_RegisterHandler(135, (void*) fcn_0055af10, (void*) he_UpdateTutorialEvent) != 0) {
		return 1;
	}
	return he_RegisterHandler(165, (void*) fcn_0055afb0, (void*) d2_ShowTitleAward) != 0;
}
