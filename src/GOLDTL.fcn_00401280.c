

int __cdecl fcn_004011d0(void* stream, void* dst);

void __cdecl fcn_00401280(void* a1, void* a2)
{
	fcn_004011d0(a1, a2);
	fcn_004011d0(a1, (char*) a2 + 4);
	fcn_004011d0(a1, (char*) a2 + 8);
}
