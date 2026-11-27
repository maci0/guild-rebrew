


extern char g_6a7e04[];
extern char g_6a7df8[];
extern char g_6a7df0[];

typedef void (__cdecl* handler)(char*);

int __cdecl he_RegisterHandler(int, handler, handler);
void __cdecl he_RegisterActionMeta(int, char*, int, int, int);
void __cdecl he_StartAbbau(char*);
void __cdecl he_RunAbbau(char*);
void __cdecl he_AllocProduktion(char*);
void __cdecl he_RunProduktion(char*);
void __cdecl fcn_00572760(char*);
void __cdecl fcn_00572770(char*);
void __cdecl he_StartSuchen(char*);
void __cdecl he_RunSuchen(char*);
void __cdecl he_StartResourceSuchen(char*);
void __cdecl he_RunResourceSuchen(char*);
void __cdecl he_StartVorkommenGefundenMsg(char*);
void __cdecl he_RunNeueVorkommenSuchen(char*);
void __cdecl he_StartHandelsrouteTrade(char*);
void __cdecl he_RunHandelsrouteTrade(char*);
void __cdecl he_StartAction0x0c(char*);
void __cdecl he_RunAction0x0c(char*);
void __cdecl he_AllocGebaeudeBauen(char*);
void __cdecl gm_HandleHausbau(char*);
void __cdecl fcn_00575450(char*);
void __cdecl fcn_00575460(char*);
void __cdecl he_StartMissionCheck(char*);
void __cdecl he_RunMissionCheck(char*);
void __cdecl fcn_005756f0(char*);
void __cdecl fcn_00575700(char*);

int __cdecl he_RegisterCoreActionHandlers(void)
{
	if (he_RegisterHandler(3, he_StartAbbau, he_RunAbbau) != 0) {
		return 1;
	}
	he_RegisterActionMeta(3, g_6a7e04, 1, 0x501, 0xac);
	if (he_RegisterHandler(4, he_AllocProduktion, he_RunProduktion) != 0) {
		return 1;
	}
	he_RegisterActionMeta(4, g_6a7df8, 1, 0x4ff, 0xac);
	if (he_RegisterHandler(5, fcn_00572760, fcn_00572770) != 0) {
		return 1;
	}
	if (he_RegisterHandler(8, he_StartSuchen, he_RunSuchen) != 0) {
		return 1;
	}
	he_RegisterActionMeta(8, g_6a7df0, 1, 0x500, 0xac);
	if (he_RegisterHandler(9, he_StartResourceSuchen, he_RunResourceSuchen) != 0) {
		return 1;
	}
	he_RegisterActionMeta(9, g_6a7df0, 1, 0x500, -1);
	if (he_RegisterHandler(0xa, he_StartVorkommenGefundenMsg, he_RunNeueVorkommenSuchen) != 0) {
		return 1;
	}
	if (he_RegisterHandler(0xb, he_StartHandelsrouteTrade, he_RunHandelsrouteTrade) != 0) {
		return 1;
	}
	if (he_RegisterHandler(0xc, he_StartAction0x0c, he_RunAction0x0c) != 0) {
		return 1;
	}
	if (he_RegisterHandler(0xd, he_AllocGebaeudeBauen, gm_HandleHausbau) != 0) {
		return 1;
	}
	if (he_RegisterHandler(0xe, fcn_00575450, fcn_00575460) != 0) {
		return 1;
	}
	if (he_RegisterHandler(0x4c, he_StartMissionCheck, he_RunMissionCheck) != 0) {
		return 1;
	}
	return he_RegisterHandler(0x4d, fcn_005756f0, fcn_00575700) != 0;
}
