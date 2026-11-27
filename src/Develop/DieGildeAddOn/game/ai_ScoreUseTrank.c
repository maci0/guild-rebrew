int __cdecl gm_GetLawEntry(int idx, void* dst);
int __cdecl ai_ComputeActionScore(void* o0, void* o1, int idx, char* s, void* p4);
int __cdecl ai_ComputeBaseActionScore(void* o0, void* o1, int idx, char* s, int a4, int a5, void* a6);

/* ADDRESS: GOLDTL 0x0049bd50 */
int __cdecl ai_ScoreUseTrank(void* firstScore, void* secondScore, int idx, char* entity, int extraA, int extraB, void* action)
{
	char lawInfo[0x24];

	*(int*) firstScore = 0;
	*(int*) secondScore = 0;
	if (*(int*) ((char*) action + 0x10) < 0x1c || *(int*) ((char*) action + 0x10) > 0x22)
		return 0;
	gm_GetLawEntry(0x12, lawInfo);
	if (*(int*) (lawInfo + 0x18) != 0)
		return ai_ComputeActionScore(firstScore, secondScore, idx, entity, lawInfo);
	return ai_ComputeBaseActionScore(firstScore, secondScore, idx, entity, extraA, extraB, action);
}
