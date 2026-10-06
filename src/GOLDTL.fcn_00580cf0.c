// FUNCTION: GOLD 0x00578700
// FUNCTION: GOLDTL 0x580cf0

void __cdecl fcn_0041ddd0(void*);

void __cdecl fcn_00580cf0(char* node)
{
	if (node != 0) {
		if (*(char**) (node + 0x70) != 0) {
			fcn_00580cf0(*(char**) (node + 0x70));
		}
		if (*(void**) (node + 0x58) != 0) {
			fcn_0041ddd0(*(void**) (node + 0x58));
			*(void**) (node + 0x58) = 0;
		}
		if (*(void**) (node + 0x64) != 0) {
			fcn_0041ddd0(*(void**) (node + 0x64));
			*(void**) (node + 0x64) = 0;
		}
		fcn_0041ddd0(node);
	}
}
