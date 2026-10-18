
int __cdecl fcn_004011d0(void* stream, void* dst);

void __cdecl fcn_00401240(void* u, void* x)
{
	fcn_004011d0(u, x);
	fcn_004011d0(u, (char*) x + 4);
	fcn_004011d0(u, (char*) x + 8);
}
