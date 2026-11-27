/* The inventory start at 0x49d059 is the branch target of the je at
   0x49d03b, not an independent function. The real function entry is
   0x49d030 and its extent runs to the ret at 0x49d0c8 (152 bytes). */
extern int gm_GetLawEntry(int idx, void* out);
extern int ai_ComputeActionScore(int* a1, int* a2, int a3, int a4, void* s);
extern int fcn_004a4410(int* a1, int* a2, int a3, int a4, int z, int a6, int a7);

/* ADDRESS: GOLDTL 0x0049d030 */
int __cdecl ai_ScoreErpressen(int* firstOut, int* secondOut, int a3, int a4, int a5, int a6, int a7)
{
	char s[0x24];
	int* firstScore;
	int* secondScore;

	firstScore = firstOut;
	secondScore = secondOut;
	if (a5 != 0) {
		*firstScore = (int) 0xf149f2ca;
		*secondScore = (int) 0xf149f2ca;
		return 0;
	}
	*firstScore = 0;
	*secondScore = 0;
	gm_GetLawEntry(0x16, s);
	if (*(int*) (s + 0x18) != 0) {
		return ai_ComputeActionScore(firstScore, secondScore, a3, a4, s);
	}
	return fcn_004a4410(firstScore, secondScore, a3, a4, 0, a6, a7);
}
