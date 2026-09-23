/* fcn_004d85c0 — tail-call the handler with the record's field. */

void* __cdecl fcn_004cef30(int);
void __cdecl fcn_00406120(int);

// FUNCTION: GOLD 0x004d6f60
// SIZE: 47
// FUNCTION: GOLDTL 0x4d85c0
// SIZE: 47
void __cdecl fcn_004d85c0(int* a1)
{
	void* record;

	if (a1[1] == 0) {
		return;
	}
	if (a1[0] == -1) {
		return;
	}
	record = fcn_004cef30(a1[0]);
	if (record == 0) {
		return;
	}
	fcn_00406120(*(int*) ((char*) record + 0x184));
}
