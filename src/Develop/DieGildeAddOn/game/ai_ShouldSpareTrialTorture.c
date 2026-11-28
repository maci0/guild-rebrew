unsigned short* __cdecl gm_LookupEntityRecordById(int id);
float __cdecl gm_CalcEntityFavor(unsigned int a0, unsigned int a1, unsigned int a2);
unsigned short __cdecl gm_RandomMod(int n);

/* ADDRESS: GOLDTL 0x00493800 */
/* ADDRESS: GOLDDE 0x00482650 */
int __cdecl ai_ShouldSpareTrialTorture(char* trial)
{
	unsigned short* torturerRecord;
	unsigned short* accusedRecord;
	unsigned short* plaintiffRecord;
	float accusedFavor;
	float plaintiffFavor;

	torturerRecord = gm_LookupEntityRecordById(*(int*) (trial + 0x28));
	if (!torturerRecord) {
		return 1;
	}
	accusedRecord = gm_LookupEntityRecordById(*(int*) (trial + 0x18));
	plaintiffRecord = gm_LookupEntityRecordById(*(int*) (trial + 0x14));
	accusedFavor = gm_CalcEntityFavor(*accusedRecord, *torturerRecord, 1);
	plaintiffFavor = gm_CalcEntityFavor(*plaintiffRecord, *torturerRecord, 1);
	if (accusedFavor - plaintiffFavor > 20.0f) {
		return 1;
	}
	if (plaintiffFavor - accusedFavor > 20.0f) {
		return 0;
	}
	return gm_RandomMod(2);
}
