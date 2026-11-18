

/* Inferred name: four-dword reader shared by TL 0x4012b0 and Gold 0x401270. */

int __cdecl fcn_004011d0(void* stream, void* dst);

void __cdecl ReadVfsFourDwords(void* stream, void* dst)
{
	fcn_004011d0(stream, dst);
	fcn_004011d0(stream, (char*) dst + 4);
	fcn_004011d0(stream, (char*) dst + 8);
	fcn_004011d0(stream, (char*) dst + 0xc);
}
