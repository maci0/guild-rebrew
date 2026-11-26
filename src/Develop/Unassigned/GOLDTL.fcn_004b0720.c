char* __cdecl gm_LookupEntityRecordById(int);
float __cdecl gm_GetEntityHealth(char*);
float __cdecl fcn_004ff210(short, int);


/* ADDRESS: GOLD 0x004b05e0 */
/* ADDRESS: GOLDTL 0x004b0720 */
int __cdecl hst_HandleKillPlayer(char* record, int index)
{
	char* p;

	if (record != 0 && index < 8) {
		p = gm_LookupEntityRecordById(*(int*) (record + index * 8 + 4));
		if (p != 0) {
			fcn_004ff210(*(short*) p, (int) -(gm_GetEntityHealth(p) + 1.0f));
			return 1;
		}
	}
	return 0;
}
