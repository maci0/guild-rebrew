

void __cdecl d3_FreeSkyDome(void*);

void __cdecl d3_DestroySkySystem(void)
{
	if (*(int*) 0x6b89c0 != 0) {
		d3_FreeSkyDome((void*) *(int*) 0x6b89c0);
		*(int*) 0x6b89c0 = 0;
	}
}
