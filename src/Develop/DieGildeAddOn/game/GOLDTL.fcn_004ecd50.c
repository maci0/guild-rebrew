
extern float g_6628a8;


float __cdecl ahm_GetEssenceValue(char*, int);
int* __cdecl ahm_FindRecipeSlot(char*, unsigned int);
int __cdecl fcn_004eccd0(char*, char*);

/* ADDRESS: GOLDTL 0x004ecd50 */
float __cdecl fcn_004ecd50(char* a0, unsigned int* a1, int* a2)
{
	float x;
	int* obj;
	int requested;
	int v4;
	int adjusted;
	int amount;

	x = ahm_GetEssenceValue(a0, 2);
	obj = ahm_FindRecipeSlot(a0, *a1);
	if (obj == 0) {
		return 0.0f;
	}
	if (*((float*) obj + 1) >= 1.0f) {
		return 0.0f;
	}
	requested = *a2;
	if (requested <= 0) {
		return 0.0f;
	}
	v4 = fcn_004eccd0(a0, (char*) a1);
	adjusted = (int) ((float) v4 * (1.0f - x * 0.5f) * (1.0f - *((float*) obj + 1)));
	if (adjusted <= 0) {
		return 0.0f;
	}
	amount = adjusted;
	if (requested < adjusted) {
		amount = requested;
	}
	*a2 = amount;
	return ((float) amount / (float) adjusted) * (1.0f - *((float*) obj + 1));
}
