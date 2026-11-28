


extern float flt_6;

int __cdecl ahm_CheckFlag(void*);
int __cdecl ahm_CountActiveSlots(char*);
float __cdecl ahm_GetEssenceValue(char*, int);

/* ADDRESS: GOLDDE 0x004d8df0 */
int __cdecl ahm_HasRecipeSlotCapacity(char* entity)
{
	int count;

	if (ahm_CheckFlag(entity) == 0) {
		return 0;
	}
	count = ahm_CountActiveSlots(entity);
	return (int) (ahm_GetEssenceValue(entity, 2) * flt_6) > count;
}
