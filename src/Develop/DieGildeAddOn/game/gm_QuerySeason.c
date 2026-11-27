int __cdecl gm_GetSeason(int* clock);

/* ADDRESS: GOLDTL 0x0052a310 */
int __cdecl gm_QuerySeason(int* clock)
{
	return gm_GetSeason(clock);
}
