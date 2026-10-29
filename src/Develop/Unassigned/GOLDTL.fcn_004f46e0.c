

extern unsigned char* lpGebaeudeINST;
extern unsigned char* lpGebaeudePROT;

void* __cdecl FindSlotEntryFiltered(int a, unsigned char* rec, void* prev, void* filter, int mask);
int __cdecl fcn_004ef740(void);

int __cdecl fcn_004f46e0(int a, unsigned char** out1, void** out2)
{
	unsigned char* rec;
	void* r;
	int i;

	*out1 = 0;
	*out2 = 0;
	rec = lpGebaeudeINST;
	for (i = 0; i < 256; i++, rec += 0xa9) {
		if (rec[0] != 0 && lpGebaeudePROT[rec[0] * 0x24d] == 0x1d) {
			r = FindSlotEntryFiltered(a, rec, 0, (void*) fcn_004ef740, 0xff);
			if (r != 0) {
				*out1 = rec;
				*out2 = r;
				return 1;
			}
		}
	}
	return 0;
}
