void __cdecl fcn_004e4730(char*);
int __cdecl cut_RunTurnRound(int a, int b);
void __cdecl cut_WaitTicks(int a);
void __cdecl cut_CleanupCutscene(void);

/* ADDRESS: GOLDTL 0x004e1920 */
void __cdecl cut_RunTobyCutscene(int cutscene)
{
	fcn_004e4730("cutscene_toby.ed3");
	cut_RunTurnRound(cutscene, 0);
	cut_RunTurnRound(cutscene, 0);
	cut_WaitTicks(5);
	cut_CleanupCutscene();
}
