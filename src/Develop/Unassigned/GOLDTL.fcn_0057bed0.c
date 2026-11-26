


void __cdecl he_ShowZigeunerMessage(int, int);
void __cdecl fcn_0057c020(int, int);
void __cdecl he_ApplyZigeunerBetrothal(int, int);
void __cdecl he_SwapZigeunerMoods(int, int);
void __cdecl he_SendZigeunerMsg9e(int, int);
void __cdecl he_SendZigeunerMsg9f(int, int);

void __cdecl fcn_0057bed0(int a, int b, int k)
{
	if (k == 0) {
		he_ShowZigeunerMessage(a, b);
	} else if (k == 1) {
		fcn_0057c020(a, b);
	} else if (k == 2) {
		he_ApplyZigeunerBetrothal(a, b);
	} else if (k == 3) {
		he_SwapZigeunerMoods(a, b);
	} else if (k == 4) {
		he_SendZigeunerMsg9e(a, b);
	} else {
		he_SendZigeunerMsg9f(a, b);
	}
}
