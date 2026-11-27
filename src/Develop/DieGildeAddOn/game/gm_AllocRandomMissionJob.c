int __cdecl gm_PickRandomMissionEntry(int);
int __cdecl gm_AllocMissionJob(int, int, int);


/* ADDRESS: GOLDTL 0x004b3d80 */
int __cdecl gm_AllocRandomMissionJob(int a, int b, int c)
{
	return gm_AllocMissionJob(a, gm_PickRandomMissionEntry(b), c);
}
