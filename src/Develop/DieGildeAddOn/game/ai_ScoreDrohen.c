typedef struct Stat0049c800 {
	int v[9];
} Stat0049c800;

extern void __cdecl gm_GetLawEntry(int a, Stat0049c800* p);
extern void __cdecl ai_ComputeActionScore(void* a0, void* a1, int a2, int a3, Stat0049c800* p);
extern void __cdecl ai_ComputeBaseActionScore(void* a0, void* a1, int a2, int a3, int a4, int a5, int a6);


/* ADDRESS: GOLDTL 0x0049c800 */
/* ADDRESS: GOLDDE 0x0048b240 */
void __cdecl ai_ScoreDrohen(int* out1, int* out2, int a2, int a3, int a4, int a5, int a6)
{
	Stat0049c800 st;

	*out1 = 0;
	*out2 = 0;
	gm_GetLawEntry(0x13, &st);
	if (st.v[6] != 0) {
		ai_ComputeActionScore(out1, out2, a2, a3, &st);
		return;
	}
	ai_ComputeBaseActionScore(out1, out2, a2, a3, a4, a5, a6);
}
