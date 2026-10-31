void* __cdecl fcn_004c7550(void* p);
void* __cdecl fcn_004e6a30(int id);
void* __cdecl gm_LookupEntityRecordById(int id);

/* Attach counterpart of 0x004cd500: rejects an already attached command, marks
 * the result as failure, then links the fresh record into up to 16 entities and
 * reports success into the result packet. */
/* ADDRESS: GOLDTL 0x004cd590 */
int __cdecl fcn_004cd590(int* a, unsigned char* result)
{
	void* rec;
	void* e;
	int i;

	if (fcn_004c7550(a) != 0) {
		if (result != 0) {
			result[0] = 2;
		}
		return 1;
	}
	if (result != 0) {
		result[0] = 2;
	}
	rec = fcn_004e6a30(*(int*) ((char*) a + 0x10));
	if (rec != 0) {
		*(int*) ((char*) rec + 0x28) = 1;
	}
	for (i = 0; i < 16; i++) {
		e = gm_LookupEntityRecordById(*(int*) ((char*) a + 0x14 + i * 4));
		if (e != 0) {
			*(int*) ((char*) e + 0x20c) = *(int*) ((char*) a + 0x10);
		}
	}
	if (result != 0) {
		result[0] = 1;
		result[1] = 0;
		*(int*) (result + 6) = 0;
	}
	return 0;
}
