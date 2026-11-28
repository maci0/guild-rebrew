extern char d3_CurrentSeason;



int __cdecl strncmp(const char*, const char*, unsigned int);
void __cdecl SelectTextureSet(char*, int, char, int);

/* ADDRESS: GOLDDE 0x00500fc0 */
void __cdecl d3_ApplyVegetationTextureSet(char* obj)
{
	if (!strncmp(obj, "pfl_", 4) || !strncmp(obj, "vg_", 3) || strncmp(obj, "!vg_", 4) == 0) {
		SelectTextureSet(obj, *(int*) (obj + 0x1cc), d3_CurrentSeason, 1);
	}
}
