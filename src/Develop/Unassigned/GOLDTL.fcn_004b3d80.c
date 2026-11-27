int __cdecl fcn_004b3db0(int);
int __cdecl gm_AllocMissionJob(int, int, int);


/* ADDRESS: GOLDTL 0x004b3d80 */
int __cdecl fcn_004b3d80(int a, int b, int c)
{
	return gm_AllocMissionJob(a, fcn_004b3db0(b), c);
}
