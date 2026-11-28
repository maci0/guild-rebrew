extern char d3_CurrentSeason;



void __cdecl SelectTextureSet(char*, int, char, int);

/* ADDRESS: GOLDDE 0x00501020 */
char __cdecl d3_ApplySeasonTextureSet(char* obj)
{
	int s;

	s = *(int*) (obj + 0x220);
	if (s != 2 && s != 4) {
		if (s == 3) {
			SelectTextureSet(obj, *(int*) (obj + 0x1ec) + 0xf4, d3_CurrentSeason, 1);
		} else {
			SelectTextureSet(obj, *(int*) (obj + 0x1ec) + 0xf4, d3_CurrentSeason, 1);
		}
	}
	return 1;
}
