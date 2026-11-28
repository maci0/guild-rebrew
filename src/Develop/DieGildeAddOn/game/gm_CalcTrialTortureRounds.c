


#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

/* ADDRESS: GOLDDE 0x00482710 */
int __cdecl gm_CalcTrialTortureRounds(char* trial)
{
	return (int) min(max(*(float*) (trial + 4) * 0.25f, 2.0f), 6.0f);
}
