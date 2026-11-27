
// fcn_004c67a0 — fcn_004e6710(arg+0x10) == 0.

int __cdecl amt_ValidateOfficeRequest(void*);

int __cdecl fcn_004c67a0(void* a)
{
	return amt_ValidateOfficeRequest((char*) a + 0x10) == 0;
}
