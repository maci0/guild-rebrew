

int __cdecl amt_ValidateOfficeRequest(char*);

/* ADDRESS: GOLDDE 0x004b4b20 */
int __cdecl fcn_004c7330(char* p)
{
	return amt_ValidateOfficeRequest(p + 0x10) == 0;
}
