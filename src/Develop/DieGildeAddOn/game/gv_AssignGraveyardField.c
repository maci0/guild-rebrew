


int __cdecl gv_CanHireGraveyardWorker(char* e, int* out);
int* __cdecl gv_PickRandomFieldEntry(char* e);
int* __cdecl gv_LookupWorkerSlot(char* e, int* r);
int __cdecl gm_GetEntitySlotIndex(int d, int* s);
int __cdecl gv_SendAllocGraveyardWorker(char* e, int a, int b, int c, int d);

/* ADDRESS: GOLDDE 0x004df7b0 */
int __cdecl gv_AssignGraveyardField(char* e)
{
	int* r;
	int* s;
	int k;

	if (gv_CanHireGraveyardWorker(e, 0) != 1) {
		return -1;
	}
	r = gv_PickRandomFieldEntry(e);
	if (r == 0) {
		return -1;
	}
	s = gv_LookupWorkerSlot(e, r);
	if (s == 0) {
		return -1;
	}
	k = gm_GetEntitySlotIndex(*(int*) (e + 0x65), s);
	if (k == -1) {
		return k;
	}
	return gv_SendAllocGraveyardWorker(e, *s, k, *r, 0x1c);
}
