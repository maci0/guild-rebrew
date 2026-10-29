int __cdecl fcn_004f1890(int*, int*);



int __cdecl FindSlotEntryFiltered(int*, int, int, void*, int);

int __cdecl fcn_004f1a10(int a1, int* a2)
{
	if (a2 == 0 || *a2 == -1) {
		return 0;
	}
	return FindSlotEntryFiltered(a2, a1, 0, (void*) fcn_004f1890, 0xff);
}
