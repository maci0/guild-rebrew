

/* Inferred name: four-dword reader shared by TL 0x4012b0 and Gold 0x401270. */

int __cdecl fcn_004011d0(void* stream, void* dst);

void __cdecl ReadVfsFourDwords(void* a1, void* a2)
{
	fcn_004011d0(a1, a2);
	fcn_004011d0(a1, (char*) a2 + 4);
	fcn_004011d0(a1, (char*) a2 + 8);
	fcn_004011d0(a1, (char*) a2 + 0xc);
}
