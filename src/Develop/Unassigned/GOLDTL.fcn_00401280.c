

int __cdecl fcn_004011d0(void* stream, void* dst);

void __cdecl fcn_00401280(void* stream, void* dst)
{
	fcn_004011d0(stream, dst);
	fcn_004011d0(stream, (char*) dst + 4);
	fcn_004011d0(stream, (char*) dst + 8);
}
