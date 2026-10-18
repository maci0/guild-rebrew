void __cdecl fcn_0041e740(void*);

/* ADDRESS: GOLD 0x004790d0 */
int __cdecl fcn_004790d0(void* record)
{
	char* objekt;

	objekt = (char*) record;
	if (*(int*) (objekt + 0x34) == 0)
		return 0;
	if (*(void**) (objekt + 0x20) != 0) {
		fcn_0041e740(*(void**) (objekt + 0x20));
		*(int*) (objekt + 0x1c) = 0;
	}
	*(int*) (objekt + 0x34) = 0;
	return 1;
}
