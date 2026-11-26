
char* __cdecl gm_GetEquippedCombatGear(void* obj);
char* __cdecl gm_FindEntityActiveItem(void* obj);
float __cdecl gm_CalcCombatStrength(void* obj);
float __cdecl gm_GetEntityHealthRatio(void* obj);

/* ADDRESS: GOLDTL 0x004d3e90 */
float __cdecl fcn_004d3e90(void* obj, unsigned int mode)
{
	float r;
	int n;

	r = 0.0f;
	switch (mode) {
	case 0:
		{
			float f;
			f = 1.0f;
			if (*(char*) ((char*) obj + 0x1c4) != 0) {
				f = 0.5f;
			}
			n = *(int*) (gm_GetEquippedCombatGear(obj) + 0x58);
			if ((n == 1 || n == 2) && *(int*) (gm_FindEntityActiveItem(obj) + 0x20) <= 0) {
				f = 0.2f;
			}
			return gm_CalcCombatStrength(obj) * f;
		}
	case 1:
		{
			float f;
			if (*(char*) ((char*) obj + 0x1c4) == 1) {
				f = 1.0f;
			} else if (*(char*) ((char*) obj + 0x1c4) == 0) {
				f = 0.4f;
			} else {
				f = 0.5f;
			}
			n = *(int*) (gm_GetEquippedCombatGear(obj) + 0x58);
			if ((n == 1 || n == 2) && *(int*) (gm_FindEntityActiveItem(obj) + 0x20) <= 0) {
				f = 1.0f;
			}
			return f / gm_CalcCombatStrength(obj);
		}
	case 2:
		if (*(char*) ((char*) obj + 0x1c4) != 2) {
			return 0.5f;
		}
		r = 1.0f; break;
	case 4:
	case 5:
		if (*(char*) ((char*) obj + 0x1c4) == 2) {
			return 0.2f;
		}
		return 1.0f / gm_GetEntityHealthRatio(obj);
	case 3:
		r = 1.0f; break;
	}
	return r;
}
