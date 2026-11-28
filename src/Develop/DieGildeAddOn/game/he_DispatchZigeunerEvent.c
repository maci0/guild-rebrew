


void __cdecl he_ShowZigeunerMessage(int, int);
void __cdecl he_ApplyZigeunerFavorPenalty(int, int);
void __cdecl he_ApplyZigeunerBetrothal(int, int);
void __cdecl he_SwapZigeunerMoods(int, int);
void __cdecl he_SendZigeunerMsg9e(int, int);
void __cdecl he_SendZigeunerMsg9f(int, int);

/* ADDRESS: GOLDDE 0x00561d00 */
void __cdecl he_DispatchZigeunerEvent(int actor, int target, int kind)
{
	if (kind == 0) {
		he_ShowZigeunerMessage(actor, target);
	} else if (kind == 1) {
		he_ApplyZigeunerFavorPenalty(actor, target);
	} else if (kind == 2) {
		he_ApplyZigeunerBetrothal(actor, target);
	} else if (kind == 3) {
		he_SwapZigeunerMoods(actor, target);
	} else if (kind == 4) {
		he_SendZigeunerMsg9e(actor, target);
	} else {
		he_SendZigeunerMsg9f(actor, target);
	}
}
