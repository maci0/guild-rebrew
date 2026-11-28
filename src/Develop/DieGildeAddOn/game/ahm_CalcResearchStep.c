
extern float flt_0_0;


float __cdecl ahm_GetEssenceValue(char*, int);
int* __cdecl ahm_FindRecipeSlot(char*, unsigned int);
int __cdecl ahm_CalcResearchDuration(char*, char*);

/* ADDRESS: GOLDTL 0x004ecd50 */
/* ADDRESS: GOLDDE 0x004d91a0 */
float __cdecl ahm_CalcResearchStep(char* actor, unsigned int* recipe, int* maxDuration)
{
	float x;
	int* obj;
	int requested;
	int v4;
	int adjusted;
	int amount;

	x = ahm_GetEssenceValue(actor, 2);
	obj = ahm_FindRecipeSlot(actor, *recipe);
	if (obj == 0) {
		return 0.0f;
	}
	if (*((float*) obj + 1) >= 1.0f) {
		return 0.0f;
	}
	requested = *maxDuration;
	if (requested <= 0) {
		return 0.0f;
	}
	v4 = ahm_CalcResearchDuration(actor, (char*) recipe);
	adjusted = (int) ((float) v4 * (1.0f - x * 0.5f) * (1.0f - *((float*) obj + 1)));
	if (adjusted <= 0) {
		return 0.0f;
	}
	amount = adjusted;
	if (requested < adjusted) {
		amount = requested;
	}
	*maxDuration = amount;
	return ((float) amount / (float) adjusted) * (1.0f - *((float*) obj + 1));
}
