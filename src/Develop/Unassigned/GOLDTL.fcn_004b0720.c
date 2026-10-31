char* __cdecl gm_LookupEntityRecordById(int);
float __cdecl fcn_004fef80(char*);
float __cdecl fcn_004ff210(short, int);


/* ADDRESS: GOLD 0x004b05e0 */
/* ADDRESS: GOLDTL 0x004b0720 */
int __cdecl fcn_004b0720(char* o, int i)
{
	char* p;

	if (o != 0 && i < 8) {
		p = gm_LookupEntityRecordById(*(int*) (o + i * 8 + 4));
		if (p != 0) {
			fcn_004ff210(*(short*) p, (int) -(fcn_004fef80(p) + 1.0f));
			return 1;
		}
	}
	return 0;
}
