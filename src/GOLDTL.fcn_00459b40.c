// FUNCTION: GOLDTL 0x459b40
// SIZE: 56

void __cdecl fcn_004597f0(void*, void*);
void __cdecl fcn_00459a90(void*);
void __cdecl fcn_0041ddd0(void*);

void __cdecl fcn_00459b40(char* p)
{
	if (p == 0) {
		return;
	}
	while (*(void**) (p + 0x24) != 0) {
		fcn_004597f0(p, *(void**) (p + 0x24));
	}
	fcn_00459a90(p);
	fcn_0041ddd0(p);
}
