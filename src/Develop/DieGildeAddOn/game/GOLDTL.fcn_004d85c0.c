/* fcn_004d85c0 — tail-call the handler with the record's field. */

void* __cdecl gm_LookupEntityRecordIn32SlotTable(int);
void __cdecl fcn_00406120(int);

/* ADDRESS: GOLDTL 0x004d85c0 */
void __cdecl fcn_004d85c0(int* a1)
{
	void* record;

	if (a1[1] == 0) {
		return;
	}
	if (a1[0] == -1) {
		return;
	}
	record = gm_LookupEntityRecordIn32SlotTable(a1[0]);
	if (record == 0) {
		return;
	}
	fcn_00406120(*(int*) ((char*) record + 0x184));
}
