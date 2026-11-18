unsigned short* __cdecl gm_LookupEntityRecordById(int id);
float __cdecl fcn_0050f980(unsigned int a0, unsigned int a1, unsigned int a2);
unsigned short __cdecl gm_RandomMod(int n);

/* ADDRESS: GOLDTL 0x00493800 */
int __cdecl fcn_00493800(char* p)
{
	unsigned short* targetRecord;
	unsigned short* firstRecord;
	unsigned short* secondRecord;
	float firstResult;
	float secondResult;

	targetRecord = gm_LookupEntityRecordById(*(int*) (p + 0x28));
	if (!targetRecord) {
		return 1;
	}
	firstRecord = gm_LookupEntityRecordById(*(int*) (p + 0x18));
	secondRecord = gm_LookupEntityRecordById(*(int*) (p + 0x14));
	firstResult = fcn_0050f980(*firstRecord, *targetRecord, 1);
	secondResult = fcn_0050f980(*secondRecord, *targetRecord, 1);
	if (firstResult - secondResult > 20.0f) {
		return 1;
	}
	if (secondResult - firstResult > 20.0f) {
		return 0;
	}
	return gm_RandomMod(2);
}
