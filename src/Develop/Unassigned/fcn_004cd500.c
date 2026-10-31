void* __cdecl fcn_004e6a30(int id);
void __cdecl fcn_004e6b10(int id);
void* __cdecl gm_LookupEntityRecordById(int id);

/* Releases the record behind the command's 0x10 field: clears the back-pointer
 * 0x20c of every entity named in the 0x34 count table, then tears the record
 * down and reports success into the result packet. */
/* ADDRESS: GOLDTL 0x004cd500 */
int __cdecl fcn_004cd500(int* cmd, unsigned char* result)
{
	unsigned char* rec;
	int h;
	void* p;
	int i;

	rec = (unsigned char*) fcn_004e6a30(*(int*) ((char*) cmd + 0x10));
	if (rec == 0) {
		return 1;
	}
	for (i = 0; i < (int) rec[0x30]; i++) {
		h = *(int*) (rec + 0x34 + i * 4);
		if (h != -1) {
			p = gm_LookupEntityRecordById(h);
			if (p != 0 && *(int*) ((char*) p + 0x20c) == *(int*) rec) {
				*(int*) ((char*) p + 0x20c) = -1;
			}
		}
	}
	fcn_004e6b10(*(int*) ((char*) cmd + 0x10));
	if (result != 0) {
		result[0] = 1;
		result[1] = 0;
		*(int*) (result + 6) = 0;
	}
	return 0;
}
