void* __cdecl fcn_00422460(int, int);
void __cdecl fcn_004238f0(void*, int);
void __cdecl fcn_00423670(void*, int, int);

/* ADDRESS: GOLDTL 0x00410f50 */
void* __cdecl PlaySample(int* sampleId, int* playbackControl)
{
	void* h;

	if (*(int*) ((char*) *(void**) 0x6b7e98 + 0x104) != *(int*) 0x6791c8)
		return 0;
	h = fcn_00422460(0, *sampleId);
	if (h != 0) {
		fcn_004238f0(h, *playbackControl);
		fcn_00423670(h, 0, 0);
	} else {
		fcn_00422460(0, *sampleId);
	}
	return h;
}
