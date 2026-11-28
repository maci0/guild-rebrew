
// fcn_004fe330 — (short)a[1] % 4.

/* ADDRESS: GOLDTL 0x00500e00 */
/* ADDRESS: GOLDDE 0x004ec510 */
int __cdecl gm_GetSeasonFromDate(char* date)
{
	return *(short*) (date + 2) % 4;
}

