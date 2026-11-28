

void __cdecl gm_UpdateCityEconomyStats(void*);

int __cdecl cm_ExUpdateCityEconomy(char* p, char* out)
{
	gm_UpdateCityEconomyStats(p + 0x10);
	if (out != 0) {
		out[0] = 1;
		out[1] = 0;
		*(int*) (out + 6) = 0;
	}
	return 0;
}
