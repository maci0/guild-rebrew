

void __cdecl d3_DeinitUniverse(void*);

void __cdecl d3_ApplyDisplayFlags(void)
{
	void* p;

	p = *(void**) 0x772f48;
	if (p != 0) {
		d3_DeinitUniverse(p);
	}
}
