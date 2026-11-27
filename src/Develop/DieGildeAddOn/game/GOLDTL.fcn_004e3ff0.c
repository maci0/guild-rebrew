unsigned short* __cdecl gm_StartFilteredEntitySearch(int, ...);
char* __cdecl gm_LookupEntityRecordById(int);
int __cdecl gm_AccumulateTyped2(char*);
float __cdecl cut_RandFloat(void);
unsigned int __cdecl cut_RandMod(int);


/* ADDRESS: GOLDTL 0x004e3ff0 */
void __cdecl cut_HandleAuctionEvent(char* participant, int* bidCtx)
{
	int i;
	int val;
	int n;
	float fv;
	char* o;

	*(int*) (participant + 0x98) = 0;
	for (i = 0; i < bidCtx[0x12]; i++) {
		if (bidCtx[9 + i] == *(int*) (participant + 0x10))
			break;
	}
	if (i >= bidCtx[0x12])
		return;
	if (bidCtx[i] == -1)
		return;
	*(int*) (participant + 0x94) = bidCtx[8];
	gm_StartFilteredEntitySearch(1, 1, bidCtx[0x11]);
	val = bidCtx[8];
	o = gm_LookupEntityRecordById(*(int*) (participant + 0x10));
	if (o == 0)
		return;
	fv = (float) (val + bidCtx[0x13] * 32000);
	n = (int) ((cut_RandFloat() / 6.0f + 0.3f) * gm_AccumulateTyped2(o) < fv
	    ? (cut_RandFloat() / 6.0f + 0.3f) * gm_AccumulateTyped2(o) : fv);
	if (n < val)
		return;
	if (!(cut_RandFloat() > (float) val / n))
		return;
	if (n > val * 2)
		n = val * 2;
	n -= val;
	*(int*) (participant + 0x98) = 1;
	n = (int) ((float) val + cut_RandMod(n) * (bidCtx[0x13] * 0.1f));
	*(int*) (participant + 0x94) = n % 32 + n;
}
